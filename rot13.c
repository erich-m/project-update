#include <stdio.h>/*Include all the required headers*/
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define textSize 202
#define shift 13
#define lowerShift 97

int main (int argc, char*argv[]){
	if(argc == 1){
		/*if there is only 1 command line argument, the input is from stdin*/
		char *text;/*create variable for the file input from standard in*/
		text = malloc(sizeof(char) * textSize);/*malloc space for the text*/
		fgets(text,textSize,stdin);
		/*Shift Algorithm*/
		int i = 0;
		while(text[i] != '\0'){
			/*if the character is a letter*/
			/*apply  the shift alogrithm*/
			/*print out the character*/
			text[i] = tolower(text[i]);
			char e = text[i];
			if(text[i] >= 97 && text[i] <= 122){
				e = (((text[i] - lowerShift) + shift)%26) + lowerShift;
			}
			printf("%c",e);
			i++;
		}
		/*Shift Algorithm*/
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
		
				/*Shift Algorithm*/
				int i = 0;
				while(line[i] != '\0'){
					/*if the character is a letter*/
					/*apply  the shift alogrithm*/
					/*print out the character*/
					line[i] = tolower(line[i]);
					char e = line[i];
					if(line[i] >= 97 && line[i] <= 122){
						e = (((line[i] - lowerShift) + shift)%26) + lowerShift;
					}
					printf("%c",e);
					i++;
				}
				/*Shift Algorithm*/
			}else if(argc == 3){
				/*otherwise, the output is to the given file*/
				/*Shift Algorithm*/
				int i = 0;
				while(line[i] != '\0'){
					/*if the character is a letter*/
					/*apply  the shift alogrithm*/
					/*print out the character*/
					line[i] = tolower(line[i]);
					char e = line[i];
					if(line[i] >= 97 && line[i] <= 122){
						e = (((line[i] - lowerShift) + shift)%26) + lowerShift;
					}
					fprintf(fpOut,"%c",e);
					i++;
				}
				/*Shift Algorithm*/
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