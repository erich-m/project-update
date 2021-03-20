#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "a3_functions.h"

int encode_shift (char * line,int flag){
	long double smallest = 0;
	int jSmall = 0;
	int j = 0;

	if(flag == 1){/*determines whether to print out the chi squared numbers*/
		printf("Original	chi squared\n");
	}
	for(j = 0;j <= 25;j++){/*loop to find the smallest chi number*/
		long double chi = chi_sq(j,line);
		if(flag == 1){

			printf("%d 		%Lf\n",j,chi);
		}
		if(j == 0){/* if the loop is on the first loop*/
			smallest = chi;
			jSmall = j;
		}else{
			if(chi < smallest){/*if the current chi shift is smaller than the smallest, set new smallest*/
				smallest = chi;
				jSmall = j;
			}
		}
	}
	return(jSmall);/*return the smallest shift*/
}