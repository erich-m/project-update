/*Author: Erich MacLean
Assignment Part 2: read_words()
Execution and Operation Can be found in the read.me*/

#include <stdio.h>/*Include nessecary libraries*/
#include <stdlib.h>
#include <string.h>

#include "a1_functions.h"

#define MAX_WORD_L 47 /*Max word length is 45 + 2 for the newline character and null terminator*/

char **read_words(FILE *fp){/*char** function; returns array of words (array of character arrays). Takes in one parameter (file pointer)*/
	char word_input[MAX_WORD_L];/*local char array for the word input from the file*/

	char **word_arr;
	word_arr = malloc( (sizeof(char *) * (file_size(fp)/2))+1);/*dynamically allocate space for the amount of words in the file, +1 for the null terminator*/

	int i = 0;/*index location for the word array*/
	while(fgets(word_input,MAX_WORD_L,fp) != NULL){/*read from file*/
		int w_count = 2;
		while(word_input[w_count] != '\0'){/*while loop to count the chars in the word input +2 for newline and end character*/
			w_count++;
		}
		/*printf("%d",w_count); Print word count*/
		word_arr[i] = malloc( sizeof(char) * w_count);/*malloc space for the word input*/
		strcpy(word_arr[i],word_input);/*copy word input into the word array*/
		/*printf("RW: %s",word_arr[i]);*/
		i++;
	}

	word_arr[i + 1] = malloc ( sizeof(NULL));/*malloc space at the end of the words for the null terminator*/
	word_arr[i + 1] = NULL;/*set end of word array to Null*/

	return word_arr;/*return word_array*/
}