#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "a2_functions.h"

int swap_rows(struct Double_Array *d_array,int a,int b){
	if(a >= 0 && b >= 0 && a < d_array->rowsize && b < d_array->rowsize){
		/*Question 1 A Explanation-Row Swapping: 
	To copy a row in the regular, but slow way, the programmer must perform a swap on each element in the 
	two different arrays, and repeat this for each element. 
	In this program however, the function memcpy copies the memory from one location to another. 
	In this case, it copies array A into a temp array. then copies from array B into array A. and then copies the memory from temp into array B. 
	This only takes three lines of code in total (other than setting the temp variable up).*/


		/*swap the rows a and b of the array in the struct d_array*/
		double *temp;
		temp = malloc(sizeof(double) * (d_array->rowsize) * (d_array->colsize));
		/*printf("test %f %f\n",temp[0],d_array->array[a][0]);before temp copy from array row a*/
		memcpy(temp,d_array->array[a],sizeof(double) * (d_array->colsize));/*copy the array of doubles from row a into temp*/
		/*printf("test %f %f\n",temp[0],d_array->array[a][0]);after temp copy from array row a*/
		/*printf("test %f %f\n",d_array->array[a][0],d_array->array[b][0]);before array row a is copied into row b*/
		memcpy(d_array->array[a],d_array->array[b],sizeof(double) * (d_array->colsize));
		/*printf("test %f %f\n",d_array->array[a][0],d_array->array[b][0]);after array row a is copied into row b*/
		/*printf("test %f %f\n",d_array->array[b][0],temp[0]);before array temp (row a) is copied into row b making it row a*/
		memcpy(d_array->array[b],temp,sizeof(double) * (d_array->colsize));
		/*printf("test %f %f\n",d_array->array[b][0],temp[0]);after array temp (row a) is copied into row b making it a*/
		free(temp);
		temp = NULL;
		return(1);
	}
	return(0);
}