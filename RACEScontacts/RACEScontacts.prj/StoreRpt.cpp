// Store Report -- Template for such a report


#include "pch.h"
#include "StoreRpt.h"
#include "CScrView.h"
#include "Store.h"


static const int PhoneTab = 11;
static const int FCCtab   = 8;


void StoreRpt::print(CScrView& vw) {

  printing = true;

  maxLines = vw.noLinesPrPg();

  vw.disableWrap(printing);

  detNoPages(vw);

  create(vw);
  }


void StoreRpt::create(CScrView& vw) {
DSIter iter(store);
Datum* dtm;
int    i;
int    n;

  np.clear();   noLines = BigNmbr;  setMaxes();

  for (i = 0, dtm = iter(); dtm; i++, dtm = iter++) {

    n = dtm->isThirdLine() ? 4 : 3;

    if (noLines + n > maxLines) {

      if (i) np << nEndPage;

      noLines = header(np, printing);
      }

    setTabs();    line1(dtm);   noLines++;

    setTabs2();   line2(dtm);   noLines++;

    setTabs3();   line3(dtm);               // conditional line

    np << nCrlf;                noLines++;

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
    np << nTab << dtm->wrkEmail << nCrlf;     noLines += 1;
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


int StoreRpt::header(NotePad& np, bool printing) {
int nLines;

  setTabs();   hdrLine1();   nLines = 2;

  setTabs2();  hdrLine2();   nLines++;

  setTabs3();  hdrLine3();   nLines++;
  np << nCrlf;               nLines++;    return nLines;
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


void StoreRpt::hdrLine1() {
String s = store.date() + _T(" ") + store.time();

  np << store.name << nRight << s << nCrlf;

  if (store.storeSort == FCCsort) np << _T("Call Sign") << nTab << _T("Member Name");
  else                            np << _T("Member Name") << nTab << _T("Call Sign");
  np << nTab << _T("Primary Phone");
  np << nTab << _T("Cell Phone");
  np << nTab << _T("Primary Text");
  np << nTab << _T("Secdry Text");
  np << nCrlf;
  }


void StoreRpt::hdrLine2() {np << nTab << _T("Primary eMail") << nTab << _T("Secondary eMail") << nCrlf;}


void StoreRpt::hdrLine3() {
  np << nBeginLine << nTab << _T("Employer") << nTab << _T("Work Phone") << nTab << _T("work eMail");
  np << nRight << nEndLine << nCrlf;
  }


void StoreRpt::footer(Device& dev, int pageN) {

  if (pageN > maxPages) maxPages = pageN;

  dev << dRight << pageN << _T(" of ") << maxPages << dFlushFtr;
  }


