#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//Node structure
//data is a pointer to the data for this node
//next is a pointer to the next node in the list (or null)
struct Node{
	void *data;
	struct Node *next;
};

//Performance structure
//keeps track of the number of reads, writes, mallocs, and frees used in the functions called
struct Performance{
	unsigned int reads;
	unsigned int writes;
	unsigned int mallocs;
	unsigned int frees;
};

//Allocates memory for the performance structure and sets default values to 0
struct Performance *newPerformance();

//add an item to head of list
//malloc new node struct
//copy width bytes from src to data in node
//set next to list_ptr
//store the address of the structure in the pointer that is pointed to by list_ptr
void push (struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width);

//copy from head of list into dest
//if empty, print error
//otherwise, copy width bytes from the data pointer in the struct pointed to by the pointer tha list_ptr points to, into dest
//read in performance increases by 1
void readHead (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width);

//remove item from head of list
//if empty, print error
//otherwise, copy width bytes from data variable in the struct whose address is stored in the pointer pointed to by list_ptr, to the address given by dest
//it should update the pointer pointed to by list_ptr to the next node in the list and free the node struct that used to be first, free and read should be updated
void pop (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width);

//return pointer to the pointer to the second item in a list
//if empty, print error
//otherwise, return address of the next pointer from the struct pointed to by the pointer that list_ptr points to
//update read
struct Node **next(struct Performance *performance, struct Node **list_ptr);

//return 1 if empty
//return 0 if not empty
int isEmpty(struct Performance *performance, struct Node **list_ptr);

//pop items off the list until list isEmpty
void freeList(struct Performance *performance, struct Node **list_ptr);

//use next and readHead to find Node i (i=0) and retrieve data from pos
void readItem(struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width);

//add element to end of list
//call next until isempty
//then push to add item to end of list
void appendItem(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width);

//use next and push to insert a node at given index
//if index is 0, the item will be inserted at the head of the list
void insertItem (struct Performance *performance,struct Node **list_ptr, unsigned int index, void *src, unsigned int width);

//use insertitem to add data at 0
void prependItem(struct Performance *performance,struct Node **list_ptr, void *src, unsigned int width);

//use pop and next to remove item from given index
void deleteItem(struct Performance *performance,struct Node **list_ptr, unsigned int index);

//use readHead anf call next
//use compar function to compare each data
//0 uindicates a match. non-zero is not a match
//no match, return -1
int findItem(struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target,unsigned int width);

#endif