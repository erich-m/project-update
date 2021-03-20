#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "a3_functions.h"

/*long double return value
takes two parameters, a given shift value, and a string input
Returns the output of the chi squared formula for a given shift*/
long double chi_sq(int shift,char * line){
	double ef[26] = EF;
	int n = letter_count(line);/*gives the letter count for the line*/
	long double chi = 0;
	int i = 0;
	int * freq = text_freq(line);/*creates the array with the text frequencies for the line*/
		
	for(i = 0;i <=25; i++){/*loops through all the characters in the alphabet*/
		char c = i+65;
		long double num_to_sq = (n*ef[i]) - (freq[offset(encode(c,shift))]);
		long double den = n * n * ef[i];
		chi+=((num_to_sq * num_to_sq)/den);
	}

	free(freq);/*frees the integer array with the frequecnies of the letters*/
	freq = NULL;
	return(chi);/*returns the chi shift number*/
}