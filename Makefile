.POSIX:
.SUFFIXES:
all: eidp tmda

eidp: eidp.o dataio.o process.o features.o
	gcc -o eidp eidp.o dataio.o process.o features.o

eidp.o: eidp.c eidp.h
	gcc -c eidp.c
	
dataio.o: dataio.c dataio.h
	gcc -c dataio.c

process.o: process.c process.h
	gcc -c process.c
	
features.o: features.c features.h
	gcc -c features.c

tmda: tmda.o
	gcc -o tmda tmda.o
	
tmda.o: tmda.c tmda.h
	gcc -c tmda.c
	
	
clean:
	rm -f eidp eidp.o dataio.o process.o features.o
	rm -f tmda tmda.o
