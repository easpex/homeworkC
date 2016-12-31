CFLAGS = -c -g -Wall -pedantic -ansi

all: set_prog

set_prog: set.o main.o
	gcc set.o main.o -o set_prog

set.o: set.c
	gcc set.c $(CFLAGS)

main.o: main.c
	gcc main.c $(CFLAGS)