#include "set.h"
set A, B, C, D, E, F;
int main() {
	char command_array[COMMAND_ARR_ROW_LEN][COMMAND_ARR_COL_LEN] = {"sub", "halt", "read", "union", "print", "intersect"};
	char _set_array[] = "_set";
	char set_names[] = "ABCDEF";
	char *commandp[COMMAND_ARR_ROW_LEN];
	int i;
	char line[MAX_LINE_LENGTH];
	char *pline = line;
	char *pset = _set_array;


	for(i = 0; i < COMMAND_ARR_ROW_LEN; i++) {
		commandp[i] = command_array[i];
	}

	printf("%d\n", getLine(pline, MAX_LINE_LENGTH));
	printf("commandp[i] = %c\n", commandp[2][0]);
	printf("line = %d\n", line);

	i = 1;
			printf("%d\n", strlen(_set_array));



	printf("%d\n", getCommand(line, commandp, _set_array));
	printCharArr(line);
	printf("getSetName = %d\n", getSetName(&line[2], set_names)); 

	return 0;
}

