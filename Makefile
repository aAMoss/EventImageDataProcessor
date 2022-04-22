.POSIX:
.SUFFIXES:
all: eidp
eidp: main.o config.o
    cc -o eidp main.o config.o
main.o: main.c main.h
    cc -c main.c
config.o: config.c config.h
    cc -c config.c

clean:
    rm -f eidp main.o config.o



