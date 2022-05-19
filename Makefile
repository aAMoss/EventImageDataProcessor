.POSIX:
.SUFFIXES:
all: eidp tmda



eidp: eidp.o dataio.o process.o features.o pbfe.o idfe.o
	gcc -o eidp eidp.o dataio.o process.o features.o pbfe.o idfe.o


eidp.o: eidp.c eidp.h
	gcc -c eidp.c
	
dataio.o: dataio.c dataio.h
	gcc -c dataio.c

process.o: process.c process.h
	gcc -c process.c
	
features.o: features.c features.h
	gcc -c features.c

pbfe.o: pbfe.c pbfe.h
	gcc -c pbfe.c

idfe.o: idfe.c idfe.h
	gcc -c idfe.c
	
	

tmda: tmda.o procdataio.o
	gcc -o tmda tmda.o procdataio.o
	
	
tmda.o: tmda.c tmda.h
	gcc -c tmda.c
	
procdataio.o: procdataio.c procdataio.h
	gcc -c procdataio.c
	
	
	
clean:
	rm -f eidp eidp.o dataio.o process.o features.o pbfe.o idfe.o
	rm -f tmda tmda.o
