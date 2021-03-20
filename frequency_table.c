#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "a3_functions.h"

#define textSize 202


int main (int argc,char * argv[]){
	/*if there is no input file, there will be only the execution (one command line argument).
	Otherwise there will be either 2 or 3 ( for the -F and the file name)*/

	int inFlag = 0;

	char in_file_name[textSize] = "";

	int a = 1;
	for(a = 1;a < argc;a++){/*loop through the different arguments in the command line starting at the first one*/
		if(argv[a][0] == 45){/*check for dash*/
			if(argv[a][1] == 70){/*the second character is an F flag*/
				inFlag = 1;
				if(argv[a][2] != '\0'){/*if the second character is not NULL, the file name is attached to the flag*/
					int f = 2;
					while(argv[a][f] != '\0'){
						in_file_name[f-2] = argv[a][f];
						f++;
					}
				}else if (argc == 3){/*the file name is the next argument*/
					strcpy(in_file_name,argv[a+1]);
				}else{
					fprintf(stderr,"Please ensure a file is given and declared with -F\n");
					return(-1);
				}
			}
		}
	}

	if(argc > 1 && inFlag == 0){/*if there is more than one argument but no inFlag (-F) detected in the other args*/
		if(strcmp(in_file_name,"") == 0){/*If there is nothing in the file name, nothing was copied in meaning it was missed*/
			fprintf(stderr,"Please ensure the input file is declared with -F\n");
			return(-1);
		}
	}
/*test command line parser
	printf("In Name = %s;\nIn Flag = %d;\n",in_file_name,inFlag);
*/
	char * text_input = NULL;
	/*if here, I will have either stdin for input (inFlag == 0) or text file input (inFlag == 1)*/
	if(inFlag == 0){/*read from stdin*/
		text_input = malloc(0);
		int in_size = 0;
    	char nextChar;
    	nextChar = getchar();
    	while(nextChar != EOF){
    		text_input = realloc(text_input,(sizeof(char) * (in_size))+2);/*realloc will change the already given memory to the new size of memory given as the second parameter*/

    		text_input[in_size] = nextChar;
    		text_input[in_size+1] = '\0';

    		nextChar = getchar();
    		in_size++;
    	}
	}else if (inFlag == 1){/*read from txt file*/
		FILE *fpIn = NULL;
		fpIn = fopen(in_file_name,"r");/*open fIn from reading*/
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
		nextChar = fgetc(fpIn);
		while(nextChar != EOF){
			text_input[count] = nextChar;
			count++;
    		nextChar = fgetc(fpIn);
		}
		text_input[count] = '\0';
		fclose(fpIn);
	}
	printf("Letter Count: %d\n",letter_count(text_input));
	printf("Character Count: %ld\n",strlen(text_input) - 1);
	/*printf("text_input : %s\n",text_input);*/
	int * char_count = text_freq(text_input);
	int l = 0;
	for(l = 0;l < 26;l++){
		printf("%c	%d\n",(l+65),char_count[l]);
	}
	free(char_count);
	char_count = NULL;
	free(text_input);
	text_input = NULL;
	return(0);
}