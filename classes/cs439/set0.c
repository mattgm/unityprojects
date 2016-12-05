/*
Pair programming is a technique where two programmers work together side by side to achieve better efficiency,
empirically suppored by surveys and anecdotal evidence. The guidelines for pair programming are similar 
to the ethical lessons kindergaartners might learn. A programmer needs to be conscientious of their partner by 
sharing everything, including takingblame for when things go wrong.  They will take turns "driving" (handling 
the keyboard/mouse) while the other is reviewing the code as it is created. Throughout the process the 
programmers will push each other to stay focused on and keep a positive mentality about the task at hand. 
Programmers should also move furniture to set up a convenient side-by-side environment, approach pair programming
without skepticism, review or rewrite code written alone, take an occasional break and live a balanced life,
and understand how two people working together can supplement each other's brain power and capabilities. 
*/

#include <stdlib.h>
#include <stdio.h>

struct node {
	int data;
	struct node *prev;
	struct node *next;
};

struct node* add(struct node *n, int data){
	struct node *result = n;

	while (n->next) {
		if (n->data < data) {
			n = n->next;
		}
	}

	struct node *newNode = malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = n->next;
	if (n->prev == NULL) {
		return newNode;
	} else {
		n->next = newNode;
	}
	newNode->prev = n;
	newNode->next->prev = newNode;

	return result;
}

struct node* removeNode(struct node *n, struct node *del){
	struct node *result = n;
	if (n == del) result = n->next;

	while (n != del) {
		n = n->next;
	}

	n->prev->next = n->next;
	return result;
}

int main() {
	int i;
	struct node *x = malloc( sizeof( struct node) );
	x->prev = NULL;
	x->next = NULL;
	x->data = 1;
	for (i = 2; i <= 5; i++) {
		x = add(x, i);
	}

	while (x) {
		printf( "%d\n", x->data);
		x = x->next;
	}
}