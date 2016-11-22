CFLAGS = -c -Wall -pedantic -ansi

all: my_scalar con

my_scalar: my_scalar.o
	gcc my_scalar.o -o my_scalar

my_scalar.o: my_scalar.c
	gcc my_scalar.c $(CFLAGS)

con: con.o
	gcc con.o -o con

con.o: con.c
	gcc con.c $(CFLAGS)