// MainFrm.cpp : implementation of the MainFrame class


#include "stdafx.h"
#include "MainFrame.h"
#include "resource.h"


// MainFrame

IMPLEMENT_DYNCREATE(MainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(MainFrame, CFrameWndEx)
  ON_WM_CREATE()
  ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, &OnResetToolBar)              // MainFrame::
END_MESSAGE_MAP()


static UINT indicators[] = {
  ID_SEPARATOR,           // status line indicator
  ID_INDICATOR_CAPS,
  ID_INDICATOR_NUM,
  ID_INDICATOR_SCRL,
  };

// MainFrame construction/destruction

MainFrame::MainFrame() noexcept { }

MainFrame::~MainFrame() { }


BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs) {

  cs.style &= ~FWS_ADDTOTITLE;  cs.lpszName = _T("AddProj");         // Sets the default title left part

  return CFrameWndEx::PreCreateWindow(cs);
  }


int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {

  if (CFrameWndEx::OnCreate(lpCreateStruct) == -1) return -1;

  if (!m_wndMenuBar.Create(this)) {TRACE0("Failed to create menubar\n"); return -1;}
  CMFCPopupMenu::SetForceMenuFocus(FALSE);

  if (!toolBar.CreateEx(this, TBSTYLE_FLAT,
                                        WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY) ||
      !toolBar.LoadToolBar(IDR_MAINFRAME, 0, 0, TRUE)) {TRACE0("Failed to create toolbar\n"); return -1;}

  if (!m_wndStatusBar.Create(this)) {TRACE0("Failed to create status bar\n"); return -1;}

  m_wndStatusBar.SetIndicators(indicators, noElements(indicators));  //sizeof(indicators)/sizeof(UINT)

  DockPane(&m_wndMenuBar);
  DockPane(&toolBar);

  CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
                                                                         // Affects look of toolbar, etc.
  return 0;
  }


void MainFrame::setupToolBar() {
CRect winRect;   GetWindowRect(&winRect);   toolBar.initialize(winRect);

  toolBar.installMenu(ID_ContactList, IDR_MemberStatus,    _T("Sort Contacts"));
  toolBar.installMenu(ID_CSVfileSave, IDR_CSVsaveFileMode, _T("Sort && Save CSV File"));
  }


// MainFrame message handlers

afx_msg LRESULT MainFrame::OnResetToolBar(WPARAM wParam, LPARAM lParam) {setupToolBar();  return 0;}


// MainFrame diagnostics

#ifdef _DEBUG
void MainFrame::AssertValid() const
{
  CFrameWndEx::AssertValid();
}

void MainFrame::Dump(CDumpContext& dc) const
{
  CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// MainFrame message handlers




#ifdef Examples
  if (!menu2.m_hMenu) menu2.LoadMenu(IDR_PopupMenu2);

  toolBar.setBtnCtrl(ID_MyBtn,  _T("Load Combo"), 100);
  toolBar.setCbxCtrl(ID_CB,      100, 500);
  toolBar.setEbxCtrl(ID_EditBox, 100);
  toolBar.setMnuCtrl(ID_MyBtn1, menu.GetSafeHmenu(),  _T("Menu 1"));
  toolBar.setMnuCtrl(ID_Btn2,   menu2.GetSafeHmenu(), _T("Menu 2"));
#endif

//  if ( !menu.m_hMenu)  menu.LoadMenu(IDR_PopupMenu);




#if 0
  if (!stsMenu.m_hMenu) stsMenu.LoadMenu(IDR_MemberStatus);
  if (!csvMenu.m_hMenu) csvMenu.LoadMenu(IDR_CSVsaveFileMode);

  toolBar.setMnuCtrl(ID_ContactList, stsMenu.GetSafeHmenu(), _T("Sort Contacts"));
  toolBar.setMnuCtrl(ID_CSVfileSave, csvMenu.GetSafeHmenu(), _T("Sort && Save CSV File"));

  toolBar.install();
#endif

