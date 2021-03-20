#include <stdio.h>

int stringCompare(char *stringA,char *stringB){
	int i = 0;
	int result = 0;
	while(stringA[i] != '\0' || stringB[i] != '\0'){/*while the strings are not at the end*/
		if(stringA[i] != stringB[i]){/*if the characters at the location i are different, the counter "result" will increase by 1"*/
			result++;
		}
		i++;
	}
	if(result > 0){/*if result is greater than 0, there is more than 0 differences in the strings*/
		return(0);
	}
	else{/*if the result is equal to 0, all the characters are equal and will return 1*/
		return(1);
	}
}