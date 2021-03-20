/*Author: Erich MacLean
Assignment Part 6: create_alphabetical_array()
Execution and Operation Can be found in the read.me*/

#include <stdio.h>/*Include nessecary libraries*/
#include <stdlib.h>
#include <string.h>
#include "a1_functions.h"

#define MAX_WORD_L 46 /*Max word length is 45 + 1 for the newline character*/
#define NUM_OF_LETTERS 26/*Alphabet length*/

char ***create_alphabetical_array(char **word_arr,int *alpha_w_count){
	char ***alpha_arr;/*create an array of word sets. Each word set is an array of strings. Each string is an array of chars. Therefore, a 3D array*/
	char **temp;/*For some reason, the A word set would mutate to null at some point. this temp is to prevent that*/
	temp = malloc(sizeof(char*) * alpha_w_count[0]);/*allocate space for the A word set only*/
	alpha_arr = malloc(sizeof(word_arr));/*defines array of letter organized array of strings*/
	int i = 0;
	for(i = 0;i < NUM_OF_LETTERS;i++){/*loops through all the letters of the alphabet*/
		alpha_arr[i] = malloc(sizeof(char*) * MAX_WORD_L * (alpha_w_count[i] + 1));/*mallocs space for number of words in the word array*/
		if(alpha_w_count[i] > 0){/*if the word count is greater than 0, it has to be placed into the array*/
			int p = 0;/*Position of word within char set. Only increases on word addition to set*/
			int w = 0;/*loop counter for the array of words to find all words that are not NULL, and then if they begin witht he current letter*/
			while(word_arr[w] != NULL){/*loops through the word array to find words that are not NULL*/
				/*if the word starts with the letter on the correct loop num, count chars in word, allocate space in word set, copy into space*/
				if(word_arr[w][0] - 65 == i || word_arr[w][0] - 97 == i){/*the first character of the word matches the for loop case*/
					int char_count = 2;/*character count set to 2 for newline and EOF*/
					int letter = 0;/*index for the string position in the word set*/
					while(word_arr[w][letter] != '\0'){/*get the num of characters in the word*/
						char_count++;
						letter++;
					}
					alpha_arr[i][p] = malloc(sizeof(char) * char_count + 2);/*mallocs space for the word*/
					strcpy(alpha_arr[i][p],word_arr[w]);/*copy the word into the 3D array*/
					/*printf("test %d %s",i,alpha_arr[i][p]);*/
					if(i == 0){/*only if i is 0 (letter A), copy the word into the temporary array*/
						temp[p] = malloc(sizeof(char) * char_count + 2);/*allocate the space for the word in temp*/
						strcpy(temp[p],word_arr[w]);/*copy the word into temp*/
					}
					/*printf("CAA: %s;letter num=%d;position=%d",alpha_arr[i][p],i,p);*/
					p++;/*loop counter for position in word set*/
				}
				    w++;/*loop count to search through word array*/
			}
			/*after the words have been transferred into their word set, add one space that is equal to null*/
		}else if(alpha_w_count[i] <= 0){/*there are no letters: set to NUll pointer*/
			alpha_arr[i] = NULL;/*if there are no words in the word set, set the space to NULL*/
		}
	}
	if(alpha_w_count[0] <= 0){/*if the A word set has no words in it, set temp to NULL  (A set was broken)*/
		temp = NULL;
	}
	alpha_arr[0] = temp;/*if there are words in the temp array, they will take the place of the mutated NULL in the word set*/
	/*if there are no words in A set, the array will be set to NULL*/

	/*printf("Temp %s",temp[0]);*/
	/*printf("test %s",alpha_arr[0][0]);*/
	return (alpha_arr);
}