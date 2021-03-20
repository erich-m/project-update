#include <stdlib.h>
#include <string.h>

#include "a2_functions.h"

int swap_columns(struct Double_Array *d_array,int a,int b){
	/*Question 1 B Explanation-Column Swapping:
	In order to swap a column, memcpy cannot be used, as the function cannnot work on multiple variables 
	from multiple arrays. Each element is lined up within the columns of the 2 dimensional array and thus, 
	memcpy does not work. memcpy(dest,source,numOfBytes) the function call also shows that the set of values,
	despite being arranged vertically, cannot be swapped with this function
	*/
	if(a >= 0 && b >= 0 && a < d_array->colsize && b < d_array->colsize){
		int j = 0;
		for(j = 0;j < d_array->rowsize;j++){/*loop through the rows*/
			/*in each row, swap the elements at a and b*/
			double temp = 0;
			temp = d_array->array[j][a];
			d_array->array[j][a] = d_array->array[j][b];
			d_array->array[j][b] = temp;
		}
		return(1);
	}
	return(0);
}