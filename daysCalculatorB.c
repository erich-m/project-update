#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*AUthor Erich MacLean
Assignment1
Part B
Date Calculator
compile: gcc -ansi -o daysCalculatorB daysCalculatorB.c
execution: ./daysCalculatorB dd mm yyyy dd mm yyyy include 
*/
int main (int argc, char *argv[]){
	int datesListA[2][3] = {{atoi(argv[1]),atoi(argv[2]),atoi(argv[3])},{atoi(argv[4]),atoi(argv[5]),atoi(argv[6])}};/*{{d1, m1, y1},{d2, m2, y2}*/
	int dayTotal[12] = { 1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
 	int dayTotalL[12] = { 1, 32, 61, 92, 122, 153, 183, 214, 245, 275, 306, 336};
 	int monthLength[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


	int swap = 0;
		if((datesListA[0][2] % 4 == 0 && datesListA[0][2] % 100 != 0) || (datesListA[0][2] % 400 == 0)){
			if(dayTotalL[datesListA[0][1]] + datesListA[0][0] >dayTotalL[datesListA[1][1]] + datesListA[1][0]){
				swap = 1;
			}
		}else{
			if(dayTotal[datesListA[0][1]] + datesListA[0][0] >dayTotal[datesListA[1][1]] + datesListA[1][0]){
				swap = 1;
			}
		}

	if (swap == 1){
		int temp[3] = {datesListA[1][0],datesListA[1][1],datesListA[1][2]};
		int tSwap = 0;
		for(tSwap = 0;tSwap <= 2;tSwap++){
			datesListA[1][tSwap] = datesListA[0][tSwap];
			datesListA[0][tSwap] = temp[tSwap];
		}
	}
/*
	int x = 0;
	int y = 0;
	for (x = 0;x < 2;x++){
		for(y = 0;y < 3;y++){
			printf("%d\n",datesListA[x][y]);
		}
	}*/
/*{{d1, m1, y1},{d2, m2, y2}*/
	int total = 0;
		if((datesListA[0][2] % 4 == 0 && datesListA[0][2] % 100 != 0) || (datesListA[0][2] % 400 == 0)){
			total += (((dayTotalL[datesListA[1][1]-1] + datesListA[1][0])) - (((dayTotalL[datesListA[0][1]-1] + datesListA[0][0]))));
		}
		else{
			total += (((dayTotal[datesListA[1][1]-1] + datesListA[1][0])) - (((dayTotal[datesListA[0][1]-1] + datesListA[0][0]))));
		}
	if (argc > 7 && strcmp("include",argv[7]) == 0){
		total++;
	}

	printf("%d\n",total);
	return (0);
}