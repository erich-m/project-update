/*Author: Erich MacLean
Assignment Part 8: print_words_alphabetically()
Execution and Operation Can be found in the read.me*/

#include <stdio.h>/*Include nessecary libraries*/
#include <stdlib.h>
#include <string.h>
#include "a1_functions.h"

#define MAX_WORD_L 46 /*Max word length is 45 + 1 for the newline character*/
#define NUM_OF_LETTERS 26

void print_words_alphabetically(char ***word_arr){
	/*Could not convert the loop integer to character to print out the character to match the number;using letter array instead*/
	char letters[NUM_OF_LETTERS] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	
	int l = 0;
	for(l = 0;l < NUM_OF_LETTERS;l++){/*Loop through all the letters of the alphabet*/
		if(l > 0){
			printf("\n");/*formatting newline character*/
		}
		printf("\'%c\'\n",letters[l]);
		if(word_arr[l] != NULL){/*There are no words in the array*/
			print_words(word_arr[l]);
		}else{/*Print char, then use print_array() to print the words from that character set*/
			printf("There are no words that begin with the letter \'%c\'\n",letters[l]);
		}
	}
}