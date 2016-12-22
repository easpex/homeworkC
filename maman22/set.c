#include "set.h"

char buffer[BUFFER_SIZE];
int bufpos = 0;

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

void setCommand(char *line, char *commandp[], char *_set_array, Status *st) {
	int i;
	int row; /* the row of the potential command in command_array */
	int matchCount = 1; /* counts matches after each char read from user that is matched by command name */
	st -> state = -1; /* worst case scenario the state will be marked as illegal if we receive illegal input */
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
				if(*line == ' ' || *line == '\n')
					st -> command = HALT;
					st -> state = 1;
			}

			/* check that the char immediately after the command name are "_set". after the loop 
			i should be equal to 4 if "_set" goes after the command name */
			for(i = 0; i < strlen(_set_array) && *++line == _set_array[i]; i++)
				;

			/* if the matchCount == the length of the "_set" and i was incremented to "_set" length
			and the next char in string is a space, then all of the criteria for matching
			command name are satisfied so we:
			-set the command
			-set the state to 1
			-set the line position for next function */
			if(matchCount == strlen(commandp[row]) && i == strlen(_set_array) && isspace(*++line)) {
				st -> command = row;
				st -> state = 1;
				st -> pos = line;
			}
		}
	}
}

void setSetName(Status *st, char *set_names) {
	int i;
	st -> state = -1; /* worst case scenario the state will be marked as illegal if we receive illegal input */
	while(isspace(*st -> pos)) { /* skip spaces */
		st -> pos++;
	}

	for(i = 0; i < strlen(set_names); i++) {
		if(*st -> pos == set_names[i]) {
			st -> setName = *st -> pos;
			st -> state = 1;
		}
	}
	st -> pos++; /* increment the char position so the next function starts analyzing the next char */
}

int getNum(Status *st) {
	/* assumes that there's a preceding comma (maybe after spaces)
	and there's a comma after the number */
	int digitCount = 0;
	int num = 0;
	st -> state = -1;
	while(isspace(*st -> pos)) { /* skip spaces */
		st -> pos++;
	}

	/* numbers must be separated by commas*/
	if(*st -> pos == ',')
		st -> pos++;
	else {
		printf("Illegal sequence");
		return -1;
	}

	while(isspace(*st -> pos)) { /* skip spaces */
		st -> pos++;
	}

	/* if we have a minus */
	if(*st -> pos == '-') {
		st -> pos++; /* increment the string once so we can check if the next char is '1' */
		if(*(st -> pos) == '1') {
			st -> pos++; /* go to the next char */

			while(isspace(*st -> pos) && *st -> pos != '\n')/* skip spaces */
				st -> pos++;
				
			/* if there're spaces after -1 or if there're not we'll return EOFLINE else there was
			an illegal char after 1 so we return -1 */
			if(*st -> pos == '\n'){
				st -> state = 1;
				st -> endOfLine = 1;
				return -1;
			}
		} else {
			printf("Illegal sequence");
			return -1; /* we didn't get 1 after minus so the input is illegal */
		}
	}

	while(isdigit(*st -> pos) && digitCount <= MAX_DIGITS) {
		num = 10 * num + (*(st -> pos) - '0');
		st -> pos++;
		digitCount++;
	}
	
	if(digitCount == 0) { /* if digitCount was never incremented it means that we never got a number */
		printf("Illegal sequence");
		return -1;
	  /* digitCount was incremented now we need to check if the next char after the number is legal */	
	} else if(*st -> pos == ',') {
		if(num > HIGH_LIM) {
			printf("%d is out of range", num);
			return -1;
		} else {
			st -> state = 1;
			st -> pos++; /* increment the string position for next function */
			return num;
		}
	} /* end of case with comma */

	 else if(isspace(*st -> pos)){ /* now we check if the next char is a space */

		while(isspace(*st -> pos)) /* skip spaces */
			st -> pos++;

		if(*st -> pos == ',') { /* if it's a comma we just need to check the range */
			if(num > HIGH_LIM) {
				printf("%d is out of range", num);
				return -1;
			} else {
				st -> state = 1;
				st -> pos++; /* increment the string position for next function */
				return num;
			} /* end of case if the char is a comma */
		} else {
			printf("Illegal sequence"); /* if the char is not a comma or space then it's an illegal sequence */
			return -1;
		}
	}
	printf("Illegal sequence");
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

void test(char **p) {
	int i;

	for(i = 0; i < 3; i++, (*p)++)
		;
}

void printStatus(Status st) {
	printf("state = %d\n", st.state);
	printf("endOfLine = %d\n", st.endOfLine);
	printf("command = %d\n", st.command);
	printf("setName = %c\n", st.setName);
	printf("pos = %c\n", *(st.pos));
}
