#include "set.h" /* set.h has all the function definitions, "define"s, typedefs as well as sets are initialzed there */

int main() {
	/**
	 * all commands except for HALT end in "_set". this is needed for command match
	 */
	char _set_array[] = "_set"; 
	char set_names[] = "ABCDEF"; /* all possible set names for matches */
	char *commandp[COMMAND_ARR_ROW_LEN]; /* the pointer array which contains the names of all commands */
	int i;
	int num; /* receives numbers from user input */
	set *setp; /* receives set name and is used in PRINT and READ */
	set *sets[SET_ARR_LEN]; /* set pointer array which contains the relevant sets used for set operatations */
	set *left, *right, *endSet; /* convinience pointers to make code more readable, because in each set operation
	there's a left/right operand and the end set */
	char line[MAX_LINE_LENGTH]; /* the char array which holds user input (one line at a time) */
	Status curr_status; /* central part of communication between all functions, the typedef contains the information 
	on the current char position, legal/illegal state that is passed from function to function and other fields */

	setInitToZero(); /* make sure that all fields in Status typedef are set to 0 */

	/* init commandp */
	commandp[0] = "sub";
	commandp[1] = "halt";
	commandp[2] = "read";
	commandp[3] = "union";
	commandp[4] = "print";
	commandp[5] = "intersect";
	/**
	 * the while loop gets user input line by line. Everything pretty much happens inside it. The loop will stop under
	 * 3 conditions: user's command was HALT, user input exceeded max allowed input length or we reached end of file 
	 * (for convinience only if user uses file input)
	 */
	while(getLine(line, MAX_LINE_LENGTH) >= 0) {
		clearStatus(&curr_status, line); /* make sure the Status typedef is clean */
		setCommand(line, commandp, _set_array, &curr_status); /* get the command from user input */
		/**
		 * because curr_status.command is an int each command is assigned a number. after setCommand() we should have 
		 * the number so we can use switch where each command is handled in its separate block. If the command is illegal
		 * or was not entered we go to the default case and "No such command is printed"
		 */
		switch(curr_status.command) {
			case HALT: /* if the user entered "halt" then we need to exit the program */
				printf("\nExiting the program\n");
				exit(0);
				break;
			case READ:
				setp = getSetName(&curr_status, set_names); /* get the set name */
				if(curr_status.state == LEGAL) {
					clearBits(setp); /* make sure the the set is clean and empty (we need all bits equal to 0 */

					/* after we got the set name we need to get the numbers from user's input. this is done in a
					while loop which stops if: a) we reached end of the line b) if the number entered was illegal
					c) there was an illegal sequence in the input */
					while(curr_status.endOfLine != EOFLINE &&
						(num = getNum(&curr_status)) != ILLEGAL &&
						curr_status.state == LEGAL) {
						numToBit(setp, num); /* turn on the corresponding bit from the number entered */
					}
					if(curr_status.state != LEGAL) {
						clearBits(setp); /* if the state is illegal then make sure we reset the set */
					} else {
						 setp -> init = ON; /* if the state is legal activate the set so other commands know
						that the set was initiliazed*/
					}
				}
				break;
			case PRINT:
				setp = getSetName(&curr_status, set_names); /* get the set name */
				if(curr_status.state == LEGAL) {
					checkRestOfLine(&curr_status); /* make sure that the rest of the line is legal */

					if(curr_status.state == LEGAL) {
					 	if(setp -> init == OFF) {  /* user input may be perfectly legal but
					 	is the set was never read and initialized we can't print it */
							printf("\nThe set %c was not initialized\n", curr_status.setName);					
						} else if(isEmpty(setp)){ /* check is the set is empty */
							printf("\nEmpty set\n"); 
						} else {
							printSet(setp);
						}
					}
				}
				break;
			case UNION:
				/* the processSetNames() function will parse the set names and assign them within the sets[] array. the
				function will make sure that the input is legal */
				if(processSetNames(curr_status, set_names, sets)) {
					/* assign the sets from sets[] array to left/right/endSet for better readability, because
					in set operations there're 2 operands */
					left = sets[FIRST]; 
					right = sets[SECOND];
					endSet = sets[LAST];
					 /* we need to turn on init field for the endSet otherwise print_set
					will not print it */
					endSet -> init = ON;

					for(i = 0; i < CHAR_ARR_LEN; i++) {
						/* union set operation is achieved by use of | bitwise operator because we need to 
						collect all the 1's from both sets */
						endSet -> arr[i] = left -> arr[i] | right -> arr[i];
					}
				}
				break;
			case INTERSECT:
				/* the processSetNames() function will parse the set names and assign them within the sets[] array. the
				function will make sure that the input is legal */
				if(processSetNames(curr_status, set_names, sets)) {
					/* assign the sets from sets[] array to left/right/endSet for better readability, because
					in set operations there're 2 operands */
					left = sets[FIRST];
					right = sets[SECOND];
					endSet = sets[LAST];
					 /* we need to turn on init field for the endSet otherwise print_set
					will not print it */
					endSet -> init = ON;

					for(i = 0; i < CHAR_ARR_LEN; i++) {
						/* union set operation is achieved by use of & bitwise operator because we need to 
						collect only the 1's that are common to both sets */
						endSet -> arr[i] = left -> arr[i] & right -> arr[i];
					}
				}
				break;
			case SUB:
				/* the processSetNames() function will parse the set names and assign them within the sets[] array. the
				function will make sure that the input is legal */
				if(processSetNames(curr_status, set_names, sets)) {
					/* assign the sets from sets[] array to left/right/endSet for better readability, because
					in set operations there're 2 operands */
					left = sets[FIRST];
					right = sets[SECOND];
					endSet = sets[LAST];
					 /* we need to turn on init field for the endSet otherwise print_set
					will not print it */
					endSet -> init = ON;

					for(i = 0; i < CHAR_ARR_LEN; i++) {
						/* union set operation is achieved by use of & and ~ bitwise operators because we need to 
						collect only the 1's that are unique only to the left set. in set theory:
						A\B = A intersect B's complement therefore we're using the corresponding bitwise operators */
						endSet -> arr[i] = left -> arr[i] & ~right -> arr[i];
					}
				}
				break;
			default:
				printf("\nNo such command\n"); /* if we arrived here then the command entered was invalid */
		} /* end of switch */
	} /* end of while */
	return 0; /* return from main() */
} /* end of main */

