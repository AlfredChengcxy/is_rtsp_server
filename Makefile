CC= gcc

CFLAGS:= -L/usr/local/lib/ -I/usr/local/include/ -lev
CFLAGS+= $(CFLAGS) -g
CFLAGS+= -I./
CFLAGS+= -lpthread
CFLAGS+= $(CFLAGS) `pkg-config --libs --cflags glib-2.0 gthread-2.0`

TARGET_C=$(wildcard *.c)
TARGET_H=$(wildcard *.h)
#TARGET_C+= $(wildcard ./media/*.c)
TARGET_O=$(patsubst %.c,%.o,$(TARGET_C))
#TARGET=$(subst .c,,$(TARGET_C))
TARGET=$(patsubst %.c,%,$(TARGET_C))

all: rtsp_server

rtsp_server:$(TARGET_O) $(TARGET_H)
	$(CC) -o $@ $^ $(CFLAGS)

%.o:%.c
	$(CC) -c $< $(CFLAGS)

.PHONY : clean
clean:
	@rm -fvr $(TARGET_O)
	@rm -fvr rtsp_server
