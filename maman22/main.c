#include "set.h"

int main() {
	char command_array[COMMAND_ARR_ROW_LEN][COMMAND_ARR_COL_LEN] = {"sub", "halt", "read", "union", "print", "intersect"};
	char _set_array[] = "_set";
	char set_names[] = "ABCDEF";
	char *commandp[COMMAND_ARR_ROW_LEN];
	int i;
	int num;
	set *setp;
	set *sets[SET_ARR_LEN];
	set *left, *right, *endSet;
	set **receiver;


	char line[MAX_LINE_LENGTH];
	Status curr_status;

	setInitToZero();

	/* init commandp */
	for(i = 0; i < COMMAND_ARR_ROW_LEN; i++) {
		commandp[i] = command_array[i];
	}

	while(getLine(line, MAX_LINE_LENGTH) >= 0) {
		clearStatus(&curr_status, line);
		setCommand(line, commandp, _set_array, &curr_status);

		if(curr_status.state != LEGAL) { /* check if the command is legal */
			printf("\nNo such command\n");
		}

		switch(curr_status.command) {
			case HALT:
				printf("\nExiting the program\n");
				exit(0);
				break;
			case READ:
				printf("\ninside read\n");
				setp = getSetName(&curr_status, set_names);
				if(curr_status.state != LEGAL) {
					printf("\nNo such set\n");
				} else {
					clearBits(setp); /* make sure the the set is clean and empty (we need all bits equal to 0 */
					while(curr_status.endOfLine != EOFLINE &&
						(num = getNum(&curr_status)) != ILLEGAL &&
						curr_status.state == LEGAL) {
						numToBit(setp, num);
					}
					if(curr_status.state != LEGAL) {
						clearBits(setp);
					} else {
						 setp -> init = 1; /* if the state is legal activate the set so other commands know
						//that the set is initiliazed*/
						printf("*setp -> init = %c|%d\n", setp -> init, setp -> init);
					}
					printBitSet(setp);
				}
				break;
			case PRINT:
				printf("\ninside print\n");
				setp = getSetName(&curr_status, set_names);
				if(setp -> init == 0) {
					printf("\nThe set was not initialized\n");
				} else if(curr_status.state != LEGAL) {
					printf("\nNo such set\n");
				} else {
					checkRestOfLine(&curr_status);
					if(curr_status.state != LEGAL) {
						printf("Illegal sequence");
					} else {
						printSet(setp);
					}
				}
				break;
			case UNION:
				/* we need to get the 3 sets which is the required number of arguments
				that UNION needs to receive */
				for(i = 0; i < SET_ARR_LEN && curr_status.state == LEGAL; i++) {
					sets[i] = getSetName(&curr_status, set_names); /* get the set */

					if(curr_status.state != LEGAL) /* if the state is not legal, the character that the user put 
					is not a valid set name */
						printf("No such set");

					/* we need to check that the first 2 sets were initialized (the last one doesn't have to be
					initialized  */
					if(i < SET_ARR_LEN - 1 && sets[i] -> init == 0) {
						curr_status.state = ILLEGAL;
						printf("\nThe set was not initialized\n");
					}
					printf("set %d = %c\n", i, curr_status.setName);

					/* we'll use advanceComma() to make sure the set names are separated by commas 
					and/or spaces */
					if(i < SET_ARR_LEN - 1 && curr_status.state == LEGAL)
						advanceComma(&curr_status);
				}

				if(curr_status.state == LEGAL){ /* if after advanceComma() the state is legal then we need
				to check if the rest of the line is legal. The only legal characters in the rest of the line
				can be spaces and newline */
					checkRestOfLine(&curr_status);

					if(curr_status.state != LEGAL) {
						/* if the rest of the line was illegal */
						printf("Illegal sequence");
					} else {
						/* after all the checks we should've received 2 initialized, legal sets and one initialized
						or not. we'll use new pointers left/right/endSet because we better understand the function of 
						each one from its name */
						left = sets[0];
						right = sets[1];
						endSet = sets[2];
						endSet -> init = 1; /* we need to turn on init field for the endSet otherwise print_set
						will not print it */

						/* we need to loop through the arr field of the first 2 sets and save the result in the
						endSet. using bitwise operator | will allow copy all "1"s from both sets */
						for(i = 0; i < CHAR_ARR_LEN; i++) {
							endSet -> arr[i] = left -> arr[i] | right -> arr[i];
						}
					}
				}
				break;
			case INTERSECT:
				receiver = processSetNames(curr_status, set_names, sets);

				if(*receiver != NULL) {
					left = sets[0];
					right = sets[1];
					endSet = sets[2];
					endSet -> init = 1; /* we need to turn on init field for the endSet otherwise print_set
					will not print it */
					for(i = 0; i < CHAR_ARR_LEN; i++) {
						endSet -> arr[i] = left -> arr[i] & right -> arr[i];
					}
				}
				

	

				break;
			default:
				printf("\ninside default\n");
				break;
		}

		
		// clearSet(setp);
		// numToBit(setp, 5);
		
		// getSetName(&curr_status, set_names);
		printf("\n");
		printStatus(&curr_status);
		printf("\n");


	}
	

	return 0;
}

