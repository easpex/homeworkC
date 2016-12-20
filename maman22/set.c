#include "set.h"

/*
(ARR_LEN - 1 == i) ? "\n" : " ")
*/

void print_binary(int number)
{
    if (number) {
        print_binary(number >> 1);
        putchar((number & 1) ? '1' : '0');
    }
}

void printIntSet(set *s) {
	int i;

	for(i = 0; i < ARR_LEN; i++) {
		printf("%c", s -> arr[i]);
	}
	printf("\n");
}

void printBitSet(set *p) {
	int pos;
	int i;

	for(i = 0; i < ARR_LEN; i++) {
		printf("i = %d:  ", i);
		for(pos = 0; pos < 8; pos++) {
			if( ( (p -> arr[i]) & (1 << pos)) != 0)
				printf("1");
			else
				printf("0");
		}
		printf("\n");
	}
}

void clearSet(set *s) {
	int i;
	for(i = 0; i < ARR_LEN; i++) {
		s -> arr[i] = 0;
	} 
}
