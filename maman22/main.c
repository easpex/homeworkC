#include "set.h"

int main() {
	char command_array[COMMAND_ARR_ROW_LEN][COMMAND_ARR_COL_LEN] = {"sub", "halt", "read", "union", "print", "intersect"};
	char _set_array[] = "_set";
	char set_names[] = "ABCDEF";
	char *commandp[COMMAND_ARR_ROW_LEN];
	int i;
	int num;
	set *setp;

	char line[MAX_LINE_LENGTH];
	Status curr_status;

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
				printf("Exiting the program");
				exit(0);
				break;
			case READ:
				printf("\ninside read\n");
				//clearStatus(&curr_status, curr_status.pos);
				setp = getSetName(&curr_status, set_names);
				if(curr_status.state != LEGAL) {
					printf("\nNo such set\n");
				} else {
					clearSet(setp); /* make sure the the set is clean and empty (we need all bits equal 0 */
					while(curr_status.endOfLine != EOFLINE &&
						(num = getNum(&curr_status)) != ILLEGAL &&
						curr_status.state == LEGAL) {
						numToBit(setp, num);
					}
					if(curr_status.state != LEGAL)
						clearSet(setp);

					printBitSet(setp);
				}
				break;
			default:
				printf("\ninside default\n");
				break;
		}

		// setp = &A;
		// clearSet(setp);
		// numToBit(setp, 5);
		
		// getSetName(&curr_status, set_names);
		printf("\n");
		printStatus(&curr_status);
		printf("\n");


	}
	

	return 0;
}

