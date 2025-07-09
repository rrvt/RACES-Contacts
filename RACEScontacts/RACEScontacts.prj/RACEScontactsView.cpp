// RACEScontactsView.cpp : implementation of the RACEScontactsView class


#include "pch.h"
#include "RACEScontactsView.h"
#include "IniFileEx.h"
#include "OptionsDlg.h"
#include "RACEScontacts.h"
#include "RACEScontactsDoc.h"
#include "Resource.h"
#include "ResourceData.h"
#include "RptOrientDlgTwo.h"


static TCchar* StrOrietnKey = _T("Store");


// RACEScontactsView

IMPLEMENT_DYNCREATE(RACEScontactsView, CScrView)

BEGIN_MESSAGE_MAP(RACEScontactsView, CScrView)
  ON_COMMAND(ID_Options,     &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)
END_MESSAGE_MAP()


RACEScontactsView::RACEScontactsView() noexcept :
                                                dspStore(dMgr.getNotePad()), prtStore(pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


BOOL RACEScontactsView::PreCreateWindow(CREATESTRUCT& cs) {

  return CScrView::PreCreateWindow(cs);
  }


void RACEScontactsView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }


void RACEScontactsView::onRptOrietn() {
RptOrietnDlg dlg;

  dlg.lbl01 = _T("Store:");
  dlg.ntpd = printer.toStg(prtNote.prtrOrietn);
  dlg.rpt1 = printer.toStg(prtStore.prtrOrietn);

  if (dlg.DoModal() == IDOK) {
    prtNote.prtrOrietn  = printer.toOrient(dlg.ntpd);
    prtStore.prtrOrietn = printer.toOrient(dlg.rpt1);
    saveRptOrietn();
    }
  }


void RACEScontactsView::initRptOrietn() {
  prtStore.prtrOrietn = (PrtrOrient) iniFile.readInt(RptOrietnSect, StrOrietnKey, PortOrient);
  }


void RACEScontactsView::saveRptOrietn() {
  saveNoteOrietn();
  iniFile.write(RptOrietnSect, StrOrietnKey,  (int) prtStore.prtrOrietn);
  }


void RACEScontactsView::onPreparePrinting(CPrintInfo* info) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onPreparePrinting(info);     break;
#ifdef Examples
    case StoreSrc   : prtStore.onPreparePrinting(info);    break;
#endif
    }
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void RACEScontactsView::onBeginPrinting() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onBeginPrinting(*this);  break;
    case StoreSrc   : prtStore.onBeginPrinting(*this); break;
    }
  }


void RACEScontactsView::onDisplayOutput() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : dspNote.display(*this);  break;
    case StoreSrc   : dspStore.display(*this); break;
    }
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void RACEScontactsView::printFooter(DevStream& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.prtFooter(dev, pageNo);  break;
    case StoreSrc   : prtStore.prtFooter(dev, pageNo); break;
    }
  }



void RACEScontactsView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    case StoreSrc   : break;
    }
  }


void RACEScontactsView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    case StoreSrc   : break;
    }
  }


// RACEScontactsView diagnostics

#ifdef _DEBUG

void RACEScontactsView::AssertValid() const {CScrollView::AssertValid();}

void RACEScontactsView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
RACEScontactsDoc* RACEScontactsView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(RACEScontactsDoc))); return (RACEScontactsDoc*)m_pDocument;}

#endif //_DEBUG
