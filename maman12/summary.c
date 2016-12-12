#include <stdio.h>
#include <stdlib.h>
#define MAX_ARR_SIZE 1000
#define NUM_OF_ARRAYS 2
void printArray(int *p, int len);
int * createIntArray(int *p, int len);

int main() {
	int array_len;
	int *p[NUM_OF_ARRAYS];
	int i;

	printf("Enter array size (max 1000 integers):\n");
	scanf("%d", &array_len);

	if(array_len > MAX_ARR_SIZE) {
		printf("Max array exceeded!\n");
		exit(0);
	}

	for(i = 0; i < NUM_OF_ARRAYS; ++i) {
		if( !(p[i] = createIntArray(p[i], array_len)) ) {
			printf("Memory allocation failed!\n");
			exit(0);
		}
	}
	

	for(i = 0; i < array_len; ++i) {
		scanf("%d", p[0] + i);
	}

	printArray(p[0], array_len);
	return 0;
}

void printArray(int *p, int len) {
	int i;

	for(i = 0; i < len; ++i) {
		printf("%d%s", *(p + i), len - 1 == i ? "" : " ");
	}
	printf("\n");
}

int * createIntArray(int *p, int len) {
	p = (int *) malloc(len * sizeof(int));
	if(!p) {
		return 0;
	}
	return p;
}
