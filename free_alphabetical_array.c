/*Author: Erich MacLean
Assignment Part 7: free_alphabetical_array()
Execution and Operation Can be found in the read.me*/

#include <stdio.h>/*Include nessecary libraries*/
#include <stdlib.h>
#include <string.h>
#include "a1_functions.h"

#define MAX_WORD_L 46 /*Max word length is 45 + 1 for the newline character*/
#define NUM_OF_LETTERS 26/*Alphabet length*/

void free_alphabetical_array(char ***word_arr){
	int a = NUM_OF_LETTERS-1;/*start at the 25th index (letter z)*/
	for(a = NUM_OF_LETTERS-1;a >=0;a--){/*loop through the word sets backwards by index so that the end of the array is freed first*/
		if(word_arr[a] != NULL){
			/*Count the number of words in the word set.*/
			int word_set_count = 0;
			while(word_arr[a][word_set_count] != NULL){/*indexes: word set;string position in word set*/
				word_set_count++;
			}
			/*if greater than 0, free the existing words starting at the end and working backwards*/
			if(word_set_count > 0){
				int w  = word_set_count;
				while(w >= 0){
					free(word_arr[a][w]);/*start at the end of the word set and free backwards*/
					word_arr[a][w] = NULL;
					w--;
				}
			}
		}
		/*free the word set*/
		word_arr[a] = NULL;
		free(word_arr[a]);
		word_arr[a] = NULL;
	}
	word_arr = NULL;
	free(word_arr);/*free the entire array*/
	word_arr = NULL;
}