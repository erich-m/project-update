/*Author: Erich MacLean 1096984
Completed 01/28/2020 2:22AM
Due       01/29/2020 7:00PM
many_foobarbaz; creates and returns an array of foobarbaz structs*/
#include <stdlib.h>

#include "lab2_functions.h"

#define NUM_OF_FBB 20

struct foobarbaz **many_foobarbaz(){/*returns foobarbaz struct array. void function;no parameters*/
	struct foobarbaz **many_fbb = malloc((sizeof(struct foobarbaz)) * NUM_OF_FBB);/*malloc space for the array (num of structs * size of structs)*/
	int f = 0;
	for (f = 0;f < NUM_OF_FBB;f++){
		/*??*/many_fbb[f] = malloc(sizeof(struct foobarbaz));/*malloc the space for the foobarbaz struct at each element*/
		many_fbb[f] = rand_foobarbaz();/*set the element to the randomly generated foobarbaz struct*/
	}

	return(many_fbb);/*return the array of structs*/
}