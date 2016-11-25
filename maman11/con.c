#include <stdio.h>
#include <string.h>
#define TWO_CHAR_STRING 2
#define ONE_CHAR_STRING 1
#define INCREASED_BY_ONE 1
#define MAX_ARRAY_SIZE 100

/* function prototypes */
void contract(char s1[], char s2[]);
void printArr(char arr[]);

int main() {

	/* declare s1 and s2 arrays*/
	char s1[MAX_ARRAY_SIZE] =  "abcdzdcbaaa1234";
	char s2[MAX_ARRAY_SIZE];

	contract(s1, s2); /* use the contract function */

	printArr(s2); /* print the resulting s2 array */

	return 0; /* if main finished as expected return 0 */
} /* end of main */

	
/*				function contract:
				arguments: char s1[] - array with character string
			    char s2[] - empty array
	return: void
	description: the function receives 2 arrays. array s1 contains ASCII characters. The function shortens sequence(s) of
	characters according to this format: "a-z" where 'a' is the char with the lowest lexigraphical value while 'z'
	has the highest. if the string is only 2 chars long (increasing lexigraphical order) than we don't need the hyphen
	in the format. if the order is not increasing lexigraphical then we just write the chars "as is" into the array s2.
	At the end, s2 array will contain the result. The algorithm is the following:
		1) use a while-loop with the condition that the iterator i is less than the string's length
		2) check if we have a case of increasing lexigraphical order. if yes then increment str variable which stores
		the length of the currect string with increasing lexigraphical order.
		3) else if we have a case of just 2 chars of increasing lexigraphical order then write them to s2 array.
		reset min and str.
		4) else if we have a case of 3 or more chars on increasing lexigraphical order then shorten them (use the 
		the minimal char and the max char and add a hyphen). reset min and str.
		5) the last case is when we have a descending lexigraphical order. then we immediately write the char to
		s2 array. reset min. 
*/
void contract(char s1[], char s2[]) {

	int min; /* the first ascii letter in the current string with increasing order */
	int max; /* the ascii char with the highest integer value in the current string with increasing order */
	int i = 0; /* the index for traversing the s1 array */
	int j = 0; /* the index for traversing the s2 array */
	int str = ONE_CHAR_STRING; /* the length of the current sequence of chars of increasing order. initiated to 1
	in the beginning */
	int str_length = strlen(s1) + 1; /* the "real" length is s1 array which counts '\0' as well */

	min = s1[i]; /* set the min */
	++i; /* increment i so the max will be the next char after min */

	while(i < str_length) {	 /* do the while loop so long as the current char is not end of the string */
		max = s1[i]; /* set the new max. essentially we need a new max with each iteration */

		if(max - s1[i - 1] == INCREASED_BY_ONE) { /* check if max is higher than min exactly by one */
			++str; /* we increment str to signify increasing order with increments of 1 occured */
			++i;
		} else if(str == TWO_CHAR_STRING) { /* we have a string with increasing order but it's only 2 chars long
		thus just write it to s2 array*/
			s2[j] = min; /* write the first char from the current string */
			s2[++j] = s1[i - 1]; /* write the second char from the current string */
			s2[++j] = '\0'; /* the last char in s2 needs to be '\0' to signify the end of the string */
			str = ONE_CHAR_STRING; /* we took care of the current string with increasing order. 
			now reset the str to 1 for new count */
			min = s1[i]; /* now we need a new min */
			++i;
		} else if(str > TWO_CHAR_STRING){ /* we have a string with increasing order it's 3 chars or more and we need to
		make a contraction in this case */
			s2[j] = min; /* min is the starting value of the current string */
			s2[++j] = '-'; /* insert a hyphen according to the requested format */
			s2[++j] = s1[i - 1]; /* s1[i - 1] is the highest value of the current str */
			s2[++j] = '\0'; /* the last char in s2 needs to be '\0' to signify the end of the string */
			str = ONE_CHAR_STRING; /* we took care of the current string with increasing order. 
			now reset the str to 1 for new count */
			min = max; /* now we need a new min */
			++i;
		} else if(str == ONE_CHAR_STRING && (max - s1[i - 1] != INCREASED_BY_ONE)) { /* if a string with decreasing
		order occured. we know this because either str was never incremented or the integer interval between max
		and the previous char to max is not 1 */
			s2[j] = min; /* write the current char to s2 string */
			s2[++j] = '\0'; /* the last char in s2 needs to be '\0' to signify the end of the string */
			min = max; /* now we need a new min */
			++i;
		} /* end of if */
	} /* end of while */
} /* end of contract */

/* helper function, prints a char array */
void printArr(char arr[]) {
	int i;
	int str_len = strlen(arr); /* this is the length of the argument array */

	for(i = 0; i < str_len; ++i) { /* we'll use the loop print each char */
		printf("%c ", arr[i]);
	}
	printf("\n"); /* once we finished with printing the array we'll add a newline */
}
