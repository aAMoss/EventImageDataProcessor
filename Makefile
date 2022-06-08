.POSIX:
.SUFFIXES:
all: eidp tmda

eidp:	eidp.c eidp.h dataio.c dataio.h process.c process.h raw.c raw.h pbfe.c pbfe.h idfe.c idfe.h
	gcc -o eidp eidp.c dataio.c process.c raw.c pbfe.c idfe.c

tmda:	tmda.c tmda.h procdataio.c procdataio.h
	gcc -o tmda tmda.c procdataio.c
	
	
#eidp: eidp.o dataio.o process.o raw.o pbfe.o idfe.o
#	gcc -o eidp eidp.o dataio.o process.o raw.o pbfe.o idfe.o


#eidp.o: eidp.c eidp.h
#	gcc -c eidp.c
	
#dataio.o: dataio.c dataio.h
#	gcc -c dataio.c

#process.o: process.c process.h
#	gcc -c process.c
	
#raw.o: raw.c raw.h
#	gcc -c raw.c

#pbfe.o: pbfe.c pbfe.h
#	gcc -c pbfe.c

#idfe.o: idfe.c idfe.h
#	gcc -c idfe.c
	
	

#tmda: tmda.o procdataio.o
#	gcc -o tmda tmda.o procdataio.o
	
	
#tmda.o: tmda.c tmda.h
#	gcc -c tmda.c
	
#procdataio.o: procdataio.c procdataio.h
#	gcc -c procdataio.c
	
	
	
clean:
	rm -f eidp eidp.o dataio.o process.o raw.o pbfe.o idfe.o
	rm -f tmda tmda.o
