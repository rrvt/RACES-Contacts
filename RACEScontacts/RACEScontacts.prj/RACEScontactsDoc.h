// RACEScontactsDoc.h : interface of the RACEScontactsDoc class


#pragma once
#include "CDoc.h"
#include "MainFrame.h"
#include "Store.h"
#include "TBComboBox.h"
#include "TBEditBox.h"


enum DataSource {NotePadSrc, StoreSrc, StoreCSVSrc, FontSrc};

class RACEScontactsDoc : public CDoc {

DataSource  dataSource;
StoreSort   storeSort;


String      dbPath;
String      outputPath;

protected: // create from serialization only

  RACEScontactsDoc() noexcept;
  DECLARE_DYNCREATE(RACEScontactsDoc)

public:

  void       initialLoad();

  DataSource dataSrc() {return dataSource;}
  void       display(DataSource ds);

  virtual void serialize(Archive& ar);

// Implementation
public:
  virtual ~RACEScontactsDoc();

  void     getDBpath();


#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  void   loadDatabase();

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
  };

