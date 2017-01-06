CFLAGS = -c -Wall -pedantic -ansi

all: min_call

min_call: min_call.o
	gcc min_call.o -o min_call

min_call.o: min_call.c
	gcc min_call.c $(CFLAGS)