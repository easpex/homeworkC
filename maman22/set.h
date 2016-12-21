#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARR_LEN 16
#define MAX_CHARS_IN_COMMAND 9
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


typedef struct set {
	char arr[ARR_LEN];
} set;

void print_binary(int n);
void printIntSet(set *s);
void printBitSet(set *p);
void clearSet(set *s);
int getCommand(char *line, char *commandp[]);
int getLine(char s[], int max);
void printCharArr(char s[]);
void ungetch(int c);
int getch(void);
