#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int letter_count(char * line){
	int count = 0;/*count variable*/

	int l = 0;
	while(line[l] != '\0'){/*loops through the line and counts only letters*/
		l++;
		if((65 <= line[l] && line[l] <= 90) || (97 <= line[l] && line[l] <= 122)){
			count++;
		}
	}
	count++;
	return(count);/*return the count for the letters*/
}