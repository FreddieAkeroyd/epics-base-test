# Example vxWorks startup file

# Following must be added for many board support packages
#cd <full path to target bin directory>

< cdCommands

#< ../nfsCommands

cd topbin
ld < exampleLibrary.munch
threadInit()
TSinit()

cd top
dbLoadDatabase("dbd/exampleApp.dbd")
registerRecordDeviceDriver(pdbbase)
dbLoadRecords("db/dbExample1.db","user=_USER_")
dbLoadRecords("db/dbExample2.db","user=_USER_,no=1,scan=1 second")
dbLoadRecords("db/dbExample2.db","user=_USER_,no=2,scan=2 second")
dbLoadRecords("db/dbExample2.db","user=_USER_,no=3,scan=5 second")

cd startup
iocInit
#seq &snctest
