#include "set.h"
set A;
int main(int argc, char * argv[]) {
	
	set *pset = &A;
	clearSet(pset);

	A.arr[4] = 4;
	
	pset -> arr[0] = 5;
	pset -> arr[2] = 2;

	printf("pset -> arr[0] = %d\n", pset -> arr[2]);
	printf("A.arr[5] = %d\n", A.arr[0]);

	printf("\n");
	
	printIntSet(pset);

	printBitSet(pset);
	return 0;
}

