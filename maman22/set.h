#include <stdio.h> /* need it for printing output */
#include <stdlib.h> /* need it for exit() */
#include <string.h> /* need it for some built-in string functions */
#include <ctype.h> /* need it to check some primitive data types */

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

/* definition of set typedef */
typedef struct set {
	char arr[CHAR_ARR_LEN]; /* the char array which is bit array representation of a set of numbers */
	char init; /* the field  tells us if a set was initialized or not */
} set;

/* definition of Status typdef. the typedef plays central role in passing states and other information from
function to function */
typedef struct Status {
	int state; /* tells us whether a state is legal or illegal */
	int endOfLine; /* tells whether we reached end of the line */
	int command; /* tells us the current command */
	char setName; /* tells us the current set name */
	char * pos; /* holds the current char position within the string so the next function can start parsing data exactly
	where the previous function stopped */
} Status;

/* function prototypes */
void clearBits(set *s);
void setCommand(char *line, char *commandp[], char *_set_array, Status *st);
int getLine(char *s, int max);
set * getSetName(Status *st, char *set_names);
int getNum(Status *st);
void clearStatus(Status *st, char * line);
void numToBit(set *s, int num);
void printSet(set *p);
void setInitToZero();
void advanceComma(Status *st);
void checkRestOfLine(Status *st);
int processSetNames(Status curr_status, char * set_names, set * sets[]);
void printIllegalSequence();
int isEmpty(set *s);

set A, B, C, D, E, F; /* declare the sets globally so that both main() and set.c can use the typedef */
