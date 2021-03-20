#include <stdio.h>/*Include all the required headers*/
#include <string.h>
#include <stdlib.h>

#define textSize 202

int main (int argc, char*argv[]){
	if(argc == 1){
		/*if there is only 1 command line argument, the input is from stdin*/
		char *text;/*create variable for the file input from standard in*/
		text = malloc(sizeof(char) * textSize);/*malloc space for the text*/
		fgets(text,textSize,stdin);
		printf("%s",text);
		free(text);
		text = NULL;
	}else if(argc == 2 || argc == 3){
		/*if there are 2 or 3 command line arguments, the input is from the given file*/
		FILE *fpIn = NULL;
		fpIn = fopen(argv[1],"r");/*open fIn from reading*/
		if(fpIn == NULL){
			printf("file not found");
			return(1);
		}

		FILE *fpOut = NULL;
		if(argc == 3){
			fpOut = fopen(argv[2],"w");/*if there needs to be a write, set the fOut to write to a file*/
			if(fpOut == NULL){
				printf("file not found");
				return(1);
			}
		}

		char *line = NULL;/*create another input string*/
		line = malloc(sizeof(char) * textSize);
		while(fgets(line,textSize,fpIn) != NULL){/*read in from the file*/
			if(argc == 2){
				/*if there is 1 or 2 command line arguments, output is through stdout (printf)*/
			printf("%s",line);
			}else if(argc == 3){
				/*otherwise, the output is to the given file*/
				fprintf(fpOut,"%s",line);
			}
		}
		free(line);
		line = NULL;
		if(argc != 3){
			printf("\n");
		}
		if(fpIn != NULL){
			fclose(fpIn);
			fpIn = NULL;
		}
		if(fpOut != NULL){
			fclose(fpOut);
			fpOut = NULL;
		}
	}
	return(0);
}