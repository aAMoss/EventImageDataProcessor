.POSIX:
.SUFFIXES:
all: eidp

eidp: main.o config.o dataio.o process.o
	gcc -o eidp main.o config.o dataio.o process.o

main.o: main.c main.h
	gcc -c main.c

config.o: config.c config.h
	gcc -c config.c
	
dataio.o: dataio.c dataio.h
	gcc -c dataio.c

process.o: process.c process.h
	gcc -c process.c

clean:
	rm -f eidp main.o config.o dataio.o process.o
