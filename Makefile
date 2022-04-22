.POSIX:
.SUFFIXES:
all: eidp
eidp: main.o config.o
	gcc -o eidp main.o config.o
main.o: main.c main.h
	gcc -c main.c
config.o: config.c config.h
	gcc -c config.c
clean:
	rm -f eidp main.o config.o
