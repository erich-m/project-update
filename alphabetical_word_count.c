/*Author: Erich MacLean
Assignment Part 4: alphabetical_word_count()
Execution and Operation Can be found in the read.me*/

#include <stdio.h>/*Include nessecary libraries*/
#include <stdlib.h>
#include <string.h>
#include "a1_functions.h"

#define MAX_WORD_L 46 /*Max word length is 45 + 1 for the newline character*/
#define NUM_OF_LETTERS 26

int *alphabetical_word_count(char** word_arr){/*void function that takes in char** as one parameter*/
	int *alpha_w_count = malloc((sizeof(int) * NUM_OF_LETTERS) + 1);

	int l = 0;
	for(l = 0;l < NUM_OF_LETTERS;l++){/*loop through the letters of the alphabet*/
		/*for each letter, loop through the array of words*/
		int w = 0;
		while(word_arr[w] != NULL){/*while the word array is not at NULL*/
			if((l+65) == (word_arr[w][0]-32) || (l+65) == (word_arr[w][0])){/*if the first letter of the word matches the loop case, capital or not*/
				alpha_w_count[l]++;
			}
			w++;
		}
	}
	alpha_w_count[l+1] = '\0';
	return alpha_w_count;
}