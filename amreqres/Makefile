CFLAGS+=-Wall  -std=gnu99 -O2
LDFLAGS+=`curl-config --libs sqlite3-config --libs`

TARGETS=signup login addApplications addSubscription generateApplicationKey getAppDetails

SignupOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o signup.o
LoginOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o login.o
AddAppOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o addApplications.o
AddSubsOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o addSubscription.o
GenKeyOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o generateApplicationKey.o
GetAppDetailsOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o getAppDetails.o

all: $(TARGETS)

clean:
	$(RM) $(TARGETS)
	$(RM) $(SignupOBJ)
	$(RM) $(LoginOBJ)
	$(RM) $(AddAppOBJ)
	$(RM) $(AddSubsOBJ)
	$(RM) $(GenKeyOBJ)
	$(RM) $(GetAppDetailsOBJ)

all: $(TARGETS)

signup: $(SignupOBJ) signup.o
	$(CC) -o $@ $^ -l curl -l sqlite3

login: $(LoginOBJ) login.o
	$(CC) -o $@ $^ -l curl -l sqlite3

addApplications: $(AddAppOBJ) addApplications.o
	$(CC) -o $@ $^ -l curl -l sqlite3

addSubscription: $(AddSubsOBJ) addSubscription.o
	$(CC) -o $@ $^ -l curl -l sqlite3

generateApplicationKey: $(GenKeyOBJ) generateApplicationKey.o
	$(CC) -o $@ $^ -l curl -l sqlite3

getAppDetails: $(GetAppDetailsOBJ) getAppDetails.o
	$(CC) -o $@ $^ -l curl -l sqlite3

.PHONY: all clean
