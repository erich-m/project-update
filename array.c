/*Author: Erich MacLean
Due Thursday, October 1, 2020
Completed Tuesday September 29, 2020*/
#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
struct Array *newArray (struct Performance *performance, unsigned int width, unsigned int capacity){
	struct Array *array;

	array = malloc(sizeof(struct Array));
	if(array == NULL){
		fprintf(stderr, "newArray [Memory Allocation Unsuccessful]: Memory allocation for struct Array failed\n");
		exit(-1);
	}
	array->width = width;
	array->capacity = capacity;

	array->data = malloc(width*capacity);
	if(array->data == NULL){
		fprintf(stderr, "newArray [Memory Allocation Unsuccessful]: Memory allocation for the data field of struct array failed\n");
		exit(-1);
	}
	(performance->mallocs)++;
	return (array);
}
void readItem(struct Performance *performance, struct Array * array, unsigned int index, void *dest){//index is the index of the data we are trying to retrieve//figure out where in array->data the element is. (index tells which set of bytes.) 
	if(index >= array->nel){//if the index is greater than or equal to the length of the array for reading, genrate an error
		fprintf(stderr, "readItem [Unreachable value]: The specified index {%u} does not exist\n",index);
		exit(-1);
	}
	unsigned char * arrayData;//temproary pointer to data that can be accessed by byte number
	arrayData = array->data;

	unsigned char * destination = dest;;
	//copy bytes using the byte number relative to the pointer temp//use memcpy
	for(int b = 0;b < array->width;b++){
		//byte number is b+(index*width)
		destination[b] = arrayData[b+(index*(array->width))];
	}
	dest = destination;

	(performance->reads)++;
}
void writeItem (struct Performance *performance, struct Array *array, unsigned int index, void *src){
	unsigned char * source;//Set source to a char array to make the bytes accessable
	source = src;

	if(index > array->nel || index >= array->capacity){
		fprintf(stderr, "writeItem [Unreachable value]: The specified index {%u} does not exist\n",index);
		exit(-1);
	}
	//if index is occupied, overwrite it
	//if the element is one elment past the occupied element (equal to array->nel) add the data to the end o fht earray and increase nel by 1
	//if the element is NOT adjacent to the current elements, flag as an error

	unsigned char * arrayData;//make the bytes of array data accessable
	arrayData = array->data;

	for(int b = 0;b < array->width;b++){//loop through the bytes in source
		//byte number is b+(index*width0)
		arrayData[b+(index*array->width)] = source[b];
	}
	array->data = arrayData;

	if(index == array->nel){
		(array->nel)++;
	}
	(performance->writes)++;
}
void contract(struct Performance *performance, struct Array *array){
	if(array->nel == 0){
		fprintf(stderr, "contract [Empty Array]: The data field of array is empty and cannot be contracted\n");
		exit(-1);
	}
	(array->nel)--;
}
void freeArray(struct Performance * performance, struct Array *array){
	free(array->data);
	array->data = NULL;
	free(array);
	array= NULL;
	(performance->frees)++;
}
void appendItem(struct Performance *performance, struct Array *array, void *src){
	writeItem(performance,array,array->nel,src);//writes an item at index array->nel
}
void insertItem (struct Performance * performance,struct Array *array,unsigned int index, void *src){
	unsigned char * temp[array->width];
	for(int i = 0;i < (array->nel-index);i++){
		readItem(performance,array,array->nel - 1 - i,temp);
		writeItem(performance,array,array->nel - i,temp);
	}
	writeItem(performance,array,index,src);
}
void prependItem(struct Performance *performance, struct Array *array,void *src){
	insertItem (performance,array,0,src);
}
void deleteItem(struct Performance * performance , struct Array * array,unsigned int index){
	unsigned char * temp[array->width];
	for(int i = 0;i < (array->nel - index - 1);i++){
		readItem(performance,array,index + i + 1,temp);
		writeItem(performance,array,index + i,temp);
	}
	contract(performance,array);
}
int findItem(struct Performance *performance,  struct Array *array, int (*compar)(const void *, const void*),void *target){
	//USE READITEM TO GET ARRAY ELEMENT!!!!!
	//loop through the array->data content
	//use readitem to read the element at any particular index
	//compare it to the target
	//return either the index of the found element or -1
	unsigned char * temp[array->width];

	for(int i = 0;i < array->nel;i++){//loop through the array->data
		readItem(performance,array,i,temp);//read from i and store in a temp char array

		if((compar(temp,target)) == 0){
			return (i);
		}
	}
	return(-1);
}
int searchItem(struct Performance *performance,struct Array * array, int (*compar)(const void *, const void *),void *target){
	//USE READITEM TO GET ARRAY ELEMENT!!!!!

	unsigned char * temp[array->width];//create a temp array for the array->data

	//define my start index, end index and middle index for the binary search implementation
	int start = 0;
	int end = array->nel - 1;
	int mid = 0;

	while(end >= start){//check that the end index is still greater than the starting index
		mid = (start + end)/2;//find the middle of the two indexes
		readItem(performance,array,mid,temp);//read from i and store in a temp char array

		if((compar(temp,target)) < 0){//if the current element is "less than" the target, compar will return a -1
		//current element comes before target. Target is to the right of the current mid index element. 
			start = mid+1;//because target is to the right of my current element, I can change the middle index to the upper half of the sets
		}else if ((compar(temp,target)) > 0){//if the current element  is "greater than" the target, compar will return a +1
		//current element comes after target. Target is to the left of the current mid index element
			end = mid - 1;//because target is to the left of my current element, I can change the middle index to the lower half of the set
		}else{//target == temp
			return mid;
		}
	}
	return(-1);//if the loop exits without returning a value, the function returns a negative 1
}

