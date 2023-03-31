// Store Report -- Template for such a report


#include "pch.h"
#include "StoreRpt.h"
#include "CScrView.h"
#include "Store.h"


static const int PhoneTab = 11;
static const int FCCtab   = 8;


void StoreRpt::onBeginPrinting(CScrView& vw) {

  printing = true;

  vw.disablePrtWrap();

  vw.getNoPages();

  getData(vw);
  }


void StoreRpt::getData(CScrView& vw) {
DSIter iter(store);
Datum* dtm;
int    i;
int    n;

  np.clear();   setMaxes();

  for (i = 0, dtm = iter(); dtm; i++, dtm = iter++) {

    n = dtm->isThirdLine() ? 4 : 3;

    setTabs();    line1(dtm);

    setTabs2();   line2(dtm);

    setTabs3();   line3(dtm);

    np << nCrlf;
    }
  }


void StoreRpt::line1(Datum* dtm) {

  if (store.storeSort == FCCsort) {
    np << dtm->callSign;
    np << nTab << dtm->lastName << _T(", ") << dtm->firstName;
    }
  else {
    np << dtm->lastName << _T(", ") << dtm->firstName;
    np << nTab << dtm->callSign;
    }
  np << nTab << formatPhone(dtm->prmPhone);
  np << nTab << formatPhone(dtm->celPhone);
  np << nTab << formatPhone(dtm->prmText);
  np << nTab << formatPhone(dtm->SecText);
  np << nCrlf;
  }


void StoreRpt::line2(Datum* dtm) {np << nTab << dtm->prmEmail << nTab << dtm->secEmail << nCrlf;}


// !dtm->employer.isEmpty() && (!dtm->wrkEmail.isEmpty() || !dtm->wrkPhone.isEmpty())

void StoreRpt::line3(Datum* dtm) {

  if (dtm->isThirdLine()) {
    np << nTab << dtm->employer << nTab << formatPhone(dtm->wrkPhone);
    np << nTab << dtm->wrkEmail << nCrlf;
    }
  }


void StoreRpt::setMaxes() {
DSIter iter(store);
Datum* dtm;

  maxName = 0;   maxEmpl = 0;   maxEmail = 0;

  for (dtm = iter(); dtm; dtm = iter++) {
    int t = dtm->firstName.length() + dtm->lastName.length() + 2;   if (t > maxName)  maxName  = t;
    t = dtm->employer.length();                                     if (t > maxEmpl)  maxEmpl  = t;
    t = dtm->prmEmail.length();                                     if (t > maxEmail) maxEmail = t;
    }
  }



String StoreRpt::formatPhone(TCchar* ph) {
String s = ph;
String t;
int    n = s.length();   if (!n) return _T("          ");

  t = s.substr(0, 3);   s = t + _T('.') + s.substr(3);

  t = s.substr(0, 7);   s = t + _T('.') + s.substr(7);   return s;
  }


void StoreRpt::prtHeader(DevBase& dev, int pageNo) {

  setTabs();   hdrLine1(dev);
  setTabs2();  hdrLine2(dev);
  setTabs3();  hdrLine3(dev);
  dev << dCrlf;
  }



void StoreRpt::setTabs() {
int tab1 = store.storeSort == FCCsort ? FCCtab : maxName * 8 /10;
int tab2 = tab1 + (store.storeSort == FCCsort ? maxName * 8 / 10 : FCCtab);
int tab3 = tab2 + PhoneTab;
int tab4 = tab3 + PhoneTab;
int tab5 = tab4 + PhoneTab;

  np << nClrTabs << nSetTab(tab1) << nSetTab(tab2) << nSetTab(tab3) << nSetTab(tab4) << nSetTab(tab5);
  }


void StoreRpt::setTabs2() {
int tab1 = FCCtab;
int tab2 = tab1 + maxEmail * 8 / 10;

  np << nClrTabs << nSetTab(tab1) << nSetTab(tab2);
  }


void StoreRpt::setTabs3() {
int tab1 = FCCtab;
int tab2 = tab1 + maxEmpl * 8 / 10;
int tab3 = tab2 + PhoneTab;

  np << nClrTabs << nSetTab(tab1) << nSetTab(tab2) << nSetTab(tab3);
  }


void StoreRpt::hdrLine1(DevBase& dev) {
String s = store.date() + _T(" ") + store.time();

  dev << store.name << dRight << s << dCrlf;

  if (store.storeSort == FCCsort) dev << _T("Call Sign") << dTab << _T("Member Name");
  else                            dev << _T("Member Name") << dTab << _T("Call Sign");
  dev << dTab << _T("Primary Phone");
  dev << dTab << _T("Cell Phone");
  dev << dTab << _T("Primary Text");
  dev << dTab << _T("Secdry Text");
  dev << dCrlf;
  }


void StoreRpt::hdrLine2(DevBase& dev)
                          {dev << dTab << _T("Primary eMail") << dTab << _T("Secondary eMail") << dCrlf;}


void StoreRpt::hdrLine3(DevBase& dev) {
  dev << dBeginLine << dTab << _T("Employer") << dTab << _T("Work Phone") << dTab << _T("work eMail");
  dev << dRight << dEndLine << dCrlf;
  }


void StoreRpt::prtFooter(DevBase& dev, int pageN) {

  if (pageN > maxPages) maxPages = pageN;

  dev << dCenter << pageN << _T(" of ") << maxPages << dFlushFtr;
  }


