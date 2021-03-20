#include <stdlib.h>
#include <stdio.h>

#include "a2_functions.h"

void randomize_array(struct Double_Array * d_array,double a,double b){
	int i = 0;
	for(i = 0;i < d_array -> rowsize;i++){
		int j = 0;
		for(j = 0;j < d_array -> colsize;j++){
			double rand = rand_double(a,b);
			d_array -> array[i][j] = rand;
			/*printf("testing %d %d %f\n",i,j,rand);*/
		}
	}
}