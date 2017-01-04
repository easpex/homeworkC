#include "set.h" /* set.h has all the function definitions, "define"s, typedefs as well as sets are initialzed there */

/**
Before we read set name and the numbers it contains we make sure that the previous numbers are removed from the set. 
Because we use bit arrays for numbers representation we actually set all bits to 0.

@param - set *s - a pointer to a set
*/

void clearBits(set *s) {
	int i;
	for(i = 0; i < CHAR_ARR_LEN; i++) {
		s -> arr[i] = 0;
	} 
}

/**
The function receives a string and attempts to deduce the command from six possible ones. Deducing the command is
the first step in order to execute a specific command. Therefore if the command was not deduced from the string, the 
function will set the state to illegal in the Status typedef pointer and the rest of the string will be ignored. Assumes
there may be spaces before the command itself. If the input is legal sets st -> pos to the
next char after the last char of the command name. Checks if the next immediate char after the command name is a space, if
it's not a space will set st -> state to illegal. If the command is halt the function will be a bit lenient in the sense
that it will check if the next char is a space or a newline. If there're other chars after those, the chars will be
ignored and HALT will still be executed. If the command was deduced successfully st -> command will be set to an int
which corresponds to the command. There's a switch in the main which essentially decided what command to execute 
based on the st -> command. 

@param - char *line - the whole string that the user entered
@param - char *commandp[] - pointer array to the names of all the six possible commands. the function checks
if the entered command is matched with any of the six commands in the array
@param - char *_set_array - each command ends in "_set" chars so *_set_array is exactly that string
@param - Status *st - Status typedef which contains the most important information that needs to be passed from the
function to other functions. the position of the next char is passed through *st as well as the command itself and
the state (legal/illegal)

Algorithm: 
1) set state as illegal. only if future actions will lead to a legal state we will change the state.
2) disregard spaces.
3) check if the first letter of the entered command matches the first letter of any of the six commands, otherwise 
we don't even need to check further
4) check if the rest of the entered command matches the rest of the selected command.
5) if the command is HALT then can immediately set the state to legal
6) if it's other command than HALT we need to check if "_set" is also matched.
7) finally of all the conditions are satisfied we set the state to legal and pass st -> pos to the next function 
*/

void setCommand(char *line, char *commandp[], char *_set_array, Status *st) {
	int i;
	int row; /* the row of the potential command in command_array */
	int matchCount = 1; /* counts matches after each char read from user that is matched by command name.
	it is set to 1 because first we check if the first letter of the entered command matches the first
	letter of any of the six commands. then there's another loop that increments matchCount. because the
	second loop is unaware of the first one we assume that of we arrived to the stage of the second loop
	at least the first letter was matched */
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
			if(row == HALT && matchCount == strlen(commandp[row])) {
				++line; /* advance 1 char forward */
				if(*line == ' ' || *line == '\n')
					st -> command = HALT; /* set the command to HALT */
					st -> state = LEGAL; /* set the state to legal */
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
				st -> pos = line; /* pass the next char pos of the user's input to other functions */
			}
		}
	}
}

/**
The function returns the set that the user entered. It receives the current char position within the string of the
user's input from Status typdef and it matched user input to an array of six possible set names.

@param - Status *st - Status typdef which contains state, setName, char position information.
@param - char *set_names - a char pointer to the string which contains all possible six names of the set names.
@return - set * - set typedef pointer to the matched set.

Algorithm:
1) conservatively set the state to illegal (worst case scenario)
2) disregard spaces.
3) now after spaces (if any) there must the set name. if it's legal it will be matched to the six possible set names,
if not "No such set" will be printed and null pointer will be returned.
*/

set *getSetName(Status *st, char *set_names) {
	/* assumes there may be spaces before, sets st-> pos to the next char after set name if the input is legal */
	int i;
	st -> state = ILLEGAL; /* worst case scenario the state will be marked as illegal if we receive illegal input */
	while(isspace(*st -> pos)) { /* skip spaces */
		st -> pos++;
	}

	/* the for loop checks if the given char is matched to any of the possbile  six set names */
	for(i = 0; i < strlen(set_names); i++) {

		/* we can use switch in order to match the set name because all chars have digit values.
		so we check it the current char (*st -> pos) is matched to the set_names string */
		switch(*st -> pos) {
			case 'A':
				st -> setName = *st -> pos; /* set the setName */
				st -> state = LEGAL; /* set the state to LEGAL */
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
		} /* end of swtitch */
	} /* end of for loop */

		/* if arrived all the way to here then the char the user entered was not matched, we print a message to 
		the user ans return NULL pointer */
		printf("\nNo such set\n");
		return NULL; /* return dummy set. main will still check for legal state */
} /* end of getSetName function */

/**
The function gets a number from user input. It assumed that there's a comma that precedes the number (maybe after spaces).
It received the current char position from Status typedef. In the end it returns the number.

@param - Status *st - Status typedef which contains the information about state, char position of user input.
@return - int - the number that the user entered or -1 if the input was illegal.

Algorithm:
1) The range of numbers can be between 0 and 127. digitCount is incremented each time we have a new digit (3 max).
2) conservatively set the state to illegal (worst case scenario)
3) disregard spaces
4) check if have a comma, if comma was never encountered the input is illegal
5) check again if there're spaces after the comma
6) if we encounter "-1" this means end of user input per the given line. if there're still other characters after
"-1" (spaces or newline are OK of course) then the input is illegal.
7) if the next char is actually a digit we start collecting up to 3 digits (there can be 3 digits max).
8) if the collected digits form a legal number we return it else we return -1
*/

int getNum(Status *st) {
	/* assumes that there's a preceding comma (maybe after spaces)
	and there's a comma after the number */
	int digitCount = 0; /* there can be max 3 digits in any number */
	int num = 0; /* the number to be returned */
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
				st -> endOfLine = ON; /* we inform the next function that end of line was reached via Status typdef */
				return -1;
			} else {
				printIllegalSequence();
				return ILLEGAL;
			}
		} else {
			printIllegalSequence();
			return ILLEGAL; /* we didn't get 1 after minus so the input is illegal */
		}
	}

	/* the loop checks if the char is a digit. if it is, then we allow up to 3 possible iterations
	(because legal number can be between 0 and 127).  */
	while(isdigit(*st -> pos) && digitCount <= MAX_DIGITS) {
		num = 10 * num + (*(st -> pos) - '0'); /* incerement the number by the next digit. each previous digit will
		be multiplied by 10 plus the next digit */
		st -> pos++; /* increment the string position for next function */
		digitCount++; /* increment the digitCount which helps us make sure we're checking for more than 3 digits */
	}
	
	if(!digitCount) { /* if digitCount was never incremented it means that we never got a number */
		printIllegalSequence();
		return ILLEGAL;
	  /* digitCount was incremented now we need to check if the next char after the number between 0 and 127 */	
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

/**
The function reads user input line by line. It terminates if it reached end of file (handy if the user enters input
via a file), if the input exceeded max allowed length and finally if newline is reached. Returns the length of the entered
line.

@param - char *s - pointer to char array where user input will be saved
@param - int max - max allowed input length
@return - int - the length of user input

Algorithm:
1) keep reading user input char by char until EOF, newline or max input length is exceeded. 
2) if we reached end of file return -1 (defined as ILLEGAL in set.h)
3) if max was decrememnted until it's 0 and the last char is not newline then max allowed input
length was exceeded
4) lastly return input length
*/

int getLine(char *s, int max) {
	char *p = s; /* we will use p to count string length */
	int c;

	/* read user input */
	while(--max > 0 && (c = getchar()) != EOF && c != '\n') {
		*s++ = c;
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
		*s++ = c; /* c is a newline and we add it to *s */
	}

	*s = '\0'; /* the last char in any string should be '\0' */

	/* in the beginning of the function p pointed to s. s then was incremented by p was not. 
	therefore we can calculate the length of the string if we subtract p from s */
	return s - p - 1;
}

/**
At each iteration of while loop in main() we need to make sure that Status typedef is cleared from earlier settings as
well as it needs to be aware of the new line from user input.

@param - Status *st - Status typedef which needs to be reset
@param - char * line - st -> pos will now point to the new line from user input
*/

void clearStatus(Status *st, char * line) {
	st -> endOfLine = OFF;
	st -> command = ILLEGAL;
	st -> setName = OFF;
	st -> pos = line;
}

/**
The function turns on the corresponding bit in the char array from the given num. For example, if the num is 12,
12-th bit will be turned on in the char array field from set *s. In order to turn on the correct bit we first need
to determine the byte. This can be determined by the floor of num / BIT_IN_CHAR = num / 8. Now that we're inside the
required byte we need to determine the correct bit. This can be done through modulo: num % BIT_IN_CHAR = num % 8.
Once we know the position of the byte in the char array and the position of the bit inside the byte we can turn on the
required bit.

@param - set *s - a pointer to set typedef
@param - int num - the bit corresponding to the number will be turned on
*/
void numToBit(set *s, int num) {
	int array_pos = num / BIT_IN_CHAR; /* determine the byte we need */
	int bit_pos = num % BIT_IN_CHAR; /* determine the bit we need */

	/* first we can use left shift bitwise operator to signify the bit we want to turn on. 
	then we use OR bitwise operator, which means that if the bit we want to turn on is 0 it will become 1.
	if it was 1 already then it will remain 1 */
	s -> arr[array_pos] = s -> arr[array_pos] | (1 << bit_pos); /* turn on the required bit */
}

/**
The function prints the numbers that belong to a given set. 

@param - set *p - a pointer to a set typedef

Algorithm:
1) outer loop iterates through set -> arr field, byte after byte, i represents a given byte
2) inner loop iterates inside a byte. bitpos represents the position within the byte. we check bit by bit if the
bit is 1 and if yes we can convert it to a number via the formula: number = (i * BIT_IN_CHAR) + bitpos.
3) memberCount counts how many 1's we have encountered. because we're required to print at max 16 
numbers per line so we check if memberCount % 16 == 1 then we start printing numbers from a new line
4) if the number to print is a single digit we add '0' so it's prettier.
*/
void printSet(set *p) {
	int bitpos; /* the position of a bit in a byte */
	int memberCount = 0; /* counts how many numbers were printed so far */
	int i;
	int numToPrint; /* number to be printed */

	for(i = 0; i < CHAR_ARR_LEN; i++) {
		/* traverse all the 16 bytes of set.arr */
		for(bitpos = 0; bitpos < BIT_IN_CHAR; bitpos++) {

			/* if the it's 1 at the shifted position then we have a number to print */
			if( ( (p -> arr[i]) & (1 << bitpos)) != 0) {
				numToPrint = (i * BIT_IN_CHAR) + bitpos;
				/* if the bit is 1 then print it's position in the array.
				in order to calculate its position in the array:
				i - is the byte
				bitpos is the position inside the byte */
				memberCount++;
				
				if(memberCount % NUMS_PER_LINE == 1) /* once every 16 numbers we print a newline */
					printf("\n");
			
				if(numToPrint < DOUBLE_DIGIT) {
					printf("%d%d ", 0, numToPrint); /* add a '0' if it's a single digit number */
				} else {
					printf("%d ", numToPrint);
				}
			}
		}
	}
	printf("\n");
}

/**
The function sets the init field of all sets to 0 at the start of main()
*/
void setInitToZero() {
	A.init = OFF;
	B.init = OFF;
	C.init = OFF;
	D.init = OFF;
	E.init = OFF;
	F.init = OFF;
}

/**
The function is needed for processSetNames(). It assumes that a comma will be encountered (after possible spaces)
and increments the char position to the next char.

@param - Status *st - Status typedef which contains the current char position of user input and state field

Algorithm:
1) disregard spaces
2) once a non-space is encountered check if it's a comma. if yes, set the state to legal otherwise it's illegal
input and set the state to illegal
*/

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

/**
The function is needed for command all commands except for READ and HALT. It makes sure that after all
the meaningful input is received there's no other input. For example, if a user entered "print_set A  , 234"
the function would recognize that after "print_set A" there's ", 234" which is illegal sequence.

@param - Status *st - a pointer to Status typedef which contains current char position and state field.

Algorithm:
1) conservatively set the state to illegal (worst case scenario)
2) disregard spaces
3) if we encountered a newline that the input is legal
4) otherwise print message that the input is illegal
*/

void checkRestOfLine(Status *st) {
	st -> state = ILLEGAL;
	while(isspace(*st -> pos) && *st -> pos != '\n') { /* skip spaces */
		st -> pos++;
	}

	if(*st -> pos == '\n') { /* if we encountered a newline and so far there was no illegal input then set the
	state to legal */
		st -> state = LEGAL;
	} else {
		printIllegalSequence();
	}
}

/**
The function processes sets for 3 commands: SUB/UNION/INTERSECT. It checks that the user entered exactly 3 sets,
that the input is legal and sets the *sets[] pointer array to the relevant sets. If the input is legal it returns 1
otherwise 0.

@param - Status curr_status - Status typedef. it is not a pointer this time because we don't need to preserve any
information for other functions (e.g. char pos, state) because we already have the command and sets (if the input is
legal) and we just need to perform the set operation.
@param - char * set_names - the string with the names of all the sets
@param - set *sets[] - pointer array of set typedef. they will be set to the relevant sets so that the actual
set operation can be perfomed in the main().

@return - int - 1 if the function managed to process the sets correctly otherwise 0

Algorithm:
1) 
*/

int processSetNames(Status curr_status, char * set_names, set * sets[]) {
	int i;
	/* we need to get the 3 sets which is the required number of arguments
				that SUB/UNION/INTERSECT need to receive */
	for(i = 0; i < SET_ARR_LEN && curr_status.state == LEGAL; i++) {
		sets[i] = getSetName(&curr_status, set_names); /* get the set */
		if(curr_status.state != LEGAL) { /* if the state is not legal, the character that the user put 
		is not a valid set name */
			return 0;
		}

		/* we need to check that the first 2 sets were initialized (the last one doesn't have to be
		initialized. If it existed from before it will be overwritten) that's why i < SET_ARR_LEN - 1.
		*/
		if(i < SET_ARR_LEN - 1 && sets[i] -> init == 0) {
			curr_status.state = ILLEGAL;
			printf("\nThe set %c was not initialized\n", curr_status.setName);
			return 0;
		}

		/* we'll use advanceComma() to make sure the set names are separated by commas 
		and/or spaces. We only need to use advanceComma() for the first 2 sets, because there won't be
		a comma after the 3rd */
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
	return 0; /* if we arrived to here then the input was illegal */
}

/**
A small convinience function which prints "Illegal sequence" instead of having the manually printf this each time.
This way possible spelling errors can be avoided and less characters are required to achieve the goal.
*/

void printIllegalSequence() {
	printf("\nIllegal sequence!\n");
}
