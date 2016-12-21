#include "set.h"
set A, B, C, D, E, F;
int main() {
	char command_array[COMMAND_ARR_ROW_LEN][COMMAND_ARR_COL_LEN] = {"sub", "halt", "read", "union", "print", "intersect"};
	char _set_array[] = "_set";
	char *commandp[COMMAND_ARR_ROW_LEN];
	int i;
	char line[MAX_LINE_LENGTH];
	char *pline = line;


	for(i = 0; i < COMMAND_ARR_ROW_LEN; i++) {
		commandp[i] = command_array[i];
	}

	printf("%d\n", getLine(line, MAX_LINE_LENGTH));
	printf("commandp[i] = %c\n", commandp[2][0]);
	printf("line = %d\n", line);
	printf("%d\n", getCommand(line, commandp));
	//printCharArr(line);

	return 0;
}

