#include <stdio.h>/*Bring in libraries for the code*/
#include <string.h>

#define MAXSIZE 500/*create a max size for ranges on size*/

int main (int argc,char * argv[]){/*main line*/
	char line[MAXSIZE];/*input line variable*/
	int run = 1;/*run toggle variable*/

	int wordC = 0;/*word count*/
	int lineC = 0;/*line count*/
	int wordLine[MAXSIZE];/*integer array to store the number of words in each line*/

	printf("Enter the poem:\n");
	while(run != 0){/*while the program is running (1)*/
		if(fgets(line,MAXSIZE,stdin) != NULL){/*check if input is not null*/
			if(line[0] == 46 && line[1] == 10){/*check if there is a single period (exit case)*/
				run = 0;/*set run to 0 */
			}
			else{/*if the exit case was not entered*/
				run = 1;/*set run to 1*/
				lineC++;/*add   to line count*/
				int index = 0;
				int currentWC = 0;/*word count for the line*/
				while(line[index] != 10){/*Search through the line*/
					if(index > 0){
						/*if the previous character is a space or tab, and the current character is not a space or tab, it is a word*/
						if((line[index - 1] == 9 || line[index - 1] == 32) && (tolower(line[index]) >= 97 && tolower(line[index]) <= 122)){
							wordC++;
							currentWC++;
						}
					}else{
						if(tolower(line[index]) >=97 && tolower(line[index]) <=122){
							wordC++;
							currentWC++;
						}
					}
					index++;/*add to index to move to next character in line*/
					if(lineC - 1 < MAXSIZE){/*Check that the index the word count is being placed into is within the bounds of the array*/
						wordLine[lineC - 1] = currentWC;/*add the current word count to the word count array*/
					}else{
						printf("The number of input lines has been reached. (500)");
						run = 0;/*set run to exit condition*/
					}
				}
			}
		}
	}

	printf("%d words on %d lines\n",wordC,lineC);/*print the word number and line number*/
	/*loop through the number of lines - 1 and print out the words in the line and a space*/
	int i = 0;
	for(i = 0;i < lineC - 1;i++){
		printf("%d",wordLine[i]);
		printf(" ");
	}
	printf("%d\n",wordLine[i]);/*prinnt out the last word count without space but with newline*/
	return(0);
}