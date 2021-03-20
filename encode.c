#include <stdio.h>/*Include all the required headers*/
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define textSize 202
#define lowerShift 97

int main (int argc, char*argv[]){
	int inFlag = 0;
	int outFlag = 0;
	int shift = 13;

	char in_file_name[textSize] = "";
	char out_file_name[textSize] = "";

	int a = 1;
	for(a = 1;a < argc;a++){/*loop through the different arguments in the command line starting at the first one*/
			if(argv[a][0] >= 48 && argv[a][0] <= 57){/*check to see if first char of argument is a num*/
				shift = atoi(argv[a]);/*then shift is this argument and is positive*/
			}else if(argv[a][0] == 45){/*check for dash;Either flag or negative number*/
				if(argv[a][1] >= 48 && argv[a][1] <= 57){/*check the second char for a number*/
					shift = atoi(argv[a]);
				}else if(argv[a][1] == 70){/*the second character is an F flag*/
					inFlag = 1;
					if(argv[a][2] != '\0'){/*if the second character is not NULL, the file name is attached to the flag*/
						int f = 2;
						while(argv[a][f] != '\0'){
							in_file_name[f-2] = argv[a][f];
							f++;
						}
					}else{/*the file name is the next argument*/
						strcpy(in_file_name,argv[a+1]);
					}
				}else if (argv[a][1] == 79){/*the second character is an O flag*/
					outFlag = 1;
					if(argv[a][2] != '\0'){/*if the second character is not NULL, the file name is attached to the flag*/
						int f = 2;
						while(argv[a][f] != '\0'){
							out_file_name[f-2] = argv[a][f];
							f++;
						}
					}else{/*the file name is the next argument*/
						strcpy(out_file_name,argv[a+1]);
					}
				}
			}
	}
	if(shift < -25 || shift > 25){
		printf("Please enter a shift that is between -25 and 25 inclusive\n");
		fprintf(stderr,"%s\n","Please enter a shift that is between -25 and 25 inclusive");
		return(-1);
	}
	if(shift < 0){
		shift = 26 + shift;
	}
/*test command line parser
	printf("Positive Shift = %d;\nIn Name = %s;\nOut Name = %s;\nIn Flag = %d;\nOut Flag = %d;\n",shift,in_file_name,out_file_name,inFlag,outFlag);
*/
	if(inFlag == 0){/*If the flag is 0, read in from stdin*/
		if(outFlag == 0){/*If the out flag is 0, print to stdout*/
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
		}else if (outFlag == 1){/*If the out flag is 1, print to given file*/
			FILE *fpOut = NULL;
			fpOut = fopen(out_file_name,"w");/*if there needs to be a write, set the fOut to write to a file*/
			if(fpOut == NULL){
				printf("file not found");
				return(1);
			}
			
			char *line = NULL;/*create another input string*/
			line = malloc(sizeof(char) * textSize);

				while(strcmp(fgets(line,textSize,stdin),"\n") != 0){/*read in from the file*/
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
			free(line);
			line = NULL;
			fclose(fpOut);
		}
	}else if(inFlag == 1){/*if the flag is 1, read in from the given file*/
		if(outFlag == 0){/*If the out flag is 0, print to stdout*/
			FILE *fpIn = NULL;
			fpIn = fopen(in_file_name,"r");/*open fIn from reading*/
			if(fpIn == NULL){
				printf("file not found\n");
				return(1);
			}
			char *line = NULL;/*create another input string*/
			line = malloc(sizeof(char) * textSize);
			while(fgets(line,textSize,fpIn) != NULL){/*read in from the file*/
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
			}
			printf("\n");
			free(line);
			line = NULL;

			fclose(fpIn);
		}else if (outFlag == 1){/*If the out flag is 1, print to given file*/
			FILE *fpIn = NULL;
			fpIn = fopen(in_file_name,"r");/*open fIn from reading*/
			if(fpIn == NULL){
				printf("file not found\n");
				return(1);
			}
			FILE *fpOut = NULL;
			fpOut = fopen(out_file_name,"w");/*if there needs to be a write, set the fOut to write to a file*/
			if(fpOut == NULL){
				printf("file not found");
				return(1);
			}
			
			char *line = NULL;/*create another input string*/
			line = malloc(sizeof(char) * textSize);

				while(fgets(line,textSize,fpIn) != NULL){/*read in from the file*/
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
			free(line);
			line = NULL;
			fclose(fpIn);
			fclose(fpOut);
		}
	}
	/*set up if statements for if there is a file input or not and if there is an output file or not*/
	return(0);
}