#include "set.h"

void clearBits(set *s) {
	int i;
	for(i = 0; i < CHAR_ARR_LEN; i++) {
		s -> arr[i] = 0;
	} 
}

void setCommand(char *line, char *commandp[], char *_set_array, Status *st) {
	/* assumes there may be spaces before, if the input is legal sets st -> pos to the
	next char after the last char of the command name which will always be a space if the input is legal */
	int i;
	int row; /* the row of the potential command in command_array */
	int matchCount = 1; /* counts matches after each char read from user that is matched by command name */
	st -> state = ILLEGAL; /* worst case scenario the state will be marked as illegal if we receive illegal input */
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
					st -> state = LEGAL;
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
				st -> state = LEGAL;
				st -> pos = line;
			}
		}
	}
}

set *getSetName(Status *st, char *set_names) {
	/* assumes there may be spaces before, sets st-> pos to the next char after set name if the input is legal */
	int i;
	st -> state = ILLEGAL; /* worst case scenario the state will be marked as illegal if we receive illegal input */
	while(isspace(*st -> pos)) { /* skip spaces */
		st -> pos++;
	}

	for(i = 0; i < strlen(set_names); i++) {
		switch(*st -> pos) {
			case 'A':
				st -> setName = *st -> pos;
				st -> state = LEGAL;
				st -> pos++; /* increment the char position so the next function starts analyzing the next char */
				return &A;
				break;
			case 'B':
				st -> setName = *st -> pos;
				st -> state = LEGAL;
				st -> pos++; /* increment the char position so the next function starts analyzing the next char */
				return &B;
				break;
			case 'C':
				st -> setName = *st -> pos;
				st -> state = LEGAL;
				st -> pos++; /* increment the char position so the next function starts analyzing the next char */
				return &C;
				break;
			case 'D':
				st -> setName = *st -> pos;
				st -> state = LEGAL;
				st -> pos++; /* increment the char position so the next function starts analyzing the next char */
				return &D;
				break;
			case 'E':
				st -> setName = *st -> pos;
				st -> state = LEGAL;
				st -> pos++; /* increment the char position so the next function starts analyzing the next char */
				return &E;
				break;
			case 'F':
				st -> setName = *st -> pos;
				st -> state = LEGAL;
				st -> pos++; /* increment the char position so the next function starts analyzing the next char */
				return &F;
				break;
			default:
				break;
		} /* end of swtitch */
	} /* end of for loop */
		printf("\nNo such set\n");
		return NULL; /* return dummy set. main will still check for legal state */
	
} /* end of getSetName function */

int getNum(Status *st) {
	/* assumes that there's a preceding comma (maybe after spaces)
	and there's a comma after the number */
	int digitCount = 0;
	int num = 0;
	st -> state = ILLEGAL;
	while(isspace(*st -> pos)) { /* skip spaces */
		st -> pos++;
	}

	/* numbers must be separated by commas*/
	if(*st -> pos == ',')
		st -> pos++;
	else {
		printIllegalSequence();
		return ILLEGAL;
	}

	while(isspace(*st -> pos)) { /* skip spaces */
		st -> pos++;
	}

	/* if we have a minus */
	if(*st -> pos == '-') {
		st -> pos++; /* increment the string once so we can check if the next char is '1' */
		if(*(st -> pos) == '1') {
			st -> pos++; /* go to the next char */

			while(*st -> pos == ' ' && *st -> pos != '\n') {/* skip spaces */
				st -> pos++;
			}
				
			/* if there're spaces after -1 or if there're not we'll return EOFLINE else there was
			an illegal char after 1 so we return -1 */
			if(*st -> pos == '\n'){
				st -> state = LEGAL;
				st -> endOfLine = ON;
				return ILLEGAL;
			} else {
				printIllegalSequence();
				return ILLEGAL;
			}
		} else {
			printIllegalSequence();
			return ILLEGAL; /* we didn't get 1 after minus so the input is illegal */
		}
	}

	while(isdigit(*st -> pos) && digitCount <= MAX_DIGITS) {
		num = 10 * num + (*(st -> pos) - '0');
		st -> pos++; /* increment the string position for next function */
		digitCount++;
	}
	
	if(!digitCount) { /* if digitCount was never incremented it means that we never got a number */
		printIllegalSequence();
		return ILLEGAL;
	  /* digitCount was incremented now we need to check if the next char after the number is legal */	
	} else if(num > HIGH_LIM) {
		printf("\n%d is out of range\n", num);
		return ILLEGAL;
	} else {
		st -> state = LEGAL;
		return num;
	}
	printIllegalSequence();
	return ILLEGAL;
}


int getLine(char *s, int max) {
	char *p = s; /* we will use p to count string length */
	char prev = 0;
	int c;

	while(--max > 0 && (c = getchar()) != EOF && c != '\n') {
		*s++ = c;
		prev = c;
	}

	/* if the only input was a newline */
	if(c == '\n' && prev == 0) {
		return 0;
	}

	if(c == EOF) {
		printf("\nReached the end of file\n");
		*s = '\0';
		return ILLEGAL;
	}

	if(c != '\n') {
		printf("\nExceeded max allowed input length\n");
		return ILLEGAL;
	} else {
		*s++ = c;
	}

	*s = '\0';
	return s - p - 1;
}

void clearStatus(Status *st, char * line) {
	st -> endOfLine = OFF;
	st -> command = ILLEGAL;
	st -> setName = OFF;
	st -> pos = line;
}

void numToBit(set *s, int num) {
	int array_pos = num / BIT_IN_CHAR; /* determine the byte we need */
	int bit_pos = num % BIT_IN_CHAR; /* determine the bit we need */
	s -> arr[array_pos] ^= (-1 ^ s -> arr[array_pos]) & (1 << bit_pos); /* turn on the required bit */
}

void printSet(set *p) {
	int bitpos; /* the position of a bit in a byte */
	int memberCount = 0;
	int i;
	int numToPrint;

	for(i = 0; i < CHAR_ARR_LEN; i++) {
		/* traverse all the 16 bytes of set.arr */
		for(bitpos = 0; bitpos < BIT_IN_CHAR; bitpos++) {
			if( ( (p -> arr[i]) & (1 << bitpos)) != 0) {
				numToPrint = (i * BIT_IN_CHAR) + bitpos;
				/* if the bit is 1 then print it's position in the array.
				in order to calculate its position in the array:
				i - is the byte
				bitpos is the position inside the byte */
				memberCount++;
				
				if(memberCount % NUMS_PER_LINE == 1)
					printf("\n");
			
				if(numToPrint < DOUBLE_DIGIT) {
					printf("%d%d ", 0, numToPrint);
				} else {
					printf("%d ", numToPrint);
				}
			}
		}
	}
	printf("\n");
}

void setInitToZero() {
	A.init = OFF;
	B.init = OFF;
	C.init = OFF;
	D.init = OFF;
	E.init = OFF;
	F.init = OFF;
}

void advanceComma(Status *st) {
	while(isspace(*st -> pos)) { /* skip spaces */
		st -> pos++;
	}
	/* if the char is comma then it's legal input, increment the current position in the string
	else the state is illegal */
	if(*st -> pos == ',') {
		st -> state = LEGAL;
		st -> pos++;
	} else {
		printIllegalSequence();
		st -> state = ILLEGAL;	
	}
}

void checkRestOfLine(Status *st) {
	st -> state = ILLEGAL;
	while(isspace(*st -> pos) && *st -> pos != '\n') { /* skip spaces */
		st -> pos++;
	}

	if(*st -> pos == '\n') {
		st -> state = LEGAL;
	} else {
		printIllegalSequence();
	}
}

int processSetNames(Status curr_status, char * set_names, set * sets[]) {
	int i;
	/* we need to get the 3 sets which is the required number of arguments
				that UNION needs to receive */

	for(i = 0; i < SET_ARR_LEN && curr_status.state == LEGAL; i++) {
		sets[i] = getSetName(&curr_status, set_names); /* get the set */
		if(curr_status.state != LEGAL) { /* if the state is not legal, the character that the user put 
		is not a valid set name */
			return 0;
		}

		/* we need to check that the first 2 sets were initialized (the last one doesn't have to be
		initialized  */
		if(i < SET_ARR_LEN - 1 && sets[i] -> init == 0) {
			curr_status.state = ILLEGAL;
			printf("\n1The set %c was not initialized - i = %d\n", curr_status.setName, i);
			return 0;
		}
		/* printf("set %d = %c\n", i, curr_status.setName); */

		/* we'll use advanceComma() to make sure the set names are separated by commas 
		and/or spaces */
		if(i < SET_ARR_LEN - 1 && curr_status.state == LEGAL) {
			advanceComma(&curr_status);
		}
	} /* end of for loop */

	if(curr_status.state == LEGAL){ /* if after advanceComma() the state is legal then we need
	to check if the rest of the line is legal. The only legal characters in the rest of the line
	can be spaces and newline */
		checkRestOfLine(&curr_status);

		if(curr_status.state != LEGAL) {
		 /* if the rest of the line was illegal */
			return 0;
		} else {
			return LEGAL;
		}
	}
	return 0;
}

void printIllegalSequence() {
	printf("\nIllegal sequence!\n");
}
