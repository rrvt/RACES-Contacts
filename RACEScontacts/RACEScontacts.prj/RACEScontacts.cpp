// RACEScontacts.cpp : Defines the class behaviors for the application.


#include "pch.h"
#include "RACEScontacts.h"
#include "AboutDlg.h"
#include "IniFile.h"
#include "MainFrame.h"
#include "NotePad.h"
#include "RACEScontactsDoc.h"
#include "RACEScontactsView.h"
#include "ResourceExtra.h"


RACEScontacts theApp;                       // The one and only RACEScontacts object
IniFile       iniFile;


// RACEScontacts

BEGIN_MESSAGE_MAP(RACEScontacts, CWinAppEx)
  ON_COMMAND(ID_File_New,         &CWinAppEx::OnFileNew)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &OnFilePrintSetup)
  ON_COMMAND(ID_Help,             &OnHelp)
  ON_COMMAND(ID_App_About,        &OnAppAbout)
END_MESSAGE_MAP()


// RACEScontacts initialization

BOOL RACEScontacts::InitInstance() {

  CWinAppEx::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  notePad.clear();

  SetRegistryKey(appID);

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  // serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(RACEScontactsDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(RACEScontactsView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

//  EnableShellOpen(); RegisterShellFileTypes(TRUE);       // Enable DDE Execute open

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("RACES Contact List")); setTitle(_T("Build List"));

  view()->setFont(_T("Arial"), 12.0);

  doc()->initialLoad();

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }


int RACEScontacts::ExitInstance() {

#ifdef DebugMemoryLeaks
  _CrtDumpMemoryLeaks();
#endif

  return CApp::ExitInstance();
  }


void RACEScontacts::OnHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void RACEScontacts::OnAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}

