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
	/* char s0[1] = {'a', '\0'}; */

	char s1[10] = {'a','b', 'a', 'b', 'c', '\0'};
	char s2[17] = {'k', 'k', 'k', 'k', 'k', 'k', 'k', 'k', 'k', 'k', 'k', 'k', 'k', 'k', 'k', 'k', '\0'};
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

		
printf("MAIN: strlen of s1 = %d | strlen of s2 = %d\n", strlen(s1), strlen(s2));
contract(s1, s2);

printf("-----after contract-----\n");
printArr(s2);

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
int str = ONE_CHAR_STRING; /*the length of the current sequence of chars of increasing order*/
int str_length = strlen(s1) + 1; /* the length is s1 array */
printf("s1 strlen = %d\n", str_length);

/* if the s1 string is only one char nothing needs to be done, just write the char to s2 */
if(str_length == ONE_CHAR_STRING) {
	s2[ZEROETH] = s1[ZEROETH];
	return;
}


min = s1[i]; /* set the min */
++i; /* increment i so the max will be the next char after min */

while(i < str_length) {	 /* do the while loop so long as the current char is not end of the string */
printf("inside while in contract\n");

	max = s1[i]; /* set the new max. essentially we need a new max with each iteration */
	printf("max = %d\n", max);
	if(min < max && (max - s1[i - 1] == INCREASED_BY_ONE)) {
		printf("inside 1 if \n");
		++str; /* we increment str to signify increasing order with increments of 1 occured */
		++i;
	} else if(str == TWO_CHAR_STRING) { /* we have a string with increasing order but it's only 2 chars
	thus just write it to s2 array*/
		printf("inside 2 if \n");
		s2[j] = min; /* write the first char from the string */
		s2[++j] = s1[i - 1]; /* write the second char from the string */
		s2[++j] = '\0'; /* the last char in s2 needs to be '\0' to signify the end of the string */
		str = ONE_CHAR_STRING; /* we took care of the current string with increasing order. now reset the str to 1 for new count */
		min = s1[i]; /* now we need a new min */
		++i;
	} else if(str > TWO_CHAR_STRING){ /* we have a string with increasing order it's 3 chars or more and we need to
	make a contraction in this case */
		printf("inside 3 if \n");
		s2[j] = min; /* min is the starting value of the current str */
		s2[++j] = '-'; /* insert a hyphen according to the format */
		s2[++j] = s1[i - 1]; /* s1[i - 1] is the highest value of the current str */
		s2[++j] = '\0'; /* the last char in s2 needs to be '\0' to signify the end of the string */
		str = ONE_CHAR_STRING;
		min = max; /* now we need a new min */
		++i;
	} else if(str == ONE_CHAR_STRING && (max - s1[i - 1] != INCREASED_BY_ONE)) { /* if a string with decreasing order occured
	or the integer interval between chars is not equal to +1 */
		printf("inside 4 if \n");
		s2[j] = min;
		s2[++j] = '\0'; /* the last char in s2 needs to be '\0' to signify the end of the string */
		min = max; /* now we need a new min */
		++i;
	}
	printf("the i inside while = %d | the j = %d | s2 len = %d\n", i, j, strlen(s2));
} /*end of while*/

printArr(s2);

}

void printArr(char arr[]) {
	int i;
	printf("array length = %d\n", strlen(arr));
	for(i = 0; i < strlen(arr); ++i) {
		printf("%c ", arr[i]);
	}
	printf("\n");
}
