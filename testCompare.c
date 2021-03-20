#include <stdio.h>

int stringCompare(char *stringA,char *stringB);

int main (int argc,char *argv[]){
	int result = 0;
	char *a = "Erich";
	char *b = "My Name Is Erich";

	result = stringCompare(a,b);

	printf("%d\n",result);
	return(0);
}