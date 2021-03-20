#include <stdlib.h>
#include <stdio.h>

#include "lab4_functions.h"

Node *remove_node (Node *head,Node * node){
	Node * prev = find_before(head,node);
	return remove_after(prev);
}