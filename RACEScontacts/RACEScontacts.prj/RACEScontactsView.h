// RACEScontactsView.h : interface of the RACEScontactsView class


#pragma once
#include "CScrView.h"
#include "NotePadRpt.h"
#include "StoreRpt.h"


class RACEScontactsDoc;


class RACEScontactsView : public CScrView {

StoreRpt   dspStore;
StoreRpt   prtStore;

protected: // create from serialization only

  RACEScontactsView() noexcept;

  DECLARE_DYNCREATE(RACEScontactsView)

public:

  virtual ~RACEScontactsView() { }

  virtual void initRptOrietn();
  virtual void saveRptOrietn();

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual void onPreparePrinting(CPrintInfo* info);
  virtual void onBeginPrinting();
  virtual void onDisplayOutput();

  virtual void printFooter(DevBase& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  RACEScontactsDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void onOptions();
  afx_msg void onRptOrietn();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in RACEScontactsView.cpp
inline RACEScontactsDoc* RACEScontactsView::GetDocument() const
   { return reinterpret_cast<RACEScontactsDoc*>(m_pDocument); }
#endif

