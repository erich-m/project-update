#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lab4_functions.h"

Node * create_nodes (int size){/*function that creates a linked list of given size*/
	int i = 0;
	Node * head = NULL;
	Node * temp = NULL;
	Node * p = NULL;

	for(i = 0;i < size;i++){
		/*create 1 node*/
		temp = malloc(sizeof(Node));
		temp->value  = (int)rand_double(0,10);
		temp->key1 = rand_double(10,50);
		temp->key2 = rand_double(50,90);
		temp->sort1 = NULL;
		temp->sort2 = NULL;
		temp->next = NULL;

		if(head  == NULL){/*if the list is empty, then set temp to the head*/
			head = temp;
		}else{/*add the newly created node to the end of the list*/
			p = head;
			/*iterate through the nodes to the end of the list*/
			while(p->next != NULL){
				p = p->next;
			}
			p->next = temp;
		}
	}

	return(head);
}