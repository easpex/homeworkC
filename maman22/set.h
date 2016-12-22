#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARR_LEN 16
#define MAX_LINE_LENGTH 1000
#define BUFFER_SIZE 100
#define SUB 0
#define HALT 1
#define READ 2
#define UNION 3
#define PRINT 4
#define INTERSECT 5
#define COMMAND_ARR_ROW_LEN 6
#define COMMAND_ARR_COL_LEN 9
#define EOFLINE 0
#define MAX_DIGITS 3
#define HIGH_LIM 127
#define LOW_LIM 0


typedef struct set {
	char arr[ARR_LEN];
} set;

typedef struct Status {
	int state;
	int command;
	char setName;
	char * pos;
} Status;

void print_binary(int n);
void printIntSet(set *s);
void printBitSet(set *p);
void clearSet(set *s);
int getCommand(char *line, char *commandp[], char *_set_array);
int getLine(char *s, int max);
void printCharArr(char *s);
void ungetch(int c);
int getch(void);
int getSetName(char *pset, char *set_names);
int getNum(char *pline);
int getNum(char *pline);
void test(char **p);
void setSetName(Status *st, char *set_names);
void printStatus(Status st);
