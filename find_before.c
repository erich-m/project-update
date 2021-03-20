#include <stdlib.h>
#include <stdio.h>

#include "lab4_functions.h"

Node * find_before(Node * head, Node * node){
	Node * prev = head;
	while(prev != NULL && prev -> next != node){
		prev = prev->next;
	}
	return prev;
}
