CFLAGS+=-Wall  -std=gnu99 -O2
LDFLAGS+=`curl-config --libs sqlite3-config --libs`

TARGETS=apilogin addapi apipublish

APILoginOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../log/log.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o apilogin.o
AddAPIOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o ../log/log.o addapi.o
PublishAPIOBJ=../baseStruct/baseStruct.o ../dbrequest/dbrequest.o ../json/buf/buf.o ../json/jsmn/jsmn.o ../json/json.o ../curl/curlreq.o ../log/log.o apipublish.o

all: $(TARGETS)

clean:
	$(RM) $(TARGETS)
	$(RM) $(APILoginOBJ)
	$(RM) $(AddAPIOBJ)
	$(RM) $(PublishAPIOBJ)

apilogin: $(APILoginOBJ) apilogin.o
	$(CC) -o $@ $^ -l curl -l sqlite3

addapi: $(AddAPIOBJ) addapi.o
	$(CC) -o $@ $^ -l curl -l sqlite3

apipublish: $(PublishAPIOBJ) apipublish.o
	$(CC) -o $@ $^ -l curl -l sqlite3

.PHONY: all clean
