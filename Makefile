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



all: game
game: graphics.o physics.o input.o
    cc -o game graphics.o physics.o input.o
graphics.o: graphics.c graphics.h
    cc -c graphics.c
physics.o: physics.c physics.h
    cc -c physics.c
input.o: input.c input.h graphics.h physics.h
    cc -c input.c
clean:
    rm -f game graphics.o physics.o input.o
