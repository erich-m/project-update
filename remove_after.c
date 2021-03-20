#include <stdlib.h>
#include <stdio.h>

#include "lab4_functions.h"

Node * remove_after (Node * node){
	Node * remove = (node == NULL) ? NULL : node->next;
	if(remove != NULL){
		node->next = remove->next;
		remove->next = NULL;
	}
	return remove;
}