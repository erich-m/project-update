#include <stdio.h>

#define B 2
int a = 1;

int globalFunction();

int main (int argc,char *argv[]){
	printf("My mainline %d\n",a);
	printf("My define in main %d\n",B);
	globalFunction();
}