CFLAGS+=-Wall  -std=gnu99 -O2
LDFLAGS+=`curl-config --libs sqlite3-config --libs`

TARGETS=routing_index initConfig

RoutingIndexOBJ=../libs/baseStruct.o ../libs/dbrequest.o ../libs/makeBuffer.o ../libs/log.o ../resources/externalLibs/jsmn.o \
				../libs/jsonParser.o ../libs/curlreq.o ../src/controllers/signUp.o ../src/controllers/login.o \
				../src/controllers/addApplications.o ../src/controllers/addSubscription.o ../src/controllers/generateApplicationKey.o \
				../src/controllers/apilogin.o ../src/controllers/addapi.o ../src/controllers/apipublish.o  ../src/routes/routing_index.o

InitConfigOBJ=../libs/baseStruct.o ../libs/dbrequest.o ../src/controllers/initConfig.o

all: $(TARGETS)

clean:
	$(RM) $(TARGETS)
	$(RM) $(RoutingIndexOBJ)
	$(RM) $(InitConfigOBJ)

all: $(TARGETS)

routing_index: $(RoutingIndexOBJ) ../src/routes/routing_index.o
	$(CC) -o $@ $^ -l curl -l sqlite3 -l fcgi -l pthread

initConfig: $(InitConfigOBJ) ../src/controllers/initConfig.o
	$(CC) -o $@ $^ -l sqlite3

.PHONY: all clean