#include "set.h"

char buffer[BUFFER_SIZE];
int bufpos = 0;

/*
(ARR_LEN - 1 == i) ? "\n" : " ")
*/
char haltState = 0;
char haltCount = 0;

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

int getCommand(char *line, char *commandp[], char *_set_array) {
	int i;
	int row; /* the row of the potential command in command_array */
	int matchCount = 1; /* counts matches after each char read from user that is matched by command name */

	while(isspace(*line)) { /* skip spaces */
		line++;
	}

	/* we'll check if the given string equals any of the 6 legal commands */
	for(i = 0; i < COMMAND_ARR_ROW_LEN; i++) {
		/* the first letters of each command are unique, therefore it's a good test
		to check first of all if the first letter of the string equals any of the legal commands' first letters.
		if yes then we'll check all of the letters
		*/
		if(*line == *(*(commandp + i))) {
			row = i; /* we found that the first letter matches.
			because the commands names are unique we only need to check this matches between the row and 
			the string. row is the corresponding row in the command_array */
			for(i = 1; i < strlen(commandp[row]); i++) {
				/* we'll start with i = 1 because the first letter had been matched by now */
				if(*++line == commandp[row][i]) {
					/* we increment matchCount each time 
					the pointer to the given string and the pointer to the command name are equal
					*/
					matchCount++;
				}
			}
			/* if it's halt command that check if there's a space or newline after it */
			if(row == HALT) {
				++line; /* advance 1 char forward */
				return (*line == ' ' || *line == '\n') ? row : -1;
			}

			/* check that the char immediately after the command name are "_set". after the loop 
			i should be equal to 4 if "_set" goes after the command name */
			for(i = 0; i < strlen(_set_array) && *++line == _set_array[i]; i++)
				;

			/* if the matchCount == the length of the string we have a match else return -1 */
			return (matchCount == strlen(commandp[row]) && i == strlen(_set_array) && isspace(*++line)) ? row : -1;
		}
	}
	return -1;
}

int getSetName(char *pset, char *set_names) {
	int i;
	while(isspace(*pset)) { /* skip spaces */
		pset++;
	}

	for(i = 0; i < strlen(set_names); i++) {
		if(*pset == set_names[i])
			return i;
	}
	return -1;
}

int getLine(char *s, int max) {
	int c, i;
	i = 0;

	while(--max > 0 && (c = getchar()) != EOF && c != '\n') {
		*s++ = c;
	}
	if(c != '\n') {
		printf("Exceeded max allowed input length");
		return -1;
	} else {
		*s++ = c;
	}
	*s = '\0';
	return i;
}

int getch(void) {
	return (bufpos > 0) ? buffer[--bufpos] : getchar();
}

void ungetch(int c) {
	if(bufpos >= BUFFER_SIZE) {
		printf("Too many characters\n");
	} else {
		buffer[bufpos++] = c;
	}
}

void printCharArr(char *s) {
	int i;
	for(i = 0; *s != '\0'; s++) {
		printf("%c ", *s);
	}
}
