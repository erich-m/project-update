#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include <stdio.h>

#define MULTIPLIER 3

//Allocate memory for new performance structure
//set reads, writes, amllocs and frees to zero
struct Performance *newPerformance(){
	struct Performance *perf  = (struct Performance *)malloc(sizeof(struct Performance));//allocate sufficient memory for new performance struct
	if(perf == NULL){
		fprintf(stderr, "ERROR: [Memory Allocation]: emory allocation for struct performance failed\n");
		exit(-1);
	}
	//set reads, writes, mallocs and frees to 0
	perf->reads = 0;
	perf->writes = 0;
	perf->mallocs = 0;
	perf->frees = 0;
	return perf;//return the address of the new performance structure
}
//allocate memory for a hash table
//copy values of capacity, hash and compar
//set nel to zero and data to a newly allocated block of memory sufficiently large enough to store capacity many pointers
//set value of each pointer in data array to null,increment the reads variable in performance by capacity (one for each pointer)
//return the address of the structure
//if malloc fails, print to stderr and exit
struct HashTable *createTable(struct Performance *performance,unsigned int capacity,int (*hash)(void *, int),int(*compar)(const void *,const void *)){
	struct HashTable *newTable = (struct HashTable *)malloc(sizeof(struct HashTable));//malloc sufficient memory for new hash table structure
	if(newTable == NULL){
		fprintf(stderr, "ERROR: [Memory Allocation]: memory allocation for struc hashtable failed\n");
		exit(-1);
	}
	//copy values of capacity, hash and compar into the new table structure
	//set nel to 0
	newTable->capacity = capacity;
	newTable->nel = 0;
	newTable->hash = hash;
	newTable->compar = compar;

	newTable->data = (void **)malloc(sizeof(void *) * capacity);//malloc sufficient memory for the data array (capacity times the size of the void pointer)
	if(newTable->data == NULL){
		fprintf(stderr, "ERROR: [Memory Allocation]: memory allocation for table data failed\n");
		exit(-1);
	}

	for(int c = 0;c < capacity;c++){//for each element in the data array, set to NULL
		newTable->data[c] = NULL;//set data at index c to NULL
		performance->reads++;//add 1 to performance for every read
	}
	performance->mallocs++;
	return newTable;//return the address of the new hash table structure
}

//add an element to the hash table using linear probing when a collision occurs
//if nel is equal to capacity, print an error message and exit
//else pass value of src and capacity in structre pointed to by table
//use the hash function pointed to by table to calculate and index in the pointer array
//beginning at that index, it will increment the inde until a null pointer is found. if the initial index is null, the index stays the same
//if index gets to capacity, set to 0 and search for null
//each item read should addd to performance reads
//if a null pointer is found at the current index, copy value of src to the index in data anf increment nel
//add to performnce writes
void addElement (struct Performance *performance,struct HashTable *table,void * src){
	if(table->nel == table->capacity){//if nel is equal to capacity, print error and exit
		fprintf(stderr,"ERROR: [Out of bounds]: number of elements has reached full capacity\n");
		exit(-1);
	}
	int calculatedIndex = table->hash(src,table->capacity); //index of integer range [0,capacity)
	//check if value at current index is null
	//if yes, copy src into data at calcualted index
	//if null, loop until element not null is found
	int d = calculatedIndex;
	//add 1 to reads every time the index is increased by 1
	//guarunteed to be a null spot in the table is nel < capacity//I do not have to worry about passing the current index if I start there
	//because of this being true, I can use the modulo operator to loop through theelements until I reach a null. (once the index d gets to the end index, the next index will be index=capacity. index%capacity is then =0 and will be the first index)
	while(table->data[d % (table->capacity)] != NULL){//if the data at index (current index modulo with the capacity) does not match null, (compar returns 0 if matched)
		d++;
		performance->reads++;
	}
	//upon exit of the loop, the table->data at index (d % cap) is equal to null;
	table->data[d % (table->capacity)] = src;
	performance->writes++;
	table->nel++;
}

//find element in hash table and return index
//use the hash function pointed to by table to calcuate index in pointer array data
//use compar function from that index to determine if the src pointers data matches the pointers data at the current index
	//if matched, compar returns 0, return that index
	//index reaches capacity, set to 0, continue search
	//gets to original index, return -1
//add to reads in performance, for every compar function
int getIdx (struct Performance *performance, struct HashTable *table,void *src){
	int calculatedIndex = table->hash(src,table->capacity);//index of integer range [0,capacity)

	int s = calculatedIndex;//loop variable starts at current index
	int found = -1;
	//loop while item to be searched for has not been found
	//
	//The second test case comes from the following. It is based on the idea of dual loops with the mod operator andcombining the loops into single element number
	//                           Left Block                 Right Block
	//Element Number          0 / 1 / 2 / 3 / 4 / 5 // 6 / 7 / 8 / 9 / 10 / 11
	//Index (by mod of cap)   0 / 1 / 2 / 3 / 4 / 5 // 0 / 1 / 2 / 3 /  4 /  5
	//cap = 6. Say the index given by the hash function is 3. This yields the following:
	//initial element number = 3
	//index of number        = 3
	//end element number     = 9 = initial element number + cap
	//end index number       = 3
	//
	//cap is used as reference. If s is below cap, it is in the left block and must be compared as initialElementNumber <= s < cap
	//If s is greater than or equal to cap, it is in the right block and must be compared as cap <= s < endElementNumber
	//These two are connected by and or operator. Either the index is within the left block or it is withing the right block and only one of them has to be true
	while(((calculatedIndex <= s && s < table->capacity) ||  (table->capacity <= s && s < (calculatedIndex + table->capacity))) && found == -1){
		if(table->data[s % (table->capacity)] == NULL && src == NULL){//if both the source and the data are null, the return match???......................................................................................CHECK THIS...............
			found = s % (table->capacity);		
		}else if((table->data[s % (table->capacity)] == NULL && src != NULL) || (table->data[s % (table->capacity)] != NULL && src == NULL)){//if the data at the current index is null, ignore it
			/*do nothing*/
			found = -1;
		}else if(table->compar(src,table->data[s % (table->capacity)]) == 0){//compar cannot handle null cases
			found = s % (table->capacity);
			performance->reads++;
		}
		s++;
		
	}
	return found;
}

//free the data pointer in table
//free table itself
//add to frees in performance structure
void freeTable (struct Performance *performance, struct HashTable *table){
	//free the data pointer 
	free(table->data);
	table->data = NULL;
	free(table);
	table = NULL;

	performance->frees++;
}

//find an element in the HashTable and return its pointer
//return the pointer in the data array of the table at the index calculated by getIdx
//if getIdx returns -1, return NULL
//access table to use this function
void *getElement(struct Performance *performance,struct HashTable *table,void *src){
	int findIndex = getIdx(performance,table,src);
	if(findIndex == -1){
		return NULL;
	}else{
		return table->data[findIndex];
	}
}

//remove an element from the hash table
//set the pointer in data array of table at the index calculated by getIdx equal to NULL
//increment writes in the performance struct by 1
//nel -1
void removeElement (struct Performance *performance, struct HashTable *table,void *target){
	int removeIndex = getIdx(performance,table,target);
	if(removeIndex != -1){
		table->data[removeIndex] = NULL;
		table->nel--;
		performance->writes++;
	}
}

//compute accuracy of the hash table
//calculate the differenc ebetween every entry in the hashtables index and the value computed by hash function
//if index is less than hash functions value, add the index difference between hash functions value and capacity
//return the sum of all the differences in hash value and location
int hashAccuracy (struct HashTable *table){
	int difference = 0;
	for(int t = 0;t < table->capacity;t++){
		if(table->data[t] != NULL){
			//t is the actual index
			int hashedIndex = table->hash(table->data[t],table->capacity);
			//hashedIndex is the theoretical index
			if(t < hashedIndex){
				difference += t + (hashedIndex - table->capacity);
				//printf("difference: %03d; Added to difference: %02d\n",difference, t + (table->capacity - hashedIndex));
			}else{
				difference+= t - hashedIndex;
				//printf("difference: %03d; Added to difference: %02d\n",difference, t - hashedIndex);
			}
		}
	}
	return difference;
}

//move pointers in the hash table to get a better accuracy
//function should move pointers in hash table to improve hash accuracy
//table must contain all the same pointers as before, just at different spots
//a key note to mention is that if a data is 2 spots away and the data next to it is 3 spots away, swapping those elements will not change the hash accuracy at all.
void rehash (struct HashTable *table){//this function copies all the data out of the array, removes all the elements, and then re adds them back into the array using the given hash function. This way, all items are moved back to their optimal locations
	struct Performance * tempPerf = newPerformance();
	void ** tempData = (void **)malloc(sizeof(void *) * table->nel);//malloc sufficient memory for the data array (capacity times the size of the void pointer)
	if(tempData == NULL){
		fprintf(stderr, "ERROR: [Memory Allocation]: memory allocation for temporary data failed\n");
		exit(-1);
	}
	int copied = 0;
	for(int c = 0;c < table->capacity;c++){//copy all the elements that are not equal to null into temp
		if(table->data[c] != NULL){//if the element is not null, copy into temp
			tempData[copied] = table->data[c];//copy from table->data into the temp
			copied++;//add to the copied index
		}
	}
	for(int r = 0;r < table->capacity;r++){//set all elements to null
		table->data[r] = NULL;
	}
	int totalElements = table->nel;//copy total number of elements
	table->nel = 0;//reset the total to 0 now that malloced space is empty
	for(int a = 0;a < totalElements;a++){//loop for the copied number of elements
		if(tempData[a] != NULL){//double check that it is not null
			addElement(tempPerf,table,tempData[a]);//add the element back into the tables data array
		}
	}

	free(tempData);//free the temp data storage
	tempData = NULL;
	free(tempPerf);//free the temporary perf storage
	tempPerf = NULL;
}