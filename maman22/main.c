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

		switch(curr_status.command) {
			case HALT:
				printf("\nExiting the program\n");
				exit(0);
				break;
			case READ:
				setp = getSetName(&curr_status, set_names);
				if(curr_status.state == LEGAL) {
					clearBits(setp); /* make sure the the set is clean and empty (we need all bits equal to 0 */
					while(curr_status.endOfLine != EOFLINE &&
						(num = getNum(&curr_status)) != ILLEGAL &&
						curr_status.state == LEGAL) {
						numToBit(setp, num);
					}
					if(curr_status.state != LEGAL) {
						clearBits(setp);
					} else {
						 setp -> init = ON; /* if the state is legal activate the set so other commands know
						that the set is initiliazed*/
					}
				}
				break;
			case PRINT:
				setp = getSetName(&curr_status, set_names);
				if(curr_status.state == LEGAL) {
					checkRestOfLine(&curr_status);

					if(curr_status.state == LEGAL) {
					 	if(setp -> init == OFF) { 
							printf("\nThe set %c was not initialized\n", curr_status.setName);					
						} else {
							printSet(setp);
						}
					}
				}
				break;
			case UNION:
				if(processSetNames(curr_status, set_names, sets)) {
					left = sets[FIRST];
					right = sets[SECOND];
					endSet = sets[LAST];
					 /* we need to turn on init field for the endSet otherwise print_set
					will not print it */
					endSet -> init = ON;

					for(i = 0; i < CHAR_ARR_LEN; i++) {
						endSet -> arr[i] = left -> arr[i] | right -> arr[i];
					}
				}
				break;
			case INTERSECT:
				if(processSetNames(curr_status, set_names, sets)) {
					left = sets[FIRST];
					right = sets[SECOND];
					endSet = sets[LAST];
					 /* we need to turn on init field for the endSet otherwise print_set
					will not print it */
					endSet -> init = ON;

					for(i = 0; i < CHAR_ARR_LEN; i++) {
						endSet -> arr[i] = left -> arr[i] & right -> arr[i];
					}
				}
				break;
			case SUB:
				if(processSetNames(curr_status, set_names, sets)) {
					left = sets[FIRST];
					right = sets[SECOND];
					endSet = sets[LAST];
					 /* we need to turn on init field for the endSet otherwise print_set
					will not print it */
					endSet -> init = ON;

					for(i = 0; i < CHAR_ARR_LEN; i++) {
						endSet -> arr[i] = left -> arr[i] & ~right -> arr[i];
					}
				}
				break;
			default:
				printf("\nNo such command\n");
		} /* end of switch */
	} /* end of while */
	return 0;
} /* end of main */

