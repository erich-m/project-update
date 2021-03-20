/*Author: Erich MacLean 1096984
Completed 01/28/2020 2:22AM
Due       01/29/2020 7:00PM
rand_foobarbaz;mallocs and initializes random foobarbaz struct;returns that struct*/
#include <stdlib.h>

#include "lab2_functions.h"

struct foobarbaz *rand_foobarbaz(){/*allocates the memory for a foobarbaz struct and initializes the data to random numbers within the provided ranges. No parameters*/
	struct foobarbaz *fbb;/*declare the struct*/
	/*??*/fbb = malloc(sizeof(struct foobarbaz));/*allocate the memory for the struct*/

	fbb -> foo = (int)rand_double(0,49); /*range of 0 to 49*/
	fbb -> bar = rand_double(0,100);     /*range of 0.0 to 100.00*/
	fbb -> baz = (int)rand_double(50,99);/*range of 50 to 59*/

	return(fbb);/*return the struct*/
}