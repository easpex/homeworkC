#include <stdio.h>
#include <stdlib.h> /* need this for malloc */

/* function prototypes */
int * summary(int *p, int len);
void printArray(int *p, int len);
int * createIntArray(int *p, int len);

int main() {
	int array_len; /* holds the array length */
	int *p = 0; /* will point to the input array */
	int i; /* iterator */
	int * summary_array; /* will point to the array with summarized values */

	printf("Enter array size:\n"); /* input prompt for the user */
	scanf("%d", &array_len); /* get the array length */

	/* if createIntArray returns 0, this means that malloc failed inside createIntArray().
	I decided to call exit() from main and not from inside createIntArray() because
	philosophically it feels like main should control the flow and not one of the functions
	it uses because theoretically there could be a backup scenario in main for such events */
	if( !(p = createIntArray(p, array_len)) ) {
		printf("Memory allocation failed!\n");
		exit(0); /* if there's not enough memory then exit the program */
	}
	
	printf("\nEnter the integers:\n"); /* input prompt for the user */

	/* get the integers from user's input */
	for(i = 0; i < array_len; ++i) {
		scanf("%d", p  + i); /* we're using a pointer so incrementing by one for each new int */
	}

	summary_array = summary(p, array_len); /* call summary function and receive the pointer to the summarized array */

	printf("\nThe summary array:\n");
	printArray(summary_array, array_len); /* print the summarized array */


	
	

	return 0;
}

/* summary function:
args: int *p - pointer to an int array
	  int len - the length of the int array
return: int * - pointer to the summarized array
description: summary function receives a pointer to an int array and its length. It creates
a new array using createIntArray() (exits if the array wasn't created) and fills the new array with summarized
values whereas the integer at index i of the new array is the sum of all integers of the received array from i = 0
up to i. 
*/
int * summary(int *p, int len) {
	int *s = 0; /* the pointer for the summarized array */
	int i; /* the iterator */

	if( !(s = createIntArray(s, len)) ) { /* create the array */
		printf("Memory allocation failed!\n");
		exit(0); /* if there's not enough memory exit the program */
	}

	*s = *p; /* the first int in the summarized array is the exactly the same as in the received array */
	
	for(i = 1; i < len; ++i) {
		/* loop through the received array and each time any given int in the summarized array
		is the sum of its corresponding int in the received array + previous int in the summarized arrays */
		*(s + i) = *(p + i) + *(s + i - 1); 
	}
	return s;
}
/* printArray function:
args: int *p - pointer to an int array
	  int len - the length of the array
return: void
description: the function prints the received array
*/
void printArray(int *p, int len) {
	int i;

	for(i = 0; i < len; ++i) {
		/* we want to print array elements one by one. if it's the last element then it shouldn't be followed
		by anything, else we want to print a space in order to separate the elements visually
		*/
		printf("%d%s", *(p + i), len - 1 == i ? "" : " ");
	}
	printf("\n");
}

/*
createIntArray function:
args: int * p - a pointer to an array 
*/
int * createIntArray(int *p, int len) {
	p = (int *) malloc(len * sizeof(int));
	if(!p) {
		return 0;
	}
	return p;
}
