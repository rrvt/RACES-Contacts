// Store Report -- Template for such a report


#pragma once
#include "ReportBase.h"

class NotePad;
class Datum;


class StoreRpt : public ReportBase {

public:

int maxName;
int maxEmpl;
int maxEmail;

  StoreRpt(NotePad& notePad) : ReportBase(notePad) { }
 ~StoreRpt() { }

  void   onBeginPrinting(CScrView& vw);

  void   prtHeader(DevBase& dev, int pageNo = 1);
  void   prtFooter(DevBase& dev, int pageNo);

  void   setMaxes();

  void   hdrLine1(DevBase& dev);
  void   hdrLine2(DevBase& dev);
  void   hdrLine3(DevBase& dev);
  void   line1(Datum* dtm);
  void   line2(Datum* dtm);
  void   line3(Datum* dtm);
  String formatPhone(TCchar* ph);

private:

  void   getData(CScrView& vw);
  void   setTabs();
  void   setTabs2();
  void   setTabs3();

  StoreRpt() : ReportBase(*(NotePad*)0) { }
  };




//  int    header(NotePad& np, bool printing);

