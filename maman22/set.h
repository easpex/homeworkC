#include <stdio.h>
#include <stdlib.h>
#define ARR_LEN 16

typedef struct set {
	char arr[ARR_LEN];
} set;

void print_binary(int n);
void printIntSet(set *s);
void printBitSet(set *p);
void clearSet(set *s);
