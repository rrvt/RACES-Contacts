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

  StoreRpt(NotePad& notePad) : ReportBase(notePad, ReportID) { }
 ~StoreRpt() { }

  void   onBeginPrinting(CScrView& vw);

  void   prtHeader(DevStream& dev, int pageNo = 1);
  void   prtFooter(DevStream& dev, int pageNo);

  void   setMaxes();

  void   hdrLine1(DevStream& dev);
  void   hdrLine2(DevStream& dev);
  void   hdrLine3(DevStream& dev);
  void   line1(Datum* dtm);
  void   line2(Datum* dtm);
  void   line3(Datum* dtm);
  String formatPhone(TCchar* ph);

private:

  void   getData();
  void   setTabs();
  void   setTabs2();
  void   setTabs3();

  StoreRpt() : ReportBase(*(NotePad*)0, ReportID) { }
  };




//  int    header(NotePad& np, bool printing);

