#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc,char *argv[]){

	
	char numString[5];
	int numValue = 0;

	strcpy(numString,argv[1]);

int a,b,c,d;

a = (numString[0] - '0');
b = (numString[1] - '0');
c = (numString[2] - '0');
d = (numString[3] - '0');

numValue = (a * 1000) + (b*100) + (c*10) + d;

printf("the value %s is %d", numString, numValue);
}