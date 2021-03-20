#include <stdlib.h>
#include <stdio.h>

int isLeap (int year);

int main (int argc,char *argv[]){
	if(argc == 3){

		int startYear = atoi(argv[1] - 0);
		int numLeaps = atoi(argv[2] - 0);

		int y = 0;

		while(y < numLeaps){
			if(isLeap(startYear)==1){
				y++;
				printf("%d\n",startYear);
			}
			startYear++;
		}
	}
	return(0);
}