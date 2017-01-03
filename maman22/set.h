#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CHAR_ARR_LEN 16
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
#define EOFLINE 1
#define MAX_DIGITS 3
#define HIGH_LIM 127
#define LOW_LIM 0
#define LEGAL 1
#define ILLEGAL -1
#define BIT_IN_CHAR 8
#define DOUBLE_DIGIT 10
#define NUMS_PER_LINE 16
#define SET_ARR_LEN 3
#define ON 1
#define OFF 0
#define FIRST 0
#define SECOND 1
#define LAST 2


typedef struct set {
	char arr[CHAR_ARR_LEN];
	char init;
} set;

typedef struct Status {
	int state;
	int endOfLine;
	int command;
	char setName;
	char * pos;
} Status;

void print_binary(int n);
void printIntSet(set *s);
void printBitSet(set *p);
void clearBits(set *s);
void setCommand(char *line, char *commandp[], char *_set_array, Status *st);
int getLine(char *s, int max);
void printCharArr(char *s);
void ungetch(int c);
int getch(void);
void test(char **p);
set * getSetName(Status *st, char *set_names);
void printStatus(Status *st);
int getNum(Status *st);
void clearStatus(Status *st, char * line);
void numToBit(set *s, int num);
void printSet(set *p);
void setInitToZero();
void advanceComma(Status *st);
void checkRestOfLine(Status *st);
int processSetNames(Status curr_status, char * set_names, set * sets[]);
void printString(char *s);
void printIllegalSequence();

set A, B, C, D, E, F;
