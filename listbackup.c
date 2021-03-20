#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

//Allocates memory for the performance structure and sets default values to 0
struct Performance *newPerformance(){
	struct Performance *perf;

	perf = malloc(sizeof(struct Performance));
	if(perf == NULL){
		fprintf(stderr, "newPerformance [Memory Allocation Unsuccessful]: Memory allocation for struct Performance failed\n");
		exit(-1);
	}
	perf->reads = 0;
	perf->writes = 0;
	perf->mallocs = 0;
	perf->frees = 0;

	return (perf);
}

//add an item to head of list
//malloc new node struct
//copy width bytes from src to data in node  
//set next to list_ptr
//store the address of the structure in the pointer that is pointed to by list_ptr
void push (struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width){
	struct Node * new_node = (struct Node*)malloc(sizeof(struct Node));//malloc new node structure
	if(new_node == NULL){
		fprintf(stderr, "push [Memory allocation error]: Memory allocation for struct new_node failed\n");
		exit(-1);
	}
	
	new_node->data = malloc(sizeof(width));
	if(new_node->data == NULL){
		fprintf(stderr, "push [Memory allocation error]: Memory allocation for new_node->data failed\n");
		exit(-1);
	}
	memcpy(new_node->data,src,width);
	new_node->next = (*list_ptr);
	(*list_ptr) = new_node;

	(performance->writes)++;
	(performance->mallocs)++;
}

//copy from head of list into dest
//if empty, print error
//otherwise, copy width bytes from the data pointer in the struct pointed to by the pointer tha list_ptr points to, into dest
//read in performance increases by 1
void readHead (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width){
	if (*list_ptr == NULL){
		fprintf(stderr, "readHead [Unaccessable data error]: list_ptr cannot be read because it is empty\n");
		exit(-1);
	}
	memcpy(dest,(*list_ptr)->data,width);
	
	(performance->reads)++;
}

//remove item from head of list
//if empty, print error
//otherwise, copy width bytes from data variable in the struct whose address is stored in the pointer pointed to by list_ptr, to the address given by dest
//it should update the pointer pointed to by list_ptr to the next node in the list and free the node struct that used to be first, free and read should be updated
void pop (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width){
	if(*list_ptr == NULL){
		fprintf(stderr, "pop [Unaccesable data error]: pop cannot remove anything because list_ptr is empty\n");
		exit(-1);
	}

	memcpy(dest,(*list_ptr)->data,width);//copy data into dest
	free((*list_ptr)->data);//free data
	(*list_ptr)->data = NULL;//free data
	struct Node * current_head = (*list_ptr);//set current head to the (*list_ptr)
	(*list_ptr) = (*list_ptr)->next;
	free((current_head));
	(current_head) = NULL;
	//copy data into dest
	//free data
	//set a new node to the next item in the list.
	//free the head of the list
	//set list_ptr to the new head of the list

	(performance->reads)++;
	(performance->frees)++;
}

//return pointer to the pointer to the second item in a list
//if empty, print error
//otherwise, return address of the next pointer from the struct pointed to by the pointer that list_ptr points to
//update read
struct Node **next(struct Performance *performance, struct Node **list_ptr){
	if(*list_ptr == NULL){
		fprintf(stderr, "next [Unaccesssable data error]: list_ptr is empty and the next element cannot be retrieved\n");
		exit(-1);
	}
	(performance->reads)++;

	return (&(*list_ptr)->next);
}

//return 1 if empty
//return 0 if not empty
int isEmpty(struct Performance *performance, struct Node **list_ptr){
	if(*list_ptr == NULL){//return 1 if empty
		return(1);
	}
	return(0);
}

//pop items off the list until list isEmpty
void freeList(struct Performance *performance, struct Node **list_ptr){
	while(isEmpty(performance,list_ptr) != 1){
		pop(performance,list_ptr,NULL,0);
	}
}

//use next and readHead to find Node i (i=0) and retrieve data from pos
void readItem(struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width){
	int i = 0;
	while(i < index){
		list_ptr = next(performance,list_ptr);
		i++;
	}
	readHead(performance,list_ptr,dest,width);
}

//add element to end of list
//call next until isempty
//then push to add item to end of list
void appendItem(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width){
	//printf("is empty in append %d\n",isEmpty(performance,list_ptr));
	while(isEmpty(performance,list_ptr) == 0){
		list_ptr = next(performance,list_ptr);
	}
	push(performance,list_ptr,src,width);
}

//use next and push to insert a node at given index
//if index is 0, the item will be inserted at the head of the list
void insertItem (struct Performance *performance,struct Node **list_ptr, unsigned int index, void *src, unsigned int width){
	int i = 0;
	while(i < index){
		list_ptr = next(performance,list_ptr);
		i++;
	}
	push(performance,list_ptr,src,width);
}

//use insertitem to add data at 0
void prependItem(struct Performance *performance,struct Node **list_ptr, void *src, unsigned int width){
	insertItem(performance,list_ptr,0,src,width);
}

//use pop and next to remove item from given index
void deleteItem(struct Performance *performance,struct Node **list_ptr, unsigned int index){
	int i = 0;
	while(i < index){
		list_ptr = next(performance,list_ptr);
		i++;
	}
	pop(performance,list_ptr,NULL,0);
}

//use readHead anf call next
//use compar function to compare each data
//0 uindicates a match. non-zero is not a match
//no match, return -1
int findItem(struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width){
	while(isEmpty(performance,list_ptr) == 0){//while list is not empty
		unsigned char temp[width];
		readHead(performance,list_ptr,temp,width);
		if(compar(temp,target) == 0){
			return(0);
		}
		list_ptr = next(performance,list_ptr);
	}
	return(-1);
}