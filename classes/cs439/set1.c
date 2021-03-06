#include <stdlib.h>
#include <stdio.h>

void hello(int x){
	if ( x != 0 ) {
		printf("Hello, world!\n");
		hello(--x);
	} else {
		return;
	}
}

int main(){
	int x;
	printf("Enter a number: ");
	scanf("%d", &x);
	hello(x);

	if (x == x) {
		printf("Goodbye!\n");
	}
}

/* 
Command used to compile: gcc -O set1.c -o set1
Command used in gdb: run, break, step, bt / Line number: 7 
For #5: Learn that the variable x doesn't change
*/