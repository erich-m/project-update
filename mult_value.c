#include <stdio.h>
#include <stdlib.h>

#include "lab4_functions.h"

Node * mult_value (Node * head,int factor){
	Node * temp = head;
	Node * to_mult = temp;
	int n = 1;
	while(temp!=NULL){
		if(n%3 == 0){
			temp->value = temp->value * factor;
		}
		temp = temp->next;
		n++;
	}
	return(to_mult);
}