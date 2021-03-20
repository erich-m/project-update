#include <stdio.h>
#include <stdlib.h>

#include "lab4_functions.h"

void display_list (Node * head,int version,int size){
	Node *p = head;
	int s  = 0;
	if(version == 0){
		printf("\nUnsorted List:\n");
	}else if(version == 1){
		printf("\nSorted List by Key 1:\n");
	}else if(version == 2){
		printf("\nSorted List by Key 2:\n");
	}
	while(p != NULL && s < size){
		if(version == 0){
			printf("< %d, %f, %f >\n",p->value,p->key1,p->key2);
			p = p->next;
		}else if(version == 1){
			printf("[ %d, %f, %f ]\n",p->value,p->key1,p->key2);
			p = p->sort1;
		}else if (version == 2){
			printf("{ %d, %f, %f }\n",p->value,p->key1,p->key2);
			p = p->sort2;
		}
		s++;
	}
	printf("\n");
}