#ifndef _HASH_H
#define _HASH_H

struct Performance{//performance structure
	unsigned int reads;
	unsigned int writes;
	unsigned int mallocs;
	unsigned int frees;
};

struct HashTable{
	unsigned int capacity;//number of spaces to store elements in the table
	unsigned int nel;//current number of elements in the hash table
	void **data;//array (size capacity) of pointers to data accessed by the hash table
	int (*hash)(void *,int);//pointer to the data to be stored or searched//integer that is +1 maximum value that the hash function is allowed to produce
	int(*compar)(const void *,const void *);//returns 0 if the data at the two pointers match
};

struct Performance *newPerformance();
//allocate memory for a hash table
//copy values of capacity, hash and compar
//set nel to zero and data to a newly allocated block of memory sufficiently large enough to store capacity many pointers
//set value of each pointer in data array to null,increment the reads variable in performance by capacity (one for each pointer)
//return the address of the structure
//if malloc fails, print to stderr and exit
struct HashTable *createTable(struct Performance *performance,unsigned int capacity,int (*hash)(void *, int),int(*compar)(const void *,const void *));

//add an element to the hash table using linear probing when a collision occurs
//if nel is equal to capacity, print an error message and exit
//else pass value of src and capacity in structre pointed to by table
//use the hash function pointed to by table to calculate and index in the pointer array
//beginning at that index, it will increment the inde until a null pointer is found. if the initial index is null, the index stays the same
//if index gets to capacity, set to 0 and search for null
//each item read should addd to performance reads
//if a null pointer is found at the current index, copy value of src to the index in data anf increment nel
//add to performnce writes
void addElement (struct Performance *performance,struct HashTable *table,void * src);

//find element in hash table and return index
//use the hash function pointed to by table to calcuate index in pointer array data
//use compar function from that index to determine if the src pointers data matches the pointers data at the current index
	//if matched, compar returns 0, return that index
	//index reaches capacity, set to 0, continue search
	//gets to original index, return -1
//add to reads in performance, for every compar function
int getIdx (struct Performance *performance, struct HashTable *table,void *src);

//free the data pointer in table
//free table itself
//add to frees in performance structure
void freeTable (struct Performance *performance, struct HashTable *table);

//find an element in the HashTable and return its pointer
//return the pointer in the data array of the table at the index calculated by getIdx
//if getIdx returns -1, return NULL
//access table to use this function
void *getElement(struct Performance *performance,struct HashTable *table,void *src);

//remove an element from the hash table
//set the pointer in data array of table at the index calculated by getIdx equal to NULL
//increment writes in the performance struct by 1
//nel -1
void removeElement (struct Performance *performance, struct HashTable *table,void *target);

//compute accuracy of the hash table
//calculate the differenc ebetween every entry in the hashtables index and the value computed by hash function
//if index is less than hash functions value, add the index difference between hash functions value and capacity
int hashAccuracy (struct HashTable *table);

//move pointers in the hash table to get a better accuracy
//function should move pointers in hash table to improve hash accuracy
//table must contain all the same pointers as before, just at different spots
void rehash (struct HashTable *table);


#endif