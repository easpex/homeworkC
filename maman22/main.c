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
	Status current;
	Status *st = &current;

	/* init commandp */
	for(i = 0; i < COMMAND_ARR_ROW_LEN; i++) {
		commandp[i] = command_array[i];
	}

	printf("%d\n", getLine(pline, MAX_LINE_LENGTH));
	current.pos = pline;

	//printf("!!*st -> pos = %c\n", ++(*st -> pos));
	//printf("!!*st -> pos = %c\n", *st -> pos);
	printf("current.pos\n");
	printCharArr(current.pos);

	printf("getNum = %d\n", getNum(&current));


	//setCommand(line, commandp, _set_array, &current);
	//setSetName(&current, set_names);
	
	printCharArr(current.pos);
	printStatus(current);

	
	
	printf("-----misc----");
	test(&pline);
	printf("test = %c\n", *pline);
	printf("commandp[i] = %c\n", commandp[2][0]);
	
	i = 1;
			printf("%d\n", (int) strlen(_set_array));



	

	return 0;
}

