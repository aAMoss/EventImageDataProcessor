.POSIX:
.SUFFIXES:
all: eidp
eidp: main.o config.o dataio.o
	gcc -o eidp main.o config.o dataio.o
main.o: main.c main.h
	gcc -c main.c
config.o: config.c config.h
	gcc -c config.c

dataio.o: dataio.c dataio.h
	gcc -c dataio.c
clean:
	rm -f eidp main.o config.o dataio.o
