// RACEScontactsView.cpp : implementation of the RACEScontactsView class


#include "stdafx.h"
#include "RACEScontactsView.h"
#include "RACEScontacts.h"
#include "RACEScontactsDoc.h"
#include "Options.h"
#include "Resources.h"


// RACEScontactsView

IMPLEMENT_DYNCREATE(RACEScontactsView, CScrView)

BEGIN_MESSAGE_MAP(RACEScontactsView, CScrView)
END_MESSAGE_MAP()


RACEScontactsView::RACEScontactsView() noexcept :
                                    dspStore(dMgr.getNotePad()), prtStore(pMgr.getNotePad()),
                                    dspNote( dMgr.getNotePad()), prtNote( pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


BOOL RACEScontactsView::PreCreateWindow(CREATESTRUCT& cs) {

  return CScrView::PreCreateWindow(cs);
  }


void RACEScontactsView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  setMgns(leftMgn,  topMgn,  rightMgn, botMgn, pDC);   CScrView::OnPrepareDC(pDC, pInfo);
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void RACEScontactsView::onPrepareOutput(bool printing) {
DataSource ds = doc()->dataSrc();

  if (printing)
    switch(ds) {
      case NotePadSrc : prtNote.print(*this);  break;
      case StoreSrc   : prtStore.print(*this); break;
      }

  else
    switch(ds) {
      case NotePadSrc : dspNote.display(*this);  break;
      case StoreSrc   : dspStore.display(*this); break;
      }


  CScrView::onPrepareOutput(printing);
  }


void RACEScontactsView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : setOrientation(options.orient); break;    // Setup separate Orientation?
    case StoreSrc   : setOrientation(options.orient); break;
    }
  setPrntrOrient(theApp.getDevMode(), pDC);   CScrView::OnBeginPrinting(pDC, pInfo);
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void RACEScontactsView::printFooter(Device& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.footer(dev, pageNo);  break;
    case StoreSrc   : prtStore.footer(dev, pageNo); break;
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
