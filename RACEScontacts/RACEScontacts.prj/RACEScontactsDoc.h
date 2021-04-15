// RACEScontactsDoc.h : interface of the RACEScontactsDoc class


#pragma once
#include "CDoc.h"
#include "MainFrame.h"
#include "Store.h"
#include "TBComboBox.h"
#include "TBEditBox.h"


enum DataSource {NotePadSrc, StoreSrc, StoreCSVSrc, FontSrc};

class RACEScontactsDoc : public CDoc {

PathDlgDsc  pathDlgDsc;

DataSource  dataSource;
StoreSort   storeSort;


String databasePath;
String outputPath;

protected: // create from serialization only

  RACEScontactsDoc() noexcept;
  DECLARE_DYNCREATE(RACEScontactsDoc)

public:

  DataSource dataSrc() {return dataSource;}
  void       display(DataSource ds);

  virtual void serialize(Archive& ar);

// Implementation
public:
  virtual ~RACEScontactsDoc();

  void     getDBpath();
  void     loadDatabase();


#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

//  void   testLine(int n);
//  void   wholePage();
  String readOutputPath();
  void   saveOutputPath(TCchar* path);

// Generated message map functions

protected:

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void openDatabase();
  afx_msg void onSortByName();
  afx_msg void onSortByFCC();
  afx_msg void OnFileSave();

  afx_msg void csvSaveByName();
  afx_msg void csvSaveByFCC();

  afx_msg void OnOptions();
  };




#ifdef Examples
  afx_msg void OnTest();
  afx_msg void displayDataStore();
  afx_msg void myButton();

  afx_msg void OnComboBoxChng();

  afx_msg void OnTBEditBox();
  afx_msg void myButton1();
  afx_msg void onOption1();
  afx_msg void onOption2();
  afx_msg void onOption3();
  afx_msg void onOption21();
  afx_msg void onOption22();
  afx_msg void onOption23();
  afx_msg void OnTestEditBoxes();
#endif

