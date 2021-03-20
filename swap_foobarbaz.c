/*Author: Erich MacLean 1096984
Completed 01/28/2020 2:22AM
Due       01/29/2020 7:00PM
swap_foobarbaz; Swaps two elements of the foobarbaz type array*/
#include <stdio.h>
#include <stdlib.h>

#include "lab2_functions.h"

#define NUM_OF_FBB 20

void swap_foobarbaz (struct foobarbaz **many_fbb, int index_1, int index_2){/*foobarbaz struct array, and two integers as parameters. swaps the structs that the integers.void function; no return value*/
	if(index_1 >= 0 && index_1 < NUM_OF_FBB && index_2 >= 0 && index_2 < NUM_OF_FBB){/*checks that the size is correct for safety*/
		struct foobarbaz *temp;/*create temp struct*/
		temp = malloc(sizeof(struct foobarbaz));/*malloc the space for the struct*/
		temp  = many_fbb[index_2];/*set temp to the element 2*/
		many_fbb[index_2] = many_fbb[index_1];/*copy element 1 to element 2. (now have two element 1's)*/
		many_fbb[index_1] = temp;/*set the original element 1 to temp (element 2)*/
		temp = NULL;/*set temp to NULL to avoid issue where the previous transfer would be set to 0.00000*/
		free(temp);/*free's the temp variable*/
		temp = NULL;/*set temp to NULL again*/
	}else{
		printf("The elements you are trying to swap are out of bounds. Swap failed");/*basic error statement*/
	}
}