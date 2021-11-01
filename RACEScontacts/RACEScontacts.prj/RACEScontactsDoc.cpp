// RACEScontactsDoc.cpp : implementation of the RACEScontactsDoc class


#include "stdafx.h"
#include "RACEScontactsDoc.h"
#include "DBtables.h"
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

RACEScontactsDoc::RACEScontactsDoc() noexcept : dataSource(NotePadSrc), storeSort(NilSort) {
  pathDlgDsc = PathDlgDsc(_T("Contact List"), _T(""), _T("txt"), _T("*.txt"));
  }

RACEScontactsDoc::~RACEScontactsDoc() { }


void RACEScontactsDoc::openDatabase() {
String title;
String ext;

  notePad.clear();

  getDBpath();

  if (getPathDlg(_T("Database"), databasePath, _T("accdb"), _T("*.accdb"), databasePath))
                                       iniFile.writeString(FileSection, DBFileKey, databasePath);
  loadDatabase();
  }


void RACEScontactsDoc::getDBpath() {iniFile.readString(FileSection, DBFileKey, databasePath, _T(""));}


void RACEScontactsDoc::loadDatabase() {

  dbTables.load(databasePath);

  store.name = _T("Contact List");
  store.dt.getToday();

  store.load();  display(NotePadSrc);
  }


void RACEScontactsDoc::OnOptions() {options(view());  view()->setOrientation(options.orient);}




void RACEScontactsDoc::onSortByName() {storeSort = NameSort;    store.sortByName();   display(StoreSrc);}


void RACEScontactsDoc::onSortByFCC()  {storeSort = FCCsort;   store.sortByFCC();    display(StoreSrc);}


void RACEScontactsDoc::display(DataSource ds) {dataSource = ds; invalidate();}


void RACEScontactsDoc::OnFileSave() {
String name = storeSort == FCCsort ? _T("ContactListByFCC") : _T("ContactListByName");

  name = readOutputPath() + name;

  pathDlgDsc = PathDlgDsc(_T("Contact List"), name, _T("txt"), _T("*.txt"));

  dataSource = StoreSrc;

  if (setSaveAsPath(pathDlgDsc)) {OnSaveDocument(path);   saveOutputPath(path);}
  }


void RACEScontactsDoc::csvSaveByName() {storeSort = NameSort;    store.sortByName();
String s = readOutputPath() + _T("ContactListByName");

  pathDlgDsc = PathDlgDsc(_T("Contact List"), s, _T("csv"), _T("*.csv"));

  dataSource = StoreCSVSrc;

  if (setSaveAsPath(pathDlgDsc)) {OnSaveDocument(path);   saveOutputPath(path);}
  }


void RACEScontactsDoc::csvSaveByFCC() {storeSort = FCCsort;   store.sortByFCC();
String s = readOutputPath() + _T("ContactListByFCC");

  pathDlgDsc = PathDlgDsc(_T("Contact List"), s, _T("csv"), _T("*.csv"));

  dataSource = StoreCSVSrc;

  if (setSaveAsPath(pathDlgDsc)) {OnSaveDocument(path);   saveOutputPath(path);}
  }


String RACEScontactsDoc::readOutputPath()
                  {iniFile.readString(FileSection, OutputKey, outputPath, _T(""));   return outputPath;}


void RACEScontactsDoc::saveOutputPath(TCchar* path)
                 {outputPath = ::getPath(path);   iniFile.writeString(FileSection, OutputKey, outputPath);}


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







#ifdef Examples
void RACEScontactsDoc::OnFileOpen() {

  notePad.clear();   dataSource = StoreSrc;

  pathDlgDsc = PathDlgDsc(_T("Ugly Example"), pathDlgDsc.name, _T("txt"), _T("*.txt"));

  if (!setPath(pathDlgDsc)) return;

  pathDlgDsc.name = getMainName(path);

  if (!OnOpenDocument(path)) messageBox(_T(" Not Loaded!"));

#ifdef Examples
  store.setName(pathDlgDsc.name);
#endif

  display(StoreSrc);
  }
#endif
#ifdef Examples
#include "Store.h"
#endif
#ifdef Examples
  ON_COMMAND(ID_Test,          &OnTest)
  ON_COMMAND(ID_SelDataStr,    &displayDataStore)

  ON_COMMAND(ID_MyBtn,         &myButton)

  ON_CBN_SELCHANGE(ID_CB,      &OnComboBoxChng)
  ON_COMMAND(      ID_CB,      &OnComboBoxChng)

  ON_COMMAND(ID_EditBox,       &OnTBEditBox)
  ON_COMMAND(ID_MyBtn1,        &onOption1)
  ON_COMMAND(ID_Option1,       &onOption1)
  ON_COMMAND(ID_Option2,       &onOption2)
  ON_COMMAND(ID_Option3,       &onOption3)
  ON_COMMAND(ID_Btn2,          &onOption21)
  ON_COMMAND(ID_Option21,      &onOption21)
  ON_COMMAND(ID_Option22,      &onOption22)
  ON_COMMAND(ID_Option23,      &onOption23)
#endif
#ifdef Examples

static TCchar* cbText[] = {_T("Zeta"),
                           _T("Beta"),
                           _T("Alpha"),
                           _T("Omega"),
                           _T("Phi"),
                           _T("Mu"),
                           _T("Xi"),
                           _T("Omicron"),
                           _T("Pi"),
                           _T("Rho"),
                           _T("Sigma"),
                           _T("Nu"),
                           _T("Kappa"),
                           _T("Iota")
                           };


void RACEScontactsDoc::myButton() {
TBComboBox* cb = TBComboBox::get(ID_CB);
int n = noElements(cbText);
int i;
int x;

  dataSource = NotePadSrc;

  notePad << _T("My Button") << nCrlf;

  if (!cb) {invalidate();  return;}

//  cb->SetText(_T("Greeks"));

  for (i = 0; i < n; i++) if (cb->findExact(cbText[i]) < 0) {

    x = cb->AddSortedItem(cbText[i], i);                           //AddSortedItem

    String s;  s.format(_T("%02i: "), i);

    notePad << s << _T("Pos = ") << x << _T(". Added ") << cbText[i] << nCrlf;
    }

  cb->SelectItem(-1);
  cb->SetText(_T("Greeks"));

  notePad << _T("Greeks") << nCrlf;  display(NotePadSrc);
  }


void RACEScontactsDoc::OnComboBoxChng() {
TBComboBox* cb = TBComboBox::get(ID_CB);
int        i;
String     s;
int        x;
MainFrame* mf = theApp.mainFrm();

  if (!cb)   return;
  i  = cb->GetCurSel();    if (i < 0) return;
  s  = cb->GetItem(i);
  x  = cb->GetItemData(i);   mf->SetFocus();

  notePad << _T("On Change, Item = ") << s << _T(", Data = ") << x << nCrlf;

  display(NotePadSrc);
  }



void RACEScontactsDoc::OnTBEditBox() {
TBEditBox*  eb = TBEditBox::get(ID_EditBox);   if (!eb) return;
String      s  = eb->GetContentsAll(ID_EditBox);

  notePad << s << nCrlf;   display(NotePadSrc);
  }


void RACEScontactsDoc::myButton1() {
TBEditBox* eb = TBEditBox::get(ID_EditBox);   if (!eb) return;
String     s  = eb->GetContentsAll(ID_EditBox);

  notePad << s << nCrlf;   display(NotePadSrc);
  }


void RACEScontactsDoc::onOption1() {notePad << _T("Option 1") << nCrlf; wholePage(); display(NotePadSrc);}
void RACEScontactsDoc::onOption2() {notePad << _T("Option 2") << nCrlf; display(NotePadSrc);}
void RACEScontactsDoc::onOption3() {notePad << _T("Option 3") << nCrlf; display(NotePadSrc);}


void RACEScontactsDoc::onOption21() {notePad << _T("Option 21") << nCrlf; display(NotePadSrc);}
void RACEScontactsDoc::onOption22() {notePad << _T("Option 22") << nCrlf; display(NotePadSrc);}
void RACEScontactsDoc::onOption23() {notePad << _T("Option 23") << nCrlf; display(NotePadSrc);}


void RACEScontactsDoc::OnTestEditBoxes() {display(NotePadSrc);}


// RACEScontactsDoc commands


void RACEScontactsDoc::OnTest() {
int n;

  notePad.clear();  theApp.setTitle(_T("My Test"));

  notePad << nFFace(_T("Windsor BT")) << nFSize(14.5) << nBold;

  notePad << _T("Hello World") << nCrlf;

  notePad << nFont << nFont << nFont;

  n = options.orient == Landscape ? 10 : 8;

  notePad << nFFace(_T("Courier New")) << nFSize(12.0);   testLine(n);   notePad << nFont << nFont;

  testLine(n);   display(NotePadSrc);
  }


void RACEScontactsDoc::testLine(int n) {
int i;

  for (i = 0; i < n; i++) {

    if (!i) notePad << _T('|'); else notePad << i;

    notePad << _T("123456789");
    }

  notePad << _T('|') << nCrlf;
  }


void RACEScontactsDoc::wholePage() {
int    i;
int    j;
String s;

  notePad << nSetRTab(4) << nSetTab(6) << nSetTab(8) << nSetRTab(12) << nSetTab(14);

  for (i = 0; i < 100; i++) {
    s.format(_T("%3i:"), i);

    notePad << nTab << s << nTab << _T("X") << nTab << _T("Y") << nTab << i << nTab;

    for (j = i+1; j < i+68; j++) {s.format(_T("%i"), j);   s = s.substr(s.length()-1);  notePad << s;}

    notePad << nCrlf;
    }
  }


void RACEScontactsDoc::displayDataStore() {display(StoreSrc);}

#endif

