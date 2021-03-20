#include <stdlib.h>
#include <stdio.h>

#include "a2_functions.h"

void print_array(struct Double_Array* d_array){
	int i = 0;
	for(i = 0;i < d_array -> rowsize;i++){
		int j = 0;
		for(j = 0;j < d_array -> colsize;j++){
			printf("%10.6f ",d_array -> array[i][j]);
		}
		printf("\n");
	}
}