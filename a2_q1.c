#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "a2_functions.h"

#define rowSize 6
#define colSize 9

int main(int argc,char *argv[]){
	srand(time(0));
	printf("---------------------\nQuestion 1\n---------------------\n");
	struct Double_Array *d_array = double_array(rowSize,colSize);
	randomize_array(d_array,-100,100);
	print_array(d_array);
	int row1 = (((double)rand())/((double)RAND_MAX))* (rowSize-1) + 0;
	int row2 = (((double)rand())/((double)RAND_MAX))* (rowSize-1) + 0;
	while(row1 == row2){
		row2 = (((double)rand())/((double)RAND_MAX))* (rowSize-1) + 0;
	}
	if(row1 < row2){
		printf("\nSwapping rows %d and %d\n\n",row1+1,row2+1);
	}
	else{
		printf("\nSwapping rows %d and %d\n\n",row2+1,row1+1);
	}
	swap_rows(d_array,row1,row2);
	print_array(d_array);


	int col1 = (((double)rand())/((double)RAND_MAX))* (colSize-1) + 0;
	int col2 = (((double)rand())/((double)RAND_MAX))* (colSize-1) + 0;
	while(col1 == col2){
		col2 = (((double)rand())/((double)RAND_MAX))* (colSize-1) + 0;
	}
	if(col1 < col2){
		printf("\nSwapping columns %d and %d\n\n",col1+1,col2+1);
	}
	else{
		printf("\nSwapping columns %d and %d\n\n",col2+1,col1+1);
	}
	swap_columns(d_array,col1,col2);
	print_array(d_array);
	printf("\n\n\n");
	return(0);
}