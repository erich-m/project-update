/*Author: Erich MacLean
Assignment Part 5: print_alphabetical_word_count()
Execution and Operation Can be found in the read.me*/

#include <stdio.h>/*Include nessecary libraries*/
#include <stdlib.h>
#include <string.h>
#include "a1_functions.h"

#define MAX_WORD_L 46 /*Max word length is 45 + 1 for the newline character*/
#define NUM_OF_LETTERS 26

void print_alphabetical_word_count(int *alpha_w_count){/*void function that takes in int* as one parameter*/
	/*Could not convert the loop integer to character to print out the character to match the number;using letter array instead*/
	char letters[NUM_OF_LETTERS] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int l = 0;
	for (l = 0;l < (NUM_OF_LETTERS - 1);l++){
		printf("%c=%d, ",letters[l],alpha_w_count[l]);/*Print count, without newline, but with comma and space*/
	}
	printf("%c=%d\n",letters[l],alpha_w_count[l]);/*Print count, with newline*/
}