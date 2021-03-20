/*Author: Erich MacLean
Completed 01/28/2020 2:22AM
Due       01/29/2020 7:00PM
Compilation: make all
Execution:   ./lab2
Clean:       make clean
Main function;does required tasks*/
#include <stdio.h>
#include <stdlib.h>

#include "lab2_functions.h"

#define NUM_OF_FBB 20 /*max num of foobarbaz structs*/

int main (int argc,char *argv[]){
	struct foobarbaz **fbb_array = many_foobarbaz(); /*Creates foobarbaz array*/
	print_foobarbaz(fbb_array);/*Prints the foobarbaz array*/

	/*Create 2 swap points*/
	int point_1 = (int)(((double) rand() / (double) RAND_MAX) * NUM_OF_FBB);
	int point_2 = (int)(((double) rand() / (double) RAND_MAX) * NUM_OF_FBB);
	/*Create 2 swap points*/

	printf("%d\n\n%d\n\n",point_1,point_2);/*Print swap points*/

	swap_foobarbaz(fbb_array,point_1,point_2);/*Swap elements at those points*/
	print_foobarbaz(fbb_array);/*Print the foobarbaz array again*/

	free_foobarbaz(fbb_array);/*free all allocated memory*/
	return(0);
}
