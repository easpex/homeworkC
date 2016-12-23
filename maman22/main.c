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


	char line[MAX_LINE_LENGTH];
	Status curr_status;

	setInitToZero();

	/* init commandp */
	for(i = 0; i < COMMAND_ARR_ROW_LEN; i++) {
		commandp[i] = command_array[i];
	}

	while(getLine(line, MAX_LINE_LENGTH) > 0) {
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
					printSet(setp);
				}
				break;
			case UNION:
				for(i = 0; i < SET_ARR_LEN && curr_status.state == LEGAL; i++) {
					sets[i] = getSetName(&curr_status, set_names);

					if(curr_status.state != LEGAL)
						printf("No such set");

					if(sets[i] -> init == 0) {
						curr_status.state = ILLEGAL;
						printf("\nThe set was not initialized\n");
					}
					printf("set %d = %c\n", i, curr_status.setName);

					if(i < SET_ARR_LEN - 1 && curr_status.state == LEGAL)
						advanceComma(&curr_status);
				}

					if(curr_status.state == LEGAL){
						checkRestOfLine(&curr_status);

						if(curr_status.state != LEGAL)
							printf("Illegal sequence");
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

