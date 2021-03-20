#include <stdio.h>
#include <stdlib.h>

int offset(char letter){
	int l = 0;
	if(letter >= 'A' && letter <= 'Z'){/*converts the letter to its index (A0-Z26)*/
		l = (int)(letter - 'A');
	}else if(letter >= 'a' && letter <= 'z'){/*converts the letter to its index (a0,z26)*/
		l = (int)(letter - 'a');
	}
	return(l);/*returns the letter that was entered*/
}