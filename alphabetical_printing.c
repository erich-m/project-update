/*Author: Erich MacLean
Assignment Part 9: main()
Execution and Operation Can be found in the read.me*/

#include <stdio.h>/*bring in libraries for the code*/
#include <stdlib.h>
#include <string.h>
#include "a1_functions.h"/*this library references all the created functions*/

#define MAX_WORD_L 46
int main(int argc,char *argv[]){
	FILE *fp;
	char *fileNames[2] = {"a1_words.txt","a1_moreWords.txt"};
	int f = 0;
	for(f = 0;f < 2;f++){
		if((fp=fopen(fileNames[f],"r"))==NULL){/*check that the file entered exists before opening*/
			printf("Please check that the input file exists\n");/*error and exit if the file cant be opened*/
			return(-1);
		}

		/*int size = file_size(fp);   get the size of the file using the file_size function*/
		/*printf("File Size: %d\n",size);*/

		char** word_arr = read_words(fp);
		print_words(word_arr);
		int *alpha_w_count = alphabetical_word_count(word_arr);
		print_alphabetical_word_count(alpha_w_count);
		char ***alpha_arr = create_alphabetical_array(word_arr,alpha_w_count);
		print_words_alphabetically(alpha_arr);
		free_alphabetical_array(alpha_arr);
		/*cannot figure out how to close the file...*/
		/*keep getting the following error: 
				corrupted size vs. prev_size
				Aborted
		*/
		/*fclose(fp);Close the file*/
	}
	return(0);
}


