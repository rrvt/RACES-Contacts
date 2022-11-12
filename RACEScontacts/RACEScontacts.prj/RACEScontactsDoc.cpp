// RACEScontactsDoc.cpp : implementation of the RACEScontactsDoc class


#include "pch.h"
#include "RACEScontactsDoc.h"
#include "Database.h"
#include "ExtraResource.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Options.h"
#include "Resource.h"
#include "RACEScontacts.h"
#include "RACEScontactsView.h"
#include "ToolBar.h"



static TCchar* FileSection = _T("FileSection");
static TCchar* DBFileKey   = _T("DBfile");
static TCchar* OutputKey   = _T("Output");


// RACEScontactsDoc

IMPLEMENT_DYNCREATE(RACEScontactsDoc, CDoc)

BEGIN_MESSAGE_MAP(RACEScontactsDoc, CDoc)
  ON_COMMAND(ID_OpenDatabase,  &openDatabase)

  ON_COMMAND(ID_ContactList,   &onSortByName)               //ID_SortByName
  ON_COMMAND(ID_SortByName,    &onSortByName)               //ID_SortByFCC
  ON_COMMAND(ID_SortByFCC,     &onSortByFCC)

  ON_COMMAND(ID_CSVfileSave,   &csvSaveByName)
  ON_COMMAND(ID_CSVByName,     &csvSaveByName)
  ON_COMMAND(ID_CSVByFCC,      &csvSaveByFCC)

  ON_COMMAND(ID_File_Save,     &OnFileSave)
  ON_COMMAND(ID_Options,       &OnOptions)
END_MESSAGE_MAP()


// RACEScontactsDoc construction/destruction

RACEScontactsDoc::RACEScontactsDoc() noexcept : dataSource(NotePadSrc), storeSort(NilSort) { }


RACEScontactsDoc::~RACEScontactsDoc() { }


void RACEScontactsDoc::initialLoad() {getDBpath();  loadDatabase();}


void RACEScontactsDoc::openDatabase() {
PathDlgDsc dsc;

  notePad.clear();

  getDBpath();

  dsc(_T("Database"), path, _T("accdb"), _T("*.accdb"));

  if (setOpenPath(dsc)) loadDatabase();
  }


void RACEScontactsDoc::getDBpath() {iniFile.read(FileSection, DBFileKey, path, _T(""));}


void RACEScontactsDoc::loadDatabase() {

  if (!database.load(path)) return;

  dbPath = path;   iniFile.write(FileSection, DBFileKey, path);

  store.name = _T("Contact List");   store.dt.getToday();   store.load();  display(NotePadSrc);
  }


void RACEScontactsDoc::OnOptions() {options(view());  view()->setOrientation(options.orient);}


void RACEScontactsDoc::onSortByName() {storeSort = NameSort;    store.sortByName();   display(StoreSrc);}


void RACEScontactsDoc::onSortByFCC()  {storeSort = FCCsort;   store.sortByFCC();    display(StoreSrc);}


void RACEScontactsDoc::display(DataSource ds) {dataSource = ds; invalidate();}


void RACEScontactsDoc::OnFileSave() {
String     name = storeSort == FCCsort ? _T("ContactListByFCC") : _T("ContactListByName");
PathDlgDsc dsc;

  dataSource = StoreSrc;   name = readOutputPath() + name;

  dsc(_T("Contact List"), name, _T("txt"), _T("*.txt"));

  if (setSaveAsPath(dsc)) {OnSaveDocument(path);   saveOutputPath(path);}
  }


void RACEScontactsDoc::csvSaveByName() {storeSort = NameSort;    store.sortByName();
String     s = readOutputPath() + _T("ContactListByName");
PathDlgDsc dsc(_T("Contact List"), s, _T("csv"), _T("*.csv"));

  dataSource = StoreCSVSrc;

  if (setSaveAsPath(dsc)) {OnSaveDocument(path);   saveOutputPath(path);}
  }


void RACEScontactsDoc::csvSaveByFCC() {storeSort = FCCsort;   store.sortByFCC();
String     s = readOutputPath() + _T("ContactListByFCC");
PathDlgDsc dsc(_T("Contact List"), s, _T("csv"), _T("*.csv"));

  dataSource = StoreCSVSrc;

  if (setSaveAsPath(dsc)) {OnSaveDocument(path);   saveOutputPath(path);}
  }


String RACEScontactsDoc::readOutputPath()
                        {iniFile.read(FileSection, OutputKey, outputPath, _T(""));   return outputPath;}


void RACEScontactsDoc::saveOutputPath(TCchar* path)
                    {outputPath = ::getPath(path);   iniFile.write(FileSection, OutputKey, outputPath);}


// UglyDoc serialization

void RACEScontactsDoc::serialize(Archive& ar) {

  if (ar.isStoring())
    switch(dataSource) {
      case NotePadSrc : notePad.archive(ar); return;
      case StoreSrc   : if (storeSort == FCCsort) store.sortByFCC();
                        else                      store.sortByName();

                        store.store(ar);     return;
      case StoreCSVSrc: store.storeCSV(ar);  return;
      default         :                      return;
      }

  else
    switch(dataSource) {
      case FontSrc  :
      default       : return;
      }
  }


// RACEScontactsDoc diagnostics

#ifdef _DEBUG
void RACEScontactsDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void RACEScontactsDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

