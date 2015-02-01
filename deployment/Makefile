CFLAGS+=-Wall  -std=gnu99 -O2
LDFLAGS+=`curl-config --libs sqlite3-config --libs`

TARGETS=signup login addApplications addSubscription generateApplicationKey getAppDetails apilogin addapi apipublish

SignupOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o ../amreqres/signup.o
LoginOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o ../amreqres/login.o
AddAppOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o ../amreqres/addApplications.o
AddSubsOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o ../amreqres/addSubscription.o
GenKeyOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o ../amreqres/generateApplicationKey.o
GetAppDetailsOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o ../amreqres/getAppDetails.o
APILoginOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o ../apipublishreqres/apilogin.o
AddAPIOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o ../apipublishreqres/addapi.o
PublishAPIOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o ../apipublishreqres/apipublish.o

all: $(TARGETS)

clean:
	$(RM) $(TARGETS)
	$(RM) $(SignupOBJ)
	$(RM) $(LoginOBJ)
	$(RM) $(AddAppOBJ)
	$(RM) $(AddSubsOBJ)
	$(RM) $(GenKeyOBJ)
	$(RM) $(GetAppDetailsOBJ)
	$(RM) $(APILoginOBJ)
	$(RM) $(AddAPIOBJ)
	$(RM) $(PublishAPIOBJ)

all: $(TARGETS)

signup: $(SignupOBJ) ../amreqres/signup.o
	$(CC) -o $@ $^ -l curl -l sqlite3

login: $(LoginOBJ) ../amreqres/login.o
	$(CC) -o $@ $^ -l curl -l sqlite3

addApplications: $(AddAppOBJ) ../amreqres/addApplications.o
	$(CC) -o $@ $^ -l curl -l sqlite3

addSubscription: $(AddSubsOBJ) ../amreqres/addSubscription.o
	$(CC) -o $@ $^ -l curl -l sqlite3

generateApplicationKey: $(GenKeyOBJ) ../amreqres/generateApplicationKey.o
	$(CC) -o $@ $^ -l curl -l sqlite3

getAppDetails: $(GetAppDetailsOBJ) ../amreqres/getAppDetails.o
	$(CC) -o $@ $^ -l curl -l sqlite3

apilogin: $(APILoginOBJ) ../apipublishreqres/apilogin.o
	$(CC) -o $@ $^ -l curl -l sqlite3

addapi: $(AddAPIOBJ) ../apipublishreqres/addapi.o
	$(CC) -o $@ $^ -l curl -l sqlite3

apipublish: $(PublishAPIOBJ) ../apipublishreqres/apipublish.o
	$(CC) -o $@ $^ -l curl -l sqlite3

.PHONY: all clean
