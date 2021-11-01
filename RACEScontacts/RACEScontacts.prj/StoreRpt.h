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

  void   print(CScrView& vw);
                                                    // number of pages that will be produced
  void   footer(Device& dev, int pageNo);          // Output page Footer to NotePad

  void   setMaxes();

  void   hdrLine1();
  void   hdrLine2();
  void   hdrLine3();
  void   line1(Datum* dtm);
  void   line2(Datum* dtm);
  void   line3(Datum* dtm);
  String formatPhone(TCchar* ph);

private:

  void   create(CScrView& vw);
  int    header(NotePad& np, bool printing);
  void   setTabs();
  void   setTabs2();
  void   setTabs3();

  StoreRpt() : ReportBase(*(NotePad*)0) { }
  };

