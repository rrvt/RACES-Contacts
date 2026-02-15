

RACEScontacts.chm : *.htm RACEScontacts.hhp RACEScontacts.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" RACEScontacts


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist RACEScontacts.chm del /F RACEScontacts.chm


$(TgtFolder)\RACEScontacts.chm : RACEScontacts.chm
  if not exist "$(MAKEDIR)\..\$(TgtFolder)" mkdir "$(MAKEDIR)\..\$(TgtFolder)"
  copy $(MAKEDIR)\RACEScontacts.chm  $(MAKEDIR)\..\$(TgtFolder)\RACEScontacts.chm


$(TgtFolder)\Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\$(TgtFolder)
  if exist RACEScontacts.chm del /F RACEScontacts.chm
  cd $(MAKEDIR)


$(TgtFolder)\Rebuild.rbd : $(TgtFolder)\Clean.cln $(TgtFolder)\RACEScontacts.chm



