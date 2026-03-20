// My ToolBar


#include "pch.h"
#include "MyToolBar.h"
#include "Resource.h"


static int NoOfButtonControls = 2;
static int NoOfButtons        = 8;



MyToolBar::MyToolBar() : menu(ID_ContactList), menu1(ID_CSVfileSave)
                                          {toolBarDim.initialize(NoOfButtonControls, NoOfButtons);}


bool MyToolBar::addButton( uint id, TCchar* caption) {

  return false;
  }


bool MyToolBar::addEditBox(uint id, int noChars)              {

  return false;
  }


CString MyToolBar::getText(uint id) {

  return _T("");
  }


#ifdef DocView

bool MyToolBar::addMenu(uint id, int idr, TCchar* caption) {

  if      (id == menu.getId())      return add(menu,     id, idr, caption);
  else if (id == menu1.getId())     return add(menu1,    id, idr, caption);

  return false;
  }


bool MyToolBar::addMenu(uint id, CCbxItem cbxItem[], int n, TCchar* caption) {

  if      (id == menu.getId())      return add(menu,     id, cbxItem, n, caption);
  else if (id == menu1.getId())     return add(menu1,    id, cbxItem, n, caption);

  return false;
  }


bool MyToolBar::addMenu(uint id, int idr, int index) {

  if (id == menu.getId())  return add(menu,     id, idr, index);
  if (id == menu1.getId()) return add(menu1,    id, idr, index);

  return false;
  }

#endif


void MyToolBar::setCboCaption(uint id, TCchar* txt) {

  }


void MyToolBar::setCboWthPrct(uint id, int percent) {

  }


void MyToolBar::setCboHeight(uint id) {
  }


void MyToolBar::dispatch(uint id) {
  }


// Manipulate tuple in the ComboBox

bool MyToolBar::addCboItem(uint id, TCchar* txt, ulongP data) {

  return false;
  }


bool MyToolBar::addCboItemSrtd(uint id, TCchar* txt, ulongP data) {

  return false;
  }


bool MyToolBar::setCurSel(uint id, int index) {

  return false;
  }


bool MyToolBar::setCurSel(uint id, TCchar* tc) {

  return false;
  }


int  MyToolBar::getCurSel(uint id) {

  return -1;
  }


bool MyToolBar::getCurSel(uint id, String& s, ulongP& data) {

  return false;
  }


ulongP MyToolBar::getData(uint id, int index) {

  return 0;
  }


int MyToolBar::find(uint id, TCchar* tc) {

  return -1;
  }



