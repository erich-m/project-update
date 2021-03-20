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
	//printf("push test 1\n");
	//malloc new struct Node
	//new_node is a pointer to memory for a node structure
	//malloc gives errors when using test3
	//test3: malloc.c:2385: sysmalloc: Assertion `(old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)' failed.
	struct Node * new_node = (struct Node*)malloc((sizeof(struct Node *)));//malloc returns the address of the memory block for the Node struct.// malloc enough space for 2 nodes? this fixed a valgrind invalid write size error
	if(new_node == NULL){
		fprintf(stderr, "push [Memory allocation error]: memory allocation for struct Node * new_node failed\n");
		exit(-1);
	}
	//printf("push test 2\n");
	//malloc width bytes of data. Store it in new_node->data
	new_node->data = (void*)malloc(width);//malloc returns an address to the block of memory for the data to point to
	if(new_node->data == NULL){
		fprintf(stderr, "push [Memory allocation error]: memory allocation for new_node->data failed\n");
		exit(-1);
	}
	//printf("push test 3\n");
	//copy width bytes of data from src to the address data
	//printf("push: after new_node has been created: %p\n",(void*)&(new_node->data));
	memcpy(new_node->data,src,width);
	//printf("push test 4\n");
	//set the next pointer of the struct to be equal to the value pointed to by list_ptr
	(new_node->next) = (*list_ptr);

	//printf("push test 5\n");
	//store the address of the structure in the pointer to that is pointed to by list_ptr
	
	//printf("\nlist_ptr address (should be constant):......... %p\n",(void*)&list_ptr);
	//printf("(*list_ptr) address (should also be constant):. %p\n",(void*)&(*list_ptr));
	//printf("\n(**list_ptr) address (should NOT be constant):.. %p\n",(void*)&(**list_ptr));
	(*list_ptr) = (new_node);
	//printf("push test 6\n");
	//printf("address of new_node:........................... %p\n",(void*)new_node);
	//printf("push: address of next node after adding to new list: %p\n",(void*)&(*list_ptr)->next);
	(performance->mallocs)++;
	(performance->writes)++;
}

//copy from head of list into dest
//if empty, print error
//otherwise, copy width bytes from the data pointer in the struct pointed to by the pointer tha list_ptr points to, into dest
//read in performance increases by 1
void readHead (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width){
	if(*list_ptr == NULL){//check if the list_ptr->pointer->head is NULL
		fprintf(stderr, "readHead [unaccessable memory error]: the memory that readHead is trying to access is empty\n");
		exit(-1);
	}
	//printf("readHead: before copying from data into dest: %p\n",(void*)&(*list_ptr)->data);
	memcpy(dest,(*list_ptr)->data,width);//copy width bytes of data from data from the structure pointed to by the pointer that list-ptr points to into dest
	
	(performance->reads)++;
}

//remove item from head of list
//if empty, print error
//otherwise, copy width bytes from data variable in the struct whose address is stored in the pointer pointed to by list_ptr, to the address given by dest
//it should update the pointer pointed to by list_ptr to the next node in the list and free the node struct that used to be first, free and read should be updated
void pop (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width){
	if(*list_ptr == NULL){//check if the list_ptr->pointer->head is NULL
		fprintf(stderr, "pop [unaccessable memory error]: the memory that pop is trying to access doesn't exist\n");
		exit(-1);
	}
	//printf("pop: before copying item from node into dest: %p\n",(void*)&(*list_ptr));
	memcpy(dest,(*list_ptr)->data,width);//copy width bytes of data from node->data into dest

	free((*list_ptr)->data);//free the data after transfering to dest
	(*list_ptr)->data = NULL;

	struct Node * current = (*list_ptr);
	(*list_ptr) = (*list_ptr)->next;
	free(current);
	current = NULL;

	(performance->reads)++;
	(performance->frees)++;
}

//return pointer to the pointer to the second item in a list
//if empty, print error
//otherwise, return address of the next pointer from the struct pointed to by the pointer that list_ptr points to
//update read
struct Node **next(struct Performance *performance, struct Node **list_ptr){
	if(*list_ptr == NULL){
		fprintf(stderr, "next [unaccessable memory error]: the memory next is trying to access cannot be reached\n");
		exit(-1);
	}
	//printf("next: address of next node before changing (*list_ptr) to (*list_ptr)->next: %p\n",(void*)&(*list_ptr)->next);
	//(*list_ptr) = (*list_ptr)->next;
	return &(*list_ptr)->next;
}

//return 1 if empty
//return 0 if not empty
int isEmpty(struct Performance *performance, struct Node **list_ptr){
	//printf("ENTERED isEMpty\n");
	//printf("isEmpty: address of (*list_ptr) checking if empty: %p\n",(void*)&(*list_ptr));
	if(*list_ptr != NULL){
		//printf("List is not empty\n");
		return(0);
	}
	//printf("list is empty\n");
	return(1);
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
	//printf("ENTERED APPEND\n");
	//printf("is empty in append %d\n",isEmpty(performance,list_ptr));
	while(isEmpty(performance,list_ptr) == 0){
		//printf("ENTERED while loop in APPEND\n");
		list_ptr = next(performance,list_ptr);
	}
	//printf("exited while loop in APPEND\n");
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