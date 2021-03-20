#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "a3_functions.h"

int main (int argc,char * argv[]){
	int i = 1;
	int in_arg = 0;
	int out_arg = 0;
	int flags[7] = {0,0,0,0,0,0,0}; /*Stores the state of the flags:   F O s S t x n*/
	while(argv[i] != NULL){/*loop through the arguments to find a hyphen signifying a flag*/
		if(argv[i][0] == '-'){/*find a hyphen*/
			if(argv[i][1] != 'F' && argv[i][1] != 'O'){/*if the flag is NOT a file based flag*/
				int k = 1;
				while(argv[i][k] != '\0'){/*Loop through the flag command to search for other flags. Update the flags accordingly*/
					if(argv[i][k] == 's'){
						flags[2]++;
					}else if(argv[i][k] == 'S'){
						flags[3]++;
					}else if(argv[i][k] == 't'){
						flags[4]++;
					}else if(argv[i][k] == 'x'){
						flags[5]++;
					}else if(argv[i][k] == 'n'){
						flags[6]++;
					}else{/*if the flags havent been found, print out an error*/
						fprintf(stderr,"Please check the flags are correct %c\n",argv[i][k]);
						return(-1);
					}
					k++;
				}
			}else if(argv[i][1] == 'F'){/*if the flag is file based, store the location of the file*/
				in_arg = i + 1;
				flags[0]++;
			}else if(argv[i][1] == 'O'){/*if the flag is file based, store the location of the file*/
				out_arg = i + 1;
				flags[1]++;
			}
			if((argv[i][1] == 'F' || argv[i][1] == 'O')&& argv[i][0] == '-'){/*if the flag is file based, skip checking the next argument*/
				i++;
			}

		}else{/*return as error if none of the arguments are flags*/
			fprintf(stderr,"Please check that the arguments are correct\n");
			return(-1);
		}
		i++;
	}
/*
	printf("Flags: %d %d %d %d %d %d %d\n",flags[0],flags[1],flags[2],flags[3],flags[4],flags[5],flags[6]);
*/
	char * text_input = NULL;
	if(flags[0] == 0){/*Read in from stdin one character at a time, and as itreads in, reallocate memory for new characters in the full input*/
		text_input = malloc(0);
		int in_size = 0;
    	char nextChar;
    	nextChar = getchar();/*get the first char from the file*/
    	while(nextChar != EOF){
    		text_input = realloc(text_input,(sizeof(char) * (in_size))+2);/*realloc will change the already given memory to the new size of memory given as the second parameter*/

    		text_input[in_size] = nextChar;
    		text_input[in_size+1] = '\0';

    		nextChar = getchar();/*read in next char from the file now that it is allocated*/
    		in_size++;
    	}
	}else if (flags[0] == 1){/*Standard process to read from file input*/
		FILE *fpIn = NULL;
		fpIn = fopen(argv[in_arg],"r");/*open fIn from reading*/
		int sz = 0;
		fseek(fpIn, 0L, SEEK_END);
		sz = ftell(fpIn);
		rewind(fpIn);
		text_input = malloc(sz + 2);
		if(fpIn == NULL){
			fprintf(stderr,"file not found\n");
			return(1);
		}
		int count = 0;
		char nextChar;
		nextChar = fgetc(fpIn);/*read in from the file one char at a time*/
		while(nextChar != EOF){
			text_input[count] = nextChar;
			count++;
    		nextChar = fgetc(fpIn);
		}
		text_input[count] = '\0';/*Changes the last char to NULL*/
		fclose(fpIn);/*close the file*/
	}
	int es = 0;
	es = encode_shift(text_input,flags[5]);/*gets the encode shift for the text input (from either stdin or file)*/
	if(flags[3] == 1){/*prints out the shift used to encode the text*/
		printf("Encode Shift: %d\n",es);
	}
	int ds = to_decode(es);/*gets the decode shift from the encode shift*/
	if(flags[2] == 1){/*prints it out the shift used to decode the text*/
		printf("Decode Shift: %d\n",ds);
	}

	if(flags[4] == 1){/*Print out the text frequencies*/
		int * char_count = text_freq(text_input);/*gets the text frequencies from this text input*/
		int l = 0;
		for(l = 0;l < 26;l++){
			printf("%c	%d\n",(l+65),char_count[l]);
		}
		free(char_count);/*frees the array*/
		char_count = NULL;
	}

	if(flags[6] != 1){/*if -n is NOT entered, proceed to print out the encoded text to stdout*/
		int character = 0;
		while(text_input[character] != '\0'){
			/*if the character is a letter*/
					/*apply  the shift alogrithm*/
					/*print out the character*/
					text_input[character] = tolower(text_input[character]);
					char e = text_input[character];
					if(text_input[character] >= 97 && text_input[character] <= 122){
						e = (((text_input[character] - 97) + ds)%26) + 97;
					}
					printf("%c",e);
					character++;
		}
		if(flags[0] == 1){/*prints out formatting newline*/
			printf("\n");
		}

	}
	if (flags[1] == 1){/*if there is an output flag*/
			FILE *fpOut = NULL;/*set up file output*/
			fpOut = fopen(argv[out_arg],"w");/*if there needs to be a write, set the fOut to write to a file*/
			if(fpOut == NULL){
				fprintf(stderr,"file not found");
				return(1);
			}
			int character = 0;
		while(text_input[character] != '\0'){/*print out to the file*/
			/*if the character is a letter*/
					/*apply  the shift alogrithm*/
					/*print out the character*/
					text_input[character] = tolower(text_input[character]);
					char e = text_input[character];
					if(text_input[character] >= 97 && text_input[character] <= 122){
						e = (((text_input[character] - 97) + ds)%26) + 97;
					}
					fprintf(fpOut,"%c",e);
					character++;
		}
		if(flags[0] == 1){
			fprintf(fpOut,"%c",'\n');
		}
		fclose(fpOut);
	}
/*free the input variable*/
	free(text_input);
	text_input = NULL;
	return(0);
}