#include <stdio.h> /* need it for output */
#include <stdarg.h> /* need it for working with variable length arguments list */
#include <limits.h> /* need it for INT_MAX define */
#define END_OF_INPUT -1 /* -1 signifies the end of arguments for min_call() function */


int min_call(int x, ...); /* function prototype */

int main() {
	/* calling min_call() function repeatedly in order to test what is the current minimum value */
	printf("min = %d\n",min_call(-1)); /* printing the result of min_call() */
	printf("min = %d\n",min_call(100, -1));
	printf("min = %d\n",min_call(54, 23, 66, 78, 90, -1));
	printf("min = %d\n",min_call(9,8,87,0,-1));
	printf("min = %d\n",min_call(-1));
	
	return 0; /* return 0 if main() finished normally */
}

/* the function receive a variable arguments list of integers in the range from 0 to 100 . 
The last argument is signified by -1. The function then checks which integer is the smallest from the input.
The minimum integer is saved as a static variable therefore it is accessible to future calls to the function.  

@param - int x - the first argument of the function. Other possible arguments are all integers.
@return - int - returns the smallest integer from the supplied list of arguments.

Algorithm:
There's three int variable inside the function that are used to check for the minimum: curr is initialized to the first
integer of the list of integers the function receives. next is inititalized the the next one (if end of input is not
yet reached). min is declared as a static variable so that future calls to min_call() would have access to its value.
min is also initialized to INT_MAX (which means it's out of range of 0 to 100). We need this because if it's the first
call to min_call() then we need to give min whatever value from the variable arguments list. If it's not the first call
then we need to compare the previous min with the current min.

while loop is run through the variable arguments list until -1 is reached. inside while we check each iteration if next
is smaller than next if yes then curr becomes next (minimum). 

lastly, we check whether previous min is greater than the current min and if yes update it to the current.

if all of the calls to min_call() are of the following type: "min_call(-1)" then the value  returned by the function
will always be INT_MAX (this was suggested in the forum: http://opal.openu.ac.il/mod/ouilforum/view.php?f=188595#)
*/


int min_call(int x, ...) {
	/* declare va_list struct */
	va_list p;

	int curr; /* receives the first value of the variable arguments list */
	int next = INT_MAX; /* initialized to INT_MAX initially however will be update after future calls that contain
	integers other than -1 */

	static int min = INT_MAX; /* initialized to INT_MAX initially however will be update after future calls that contain
	integers other than -1. min records the previous min and is updated if the current min is smaller */

	va_start(p, x); /* get the first value of va_list */
	curr = x; 

	/* run the while loop until we reach -1 that is the end of va_list */
	while(curr != END_OF_INPUT && next != END_OF_INPUT) {
		next = va_arg(p, int); /* get the value of the next int in the va_list */
		if(curr > next && next != END_OF_INPUT) {
			/* if the current value is bigger than the next value, update curr to next */
			curr = next;
		}
	}

	va_end(p); /* we can now free va_list because we reached the end of va_list */

	if(min == INT_MAX && curr != END_OF_INPUT) {
		/* the min was never initialized to an int from va_list so we need to initialize it now */
		min = curr;
		return min;
	} else if(min > curr && curr != END_OF_INPUT) {
		/* min was initialized before the new min is smaller, so we need to update the min */
		min = curr;
		return min;
	} else {
		/* va_list didn't contain integers other than -1 */
		return min;
	}
}
