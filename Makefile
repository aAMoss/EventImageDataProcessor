.POSIX:
.SUFFIXES:
all: eidp

eidp: main.o dataio.o process.o
	gcc -o eidp main.o dataio.o process.o

main.o: main.c main.h
	gcc -c main.c
	
dataio.o: dataio.c dataio.h
	gcc -c dataio.c

process.o: process.c process.h
	gcc -c process.c

clean:
	rm -f eidp main.o dataio.o process.o
