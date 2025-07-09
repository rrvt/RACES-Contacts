

RACEScontacts.chm : *.htm RACEScontacts.hhp RACEScontacts.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" RACEScontacts


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist RACEScontacts.chm del /F RACEScontacts.chm


Release/RACEScontacts.chm : RACEScontacts.chm
  copy $(MAKEDIR)\RACEScontacts.chm  $(MAKEDIR)\..\Release\RACEScontacts.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  if exist RACEScontacts.chm del /F RACEScontacts.chm
  cd $(MAKEDIR)


Debug/RACEScontacts.chm : RACEScontacts.chm
  copy $(MAKEDIR)\RACEScontacts.chm  $(MAKEDIR)\..\Debug\RACEScontacts.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  if exist RACEScontacts.chm del /F RACEScontacts.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/RACEScontacts.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/RACEScontacts.chm


