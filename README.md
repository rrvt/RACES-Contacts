# RACES Contact List

Load the RACES Database into the application.  The application can then produce sorted
contact lists, sorted by FCC Callsign or by name, last name first.  The output may be
as a pdf file (if print to pdf is available), as a text (".txt") file, or as a Comma
Separated Value (CSV) file suitable for loading into Excel.

## Getting Started

The application may be executed directly out of the Release directory or installed in Windows as an
application.

## Prerequisites

Windows 7 or above.  visual Studio 2017 or above.  WIX Installer.

Microsoft HTML Help Workshop (last version).  This is the link to the last version:
```
https://docs.microsoft.com/en-us/previous-versions/windows/desktop/htmlhelp/microsoft-html-help-downloads
```
Access to the RACES database.

A version of the Data Access Object dynamic library must be on your system.  The library module,
DAOAccess.h, contains the following lines (which you may have to change):
```
#import <C:\Program Files (x86)\Microsoft Office\root\Office16\ACEDAO.DLL> rename(_T("EOF"), _T("DaoEof"))
using namespace DAO;
```
Here is an explanation of DAO:
```
   https://en.wikipedia.org/wiki/Data_access_object
```

## Built With

Slickedit is used for all edits, Visual Studio 2017 with various additions (Wix being one) is used to
build and debug.  The old fashion Help Workshop is used to compile the help file and an old copy of
Dreamweaver is used to construct the html files used in the Help Workshop.

This work was built with Unicode as the character implementation.

My current operating system is Windows 7 and I have little interest in moving to Windows 10 until it
appears to be stable.  In April 2021 it still does not appear stable.

## Installing

The msi file will install the application.

## Updates

### Update 12/26/24

Split the library into DocLib and Library where DocLib supports the MFC Document/Library App
projects and Library has support classes and supports the Dialog Apps with only one class.

### Update 8/7/24

Library update.

### Update 6/29//24

Add MIT License to installation.

### Update 6/14/24

Fix WinPos.

### Update 4/15/24

Add MyToolBar class to deal with the differences between Doc/View and Dialog Box Toolbars.

### Update 2/17/24

Reorganized the Library so that it compiles once into Debug and Release directories under the Library
directory.

### Update 1/7/24

Library and other changes.

### Update 12/25/23

Modify ExpandableP and subsequent ripple.

### Update 3/30/23

Library and application updates.

### Update 11/11/22

Update help file icons.  Some internal changes related to loading and storing data.

Also replaced stdafx.h with pch.h/framework.h.

### Update 10/24/22

Add logic to keep track of window position and size.  Update the toolbar background.

### Update 8/4/22

Minor Library Updates.

### Update 4/15/22

Big adventure in February when I started moving to a new Win11 and Visual Studio 2022.  I now
feel that this version is working in the new environment.  There were several changes made to the app
in order to compile properly on VS22.

### Update 01/31/22

Updates to the library, mostly about the toolbar, but also NewAllocator, and a minor addition to
Expandable.

Also scrubbed the project files to remove all references to precompiled header files which I turned off
in VS17.  Unfortnately VS does not remove all references and pch files kept cropping up.  Not only does
that slow down the compiler but the files are large...

### Update 12/21/21

While creating a template for a dialog box only application with a toolbar the Library was added to and
changed to hopefully simplify toolbar creation.  This version of the toolbar includes buttons, edit boxes,
combo boxes and drop down menus as well as the traditional 16x15 icons.

The two toolbar drop down menus have been updated.

### Update 11/13/21

But the major changes are in the library:

  - Expandable and ExpandableP -- moved the functions out of the class to make the compilation smaller,
also fixed one bug (or feature) in the ExpandableP insert sorted function that would throw out entries
that were already in in the array.
  - FileIO -- Changed the type of path from "String&" to "TCchar*".  It turns out that automatic
conversion from String to TCchar* is easy, but the reverse is is not easy.  Also added a function to
get the length of a file given a path.
  - FineName -- Added a function to get the directory name of from a path
  - NewAllocator -- Corrected the debug dependency from if to ifdef
  - ToolBar -- Added data for drop down menus

### Update 10/31/21

Changed Resources (i.e. xxx.rc data) access so that it will work with a dll.  Changed the logic in the
About Box code.  Some other library changes.  Some corresponding changes in the application.

### Update 5/21/21

Added a clear function to all database so that load may be performed multiple time with different
databases.

## Authors

Robert R. Van Tuyl, K6RWY

Contact:  romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details


