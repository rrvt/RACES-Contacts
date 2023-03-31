// RACEScontacts.h : main header file for the RACEScontacts application

#pragma once
#include "CApp.h"


class RACEScontactsDoc;
class RACEScontactsView;
class MainFrame;


// RACEScontacts:
// See RACEScontacts.cpp for the implementation of this class

class RACEScontacts : public CApp {
public:

               RACEScontacts() noexcept : CApp(this) { }

  virtual BOOL InitInstance();
  virtual int  ExitInstance();

          RACEScontactsDoc*  doc()   {return (RACEScontactsDoc*)  CApp::getDoc();}
          RACEScontactsView* view()  {return (RACEScontactsView*) CApp::getView();}
          MainFrame*       mainFrm() {return (MainFrame*) m_pMainWnd;}

  DECLARE_MESSAGE_MAP()

  afx_msg void OnAppAbout();
  afx_msg void OnHelp();
  };


extern RACEScontacts theApp;

inline void         invalidate() {theApp.invalidate();}
inline RACEScontactsDoc*  doc()  {return theApp.doc();}
inline RACEScontactsView* view() {return theApp.view();}

