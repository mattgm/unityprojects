
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/*---------------------------Stack-----------------------/
/														 /
/-------------------------------------------------------*/

#define STACK_MAX 100
struct Stack {
    char*     data[STACK_MAX];
    int     size;
};
typedef struct Stack Stack;


void Stack_Init(Stack *S)
{
    S->size = 0;
}

char* Stack_Top(Stack *S)
{
    if (S->size == 0) {
        return NULL;
    } 

    return S->data[S->size-1];
}

void Stack_Push(Stack *S, char* d)
{
    if (S->size < STACK_MAX)
        S->data[S->size++] = d;
    else
        return;
}

void Stack_Pop(Stack *S)
{
    if (S->size == 0)
        return;
    else
        S->size--;
}

/************************************************************/


int main(int argc, char* argv[]) {
	printf("   .globl compute\n");
	printf("\n");
	printf("compute:\n");

	int n;

	Stack *vars = malloc(sizeof *vars);
	Stack_Init(vars);
	char* r10 = "r10";
	char* r11 = "r11";
	bool cflag = true;
	int count = 0;

	for (n = 0; n < argc; n++) {

		if (count >= 2) {

		}

		if (argv[n][0] == 'x') {
			printf("   pushq %%rdi\n");
			cflag ? Stack_Push(vars, r11) : Stack_Push(vars, r10);
			cflag = !cflag;
			count++;
		}

		if (argv[n][0] == 'y') {
			printf("   pushq %%rsi\n");
			cflag ? Stack_Push(vars, r11) : Stack_Push(vars, r10);
			cflag = !cflag;
			count++;
		}

		if (argv[n][0] == 'z') {
			printf("   pushq %%rdx");
			cflag ? Stack_Push(vars, r11) : Stack_Push(vars, r10);
			cflag = !cflag;
			count++;
		}

		int check = argv[n][0] - '0';
		if ((check >= 0 && check <= 9) || (argv[n][0] == '-' && argv[n][1])) {
			char* num = malloc(strlen(argv[n]) + 1);
			num[0] = '$';
			strncat(num, argv[n], strlen(argv[n]));
			printf("   pushq %s\n", num);
			cflag ? Stack_Push(vars, r11) : Stack_Push(vars, r10);
			cflag = !cflag;
			count++;
		}

		if (argv[n][0] == '+') {
			char* arg1 = Stack_Top(vars);
			Stack_Pop(vars);
			printf("   popq %%%s\n", arg1);
			char* arg2 = Stack_Top(vars);
			Stack_Pop(vars);
			printf("   popq %%%s\n", arg2);
			printf("   addq %%%s, %%%s\n", arg1, arg2);
			Stack_Push(vars, arg2);
			printf("   pushq %%%s\n", arg2);
			cflag = !cflag;
		}

		if (argv[n][0] == '-' && !argv[n][1]) {
			char* arg1 = Stack_Top(vars);
			Stack_Pop(vars);
			printf("   popq %%%s\n", arg1);
			char* arg2 = Stack_Top(vars);
			Stack_Pop(vars);
			printf("   popq %%%s\n", arg2);
			printf("   subq %%%s, %%%s\n", arg1, arg2);
			Stack_Push(vars, arg2);
			printf("   pushq %%%s\n", arg2);
			cflag = !cflag;
		}

		if (argv[n][2] == '*') {
			char* arg1 = Stack_Top(vars);
			Stack_Pop(vars);
			printf("   popq %%%s\n", arg1);
			char* arg2 = Stack_Top(vars);
			Stack_Pop(vars);
			printf("   popq %%%s\n", arg2);
			printf("   imulq %%%s, %%%s\n", arg1, arg2);
			Stack_Push(vars, arg2);
			printf("   pushq %%%s\n", arg2);
			cflag = !cflag;
		}

		
	}

	printf("   popq %%rax\n");
	printf("   retq\n");

}








