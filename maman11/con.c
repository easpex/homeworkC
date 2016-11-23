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
#define ZEROETH 0
#define FIRST 1
#define INCREASED_BY_ONE 1

void contract(char s1[], char s2[]);
void printArr(char arr[]);

int main() {
	char s0[1] = {'\0'};
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
contract(s0, s2);

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
0. if the string is length 1 return the string
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
int str_length = strlen(s1); /* the length is s1 array */
printf("the strlen = %d\n", str_length);

/* if the s1 string is only one char nothing needs to be done, just write the char to s2 */
if(str_length == ONE_CHAR_STRING) {
	s2[ZEROETH] = s1[ZEROETH];
	return;
}


min = s1[i]; /**/
do{
	
	max = s1[i];


	if(min < max && (max - s1[i - 1] == INCREASED_BY_ONE)) {
		++str; /* we increment str to signify increasing order with increments of 1 occured */
		++i;
	} else if(str == TWO_CHAR_STRING) { /* we have a string with increasing order but it's only 2 chars
	thus just write it to s2 array*/
		s2[j] = min; /* write the first char from the string */
		s2[++j] = max; /* write the second char from the string */
		++j; /* increment j so that we have an empty slot in s2 array ready next time */
		str = 0; /* we took care of the current string with increasing order. now reset the str to 0 for new count */
		min = s1[i]; /* now we need a new min */
	} else if(str > TWO_CHAR_STRING){
		s2[j] = min;
		s2[++j] = '-';
		s2[++j] = s1[i - 1];
		++j; /* increment j so that we have an empty slot in s2 array ready next time */
		min = max; /* now we need a new min */
	} 
} while(s1[i] != '\0');


	

 /*end of while*/



}

void printArr(char arr[]) {
	int i;
	for(i = 0; i < strlen(arr); ++i) {
		printf("%c ", arr[i]);
	}
	printf("\n");
}
