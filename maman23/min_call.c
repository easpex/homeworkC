#include <stdio.h>
#include <stdarg.h>
#define UNINITIALIZED -2
#define END_OF_INPUT -1


int min_call(int x, ...);

int main() {

	printf("min = %d\n",min_call(-1));
	printf("min = %d\n",min_call(100, -1));
	printf("min = %d\n",min_call(54, 23, 66, 78, 90, -1));
	printf("min = %d\n",min_call(9,8,87,2,-1));
	printf("min = %d\n",min_call(-1));

	return 0;
}

int min_call(int x, ...) {
	va_list p;

	int curr;
	int next = UNINITIALIZED;
	static int min = UNINITIALIZED;

	va_start(p, x);
	curr = x;

	while(curr != END_OF_INPUT && next != END_OF_INPUT) {
		printf("inside, curr = %d | next = %d\n", curr, next);
		next = va_arg(p, int);
		printf("inside, curr = %d | next = %d\n", curr, next);
		if(curr > next && next != END_OF_INPUT) {
			curr = next;
		}
	}

	va_end(p);

	if(min == UNINITIALIZED && curr != END_OF_INPUT) {
		min = curr;
		return min;
	} else if(min > curr && curr != END_OF_INPUT) {
		min = curr;
		return min;
	} else {
		return min;
	}
}
