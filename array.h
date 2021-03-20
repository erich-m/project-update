/*Author: Erich MacLean
Due Thursday, October 1, 2020
Completed Tuesday September 29, 2020*/
#ifndef _ARRAY_H
#define _ARRAY_H
struct Array{
	unsigned int width;//represents the size of bytes of each element in the array
	unsigned int nel;//represents the number of elements currently in the array
	unsigned int capacity;//represents the total number of elements that can be stored in the array
	void *data;//Pointer to the contents of the array
};

struct Performance{//used to track the number of reads, writes, mallocs, frees
	unsigned int reads;
	unsigned int writes;
	unsigned int mallocs;
	unsigned int frees;
};

/*return the address of the structure.
set read, write, malloc, and free attributes to 0*/
struct Performance *newPerformance();

/*Allocate sufficient memory for an array struct
set the width and capacity attributes
set nel to 0
width*capacity=number of bytes for data size
Add to performance->mallocs
return an Array pointer to the struct
Use stderr is malloc fails*/
struct Array *newArray (struct Performance *performance, unsigned int width, unsigned int capacity);

/*if index is greater than or equal to array->nel, go to stderr
otherwise, copy array->width bytes from memory address array->data offset by index(multiplied by array->width) to mem address given by dest
add one to performance->reads*/
void readItem(struct Performance *performance, struct Array * array, unsigned int index, void *dest);

/*if index exceeds array->nel or array->capacity, use stderr
otherwise, copy array->width bytes from the memory address given by src to the mem address array->data, offset by the index(multiplied by array->width) 
if index equals array->nell, add one to array->nel
add one to performance->writes*/
void writeItem (struct Performance *performance, struct Array *array, unsigned int index, void *src);

/*if array->nel==0, function should print error.
otherwise array->nel - 1*/
void contract(struct Performance *performance, struct Array *array);

/*function will free array->data, and array itself.
add to performance->frees*/
void freeArray(struct Performance * performance, struct Array *array);

/*Add an element to the end of the array (at position array->nel.
call writeItem*/
void appendItem(struct Performance *performance, struct Array *array, void *src);

/*use readItem and write item to move all elements in array given by index and higher, one position further, write given data at index in array*/
void insertItem (struct Performance * performance,struct Array *array,unsigned int index, void *src);

/*insert item at index 0 using insertItem*/
void prependItem(struct Performance *performance, struct Array *array,void *src);

/*use readItem and write item to move elements by index+1 one position forward then use contract function to remove duplitcate entry*/
void deleteItem(struct Performance * performance , struct Array * array,unsigned int index);

/*retrieve elements from array using readitem. Use compar function to target and the read item. 0 indicates a match*/
int findItem(struct Performance *performance,  struct Array *array, int (*compar)(const void *, const void*),void *target);

/*retirieve elements with readItem start with middle item rounded down. each element, usre compar function. if compar <0, repeat search on greater elements. other wise, round down. (binary search)*/
int searchItem(struct Performance *performance,struct Array * array, int (*compar)(const void *, const void *),void *target);
#endif