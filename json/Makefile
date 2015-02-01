CFLAGS+=-Wall  -std=gnu99 -O2
LDFLAGS+=`curl-config --libs`

TARGETS=twitter github
OBJS=./buf/buf.o ../log/log.o json.o ./jsmn/jsmn.o

all: $(TARGETS) .gitignore

clean:
	$(RM) $(TARGETS)
	$(RM) $(OBJS)

twitter: $(OBJS) twitter.o
	$(CC) -o $@ $^ $(LDFLAGS)

github: $(OBJS) github.o
	$(CC) -o $@ $^ $(LDFLAGS) 

.PHONY: all clean
