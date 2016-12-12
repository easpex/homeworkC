CFLAGS = -c -Wall -pedantic -ansi

all: summary

summary: summary.o
	gcc summary.o -o summary

summary.o: summary.c
	gcc summary.c $(CFLAGS)