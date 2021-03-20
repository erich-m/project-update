/*Author: Erich MacLean
Assignment Part 3: print_words()
Execution and Operation Can be found in the read.me*/

#include <stdio.h>/*Include nessecary libraries*/
#include <stdlib.h>
#include <string.h>
#include "a1_functions.h"

#define MAX_WORD_L 46 /*Max word length is 45 + 1 for the newline character*/

void print_words(char** word_arr){/*void function that takes in char** as one parameter*/
	int x = 0;
	while(word_arr[x] != NULL){/*while the array element is not NULL, print the word*/
		int y = 0;
		while(word_arr[x][y] != '\0' && word_arr[x][y] != '\n'){/*loop through each character of the word*/
			printf("%c",word_arr[x][y]);/*print character by character while it is not an EOF or newline*/
			y++;
		}
		printf("\n");/*automatically adds the newline after every word is ddone printing out*/
		x++;
	}
}