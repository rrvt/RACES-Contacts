// Sample Data Store


#include "pch.h"
#include "Store.h"
#include "EntTbl.h"
#include "MbrTbl.h"
#include "NotePad.h"
#include "StsTbl.h"
#include "StoreRpt.h"
#include "Utilities.h"


const int TabVal = 5;

static const int PhoneTab = 14;
static const int FCCtab   = 10;


Store store;                                        // Global since all classes need access



void Store::setName(String& s) {name = s; dt.getToday();}


int Store::missionNo() {
  if (!mssnNo) {Date d; d.getToday();   CTimeSpan t = d - dt;  mssnNo = t.GetSeconds() % 60;}

  return mssnNo;
  }


// Load is called from serialize in the Document class
// The basic idea is that the method reads some chunk from the file (Archive is a fileio surrogate)

void Store::load() {
MbrIter iter(mbrTbl);
MbrRcd* rcd;

  data.clear();

  for (rcd = iter(); rcd; rcd = iter++) {
    StsRcd* sts = stsTbl.find(rcd->statusID);   if (!sts) continue;

    if (sts->abbreviation == _T("Fmr")) continue;
    EntRcd* mbr  = entTbl.find(rcd->mbrEntityID);   if (!mbr) continue;
    EntRcd* empl = entTbl.find(rcd->emplEntityID);


    Datum dtm;

    dtm.firstName = mbr->firstName;
    dtm.lastName  = mbr->lastName;
    dtm.callSign  = rcd->callSign;
    dtm.prmPhone  = mbr->phone1;
    dtm.celPhone  = mbr->phone2;
    dtm.prmText   = rcd->textMsgPh1;
    dtm.SecText   = rcd->textMsgPh2;
    dtm.prmEmail  = mbr->eMail;
    dtm.secEmail  = rcd->secondaryEmail;
    if (empl) {
      dtm.employer  = empl->firstName;
      dtm.wrkPhone  = empl->phone1;
      dtm.wrkEmail  = empl->eMail;
      }

    data += dtm;
    }

  notePad << _T("Number of Members in Contact List: ") << nData() << nCrlf;
  }


void Store::sortByFCC() {
DSIter iter(*this);
Datum* dtm;

  storeSort = FCCsort;

  for (dtm = iter(); dtm; dtm = iter++) {
    dtm->key = dtm->callSign;
    }
  sort();
  }


void Store::sortByName() {
DSIter iter(*this);
Datum* dtm;

  storeSort = NameSort;

  for (dtm = iter(); dtm; dtm = iter++) {
    dtm->key = dtm->lastName + dtm->firstName + dtm->callSign;
    }

  sort();
  }


void Store::store(Archive& ar) {
DSIter   iter(*this);
Datum*   dtm;
StoreRpt rpt(notePad);

  notePad.clear();   rpt.setMaxes();

  setTabs1(rpt); rpt.hdrLine1();
  setTabs2(rpt); rpt.hdrLine2();
  setTabs3(rpt); rpt.hdrLine3();
  for (int i = 0; i < 106; i++) notePad << _T("-");    notePad << nCrlf;

  for (dtm = iter(); dtm; dtm = iter++) {
    setTabs1(rpt); rpt.line1(dtm);
    setTabs2(rpt); rpt.line2(dtm);
    setTabs3(rpt); rpt.line3(dtm);
    notePad << nCrlf;
    }

  notePad.archive(ar);

  notePad.clear();
  }


void Store::setTabs1(StoreRpt& rpt) {
int tab1 = storeSort == FCCsort ? FCCtab : rpt.maxName + 1;
int tab2 = tab1 + (storeSort == FCCsort ? rpt.maxName + 1 : FCCtab);
int tab3 = tab2 + PhoneTab;
int tab4 = tab3 + PhoneTab;
int tab5 = tab4 + PhoneTab;

  notePad << nClrTabs << nSetTab(tab1) << nSetTab(tab2) << nSetTab(tab3);
  notePad << nSetTab(tab4) << nSetTab(tab5);
  }


void Store::setTabs2(StoreRpt& rpt) {
int tab1 = FCCtab;
int tab2 = tab1 + rpt.maxEmail + 1;

  notePad << nClrTabs << nSetTab(tab1) << nSetTab(tab2);
  }


void Store::setTabs3(StoreRpt& rpt) {
int tab1 = FCCtab;
int tab2 = tab1 + rpt.maxEmpl + 1;
int tab3 = tab2 + PhoneTab;

  notePad << nClrTabs << nSetTab(tab1) << nSetTab(tab2) << nSetTab(tab3);
  }


void Store::storeCSV(Archive& ar) {
DSIter   iter(*this);
Datum*   dtm;

  notePad.clear();

  csvHdr();

  for (dtm = iter(); dtm; dtm = iter++) {
    csvLine1(dtm); csvLine2(dtm); csvLine3(dtm); notePad << nCrlf;
    }

  notePad.archive(ar);   notePad.clear();
  }


void Store::csvHdr() {
String s = date() + _T(" ") + time();

  notePad << name << _T(",,,,,,,,,,,") << s << nCrlf;

  if (storeSort == FCCsort) notePad << _T("Call Sign,") << _T("Last Name,") << _T("First Name");
  else                      notePad << _T("Last Name,") << _T("First Name,") << _T("Call Sign");
  notePad << _T(',') << _T("Primary Phone");
  notePad << _T(',') << _T("Cell Phone");
  notePad << _T(',') << _T("Primary Text");
  notePad << _T(',') << _T("Secdry Text");
  notePad << _T(',') << _T("Primary eMail");
  notePad << _T(',') << _T("Secondary eMail");
  notePad << _T(',') << _T("Employer");
  notePad << _T(',') << _T("Work Phone");
  notePad << _T(',') << _T("work eMail");
  notePad << nCrlf;
  }


void Store::csvLine1(Datum* dtm) {

  if (storeSort == FCCsort) {
    notePad << dtm->callSign;
    notePad << _T(',') << dtm->lastName << _T(", ") << dtm->firstName;
    }
  else {
    notePad << dtm->lastName << _T(", ") << dtm->firstName;
    notePad << _T(',') << dtm->callSign;
    }
  notePad << _T(',') << formatPhone(dtm->prmPhone, _T('.'));
  notePad << _T(',') << formatPhone(dtm->celPhone, _T('.'));
  notePad << _T(',') << formatPhone(dtm->prmText,  _T('.'));
  notePad << _T(',') << formatPhone(dtm->SecText,  _T('.'));
  }


void Store::csvLine2(Datum* dtm)
                              {notePad << _T(',') << dtm->prmEmail << _T(',') << dtm->secEmail;}



void Store::csvLine3(Datum* dtm) {
  if (dtm->isThirdLine()) {
    notePad << _T(',') << addQuotes(dtm->employer) << _T(',') << formatPhone(dtm->wrkPhone, _T('.'));
    notePad << _T(',') << dtm->wrkEmail;
    }
  }




int Datum::display() {
#if 0
WrapIter  iter(wrp);
WrapData* wd;
int       i;

  notePad << nClrTabs << nSetTab(TabVal) << _T(',');       // The tab is set to the same value as in wrap

  for (wd = iter(), i = 0; wd; wd = iter++, i++) {
    if (i) notePad << nTab;

    notePad << wd->line << nCrlf;
    }

  return i;
  #endif
  return 0;
  }





void Datum::copy(Datum& d) {

  firstName = d.firstName;
  lastName  = d.lastName;
  callSign  = d.callSign;
  prmPhone  = d.prmPhone;
  celPhone  = d.celPhone;
  prmText   = d.prmText;
  SecText   = d.SecText;
  prmEmail  = d.prmEmail;
  secEmail  = d.secEmail;
  employer  = d.employer;
  wrkPhone  = d.wrkPhone;
  wrkEmail  = d.wrkEmail;
  }

