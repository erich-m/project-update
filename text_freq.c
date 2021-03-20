#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int * text_freq (char * line){
	int * table;
	table = malloc(sizeof(int) * 26);/*Malloc space for an integer table to store the frequencies*/
	int t = 0;
	for (t = 0;t < 26;t++){/*declares all elements to 0 as default*/
		table[t] = 0;
	}

	int l = 0;
	while (line[l] != '\0'){/*loop through the line*/
		int index = 0;
		if((line[l] >= 'A' && line[l] <= 'Z' )|| ('a' <= line[l] && line[l] <= 'z')){
			/*for each character, if it is a lower case, subtract 97 and if it is upper case, subtract 65*/
			if(65 <= line[l] && line[l] <= 90){
				index = line[l] - 65;
			}
			else if(97 <= line[l] && line[l] <= 122){
				index = line[l] - 97;
			}
			table[index]++;
		}
		l++;
	}/*Loop through the line*/
	return(table);/*return the table*/
}