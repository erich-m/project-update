/*Author: Erich MacLean 
Completed 01/28/2020 2:22AM
due       01/29/2020 7:00PM
free_foobarbaz; frees the array of foobarbaz structs*/
#include <stdio.h>
#include <stdlib.h>

#include "lab2_functions.h"

#define NUM_OF_FBB 20

void free_foobarbaz (struct foobarbaz **many_fbb){/*void function to free all allocated memory for the array of structs*/
	int m = 0;/*loop counter*/
	for(m = 0;m < NUM_OF_FBB;m++){
		free(many_fbb[m]);/*free the struct element*/
		many_fbb[m] = NULL;
	}
	many_fbb = NULL;/*this line is here because I kept getting a 'free() invalid size;Aborted' error*/
	free(many_fbb);/*free the whole array*/
	many_fbb = NULL;
}
