#include <stdio.h>
#include <string.h>
#define LOWER 0 /*the integer value of an ascii char cannot be lower than 0 */
#define HIGHER 127 /*the integer value of an ascii char cannot be higher than 127 */
#define TWO_CHAR_STRING 2
#define ONE_CHAR_STRING 1
#define TRUE 1
#define FALSE 0
#define MIN_SEQUENCE 3
#define TWO_STEPS 2
#define INVALID 99

void contract(char s1[], char s2[]);
int isLegal(char c);
void printArr(char arr[]);

int main() {
	char s1[4] = {1000,5000,45000,'\0'};
	char s2[4] = {0};
	char c = '\n';
	char uc;
	char sc;
	char mc;

	uc = (unsigned char) c;
		sc = (signed char) c;
		mc = c - '0';
		printf("c = %d | uc = %d | sc = %d | mc = %d\n", c, uc, sc, mc);
		if(c < LOWER || c > HIGHER) {
			printf("Illegal!");
		}

		printf("-----while-----\n");
printArr(s1);


/*
	while( (c = getchar()) != EOF) {
		uc = (unsigned char) c;
		sc = (signed char) c;
		mc = c - '0';
		printf("c = %d | uc = %d | sc = %d | mc = %d\n", c, uc, sc, mc);

	}
*/
	return 0;
}

void contract(char s1[], char s2[]) {
/*
1. convert char to int
2. check that it's between 0 to 127
3. init min/max
4. if the order is increasing and increases only by 1 then continue and increment the max
	else if (the order is the same or decreases)
		write the min and the max in the "a-z" format
	else if (the order has always been the same or decreasing)
		keep writing the same string to s2

*/
int min; /*the first ascii letter in the string*/
int max; /*the ascii char with the highest integer value, 
provided the lexicographical order is still increasing*/
int i = 0; /*the index for traversing the s1 array*/
int j = 0; /*the index for traversing the s2 array*/
int str = 0; /*the length of the current sequence of chars of increasing order*/

min = s1[i];
max = s1[i + 1];

do{
	if(!isLegal(max)) {
		if(!isLegal(min)) {
			i += TWO_STEPS;
			min = s1[i];
			max = s1[i + 1];
		}
		s2[j] = min;
		++j;
		++i;
		min = s1[i];
		max = s2[i + 1];
	} else if(max > min && max < s1[i]) {
		max = s1[i];
		++str;
		++i;
	} else if(str >= MIN_SEQUENCE) {
		s2[j] = '-';
		s2[++j] = max;
		++i;
		++j;
	} else {
		s2[j] = max;
		++i;
		++j;
	} /*end of big if*/
} while(s1[i + 1] != '\0');


	

 /*end of while*/



}

int isLegal(char c) {
	int result;
	if(c < LOWER || c > HIGHER) {
		printf("Illegal character!");
		result = FALSE;
	} else {
		result = TRUE;
	}
	return result;
}

void printArr(char arr[]) {
	int i;
	for(i = 0; i < strlen(arr); ++i) {
		printf("%c ", arr[i]);
	}
	printf("\n");
}
