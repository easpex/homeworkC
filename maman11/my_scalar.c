#include <stdio.h>
#define RAND_ARRAY_SIZE 5 /*random integer to create the arrays for testing the funtion scalar_product*/
int scalar_product(int arr1[], int arr2[], int length);
/*
arguments: int arr1[] - the first vector
		   int arr2[] - the second vector
		   int length - the length of both vectors
returns: int sum - the scalar product of the two vectors
description: the function receives 2 arrays and their length and computes
the scalar product via a for-loop
*/

int main() {
	int i;
	int arr1[RAND_ARRAY_SIZE]; /*the 1st array for testing scalar_product*/
	int arr2[RAND_ARRAY_SIZE]; /*the 2nd array for testing scalar_product*/
	int result; /*stores the result returned from scalar_product*/

	for(i = 0; i < RAND_ARRAY_SIZE; ++i) { /*the loop fills the arrays with values*/
		arr1[i] = i;
		arr2[i] = i * i;
	}

	result = scalar_product(arr1, arr2, RAND_ARRAY_SIZE);
	printf("the product = %d\n", result); /* prints the result */
	return 0; /*if main finished correctly we return 0 */
}

int scalar_product(int arr1[], int arr2[], int length) {
	int i; /* iterator to traverse the arrays */
	int sum = 0; /*sum of the individual products*/

	/*we'll use a for-loop in order to loop through the arrays and aggregate the sum*/
	for(i = 0; i < length; ++i) {
		sum += arr1[i] * arr2[i];
	}

	return sum;
}

