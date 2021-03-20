#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*AUthor Erich MacLean
Assignment1
Part E
Date Calculator
compile: gcc -ansi -o daysCalculatorE daysCalculatorE.c
execution: ./daysCalculatorE dd-mm-yyyy dd-mm-yyyy include 
*/
int main (int argc, char *argv[]){
	int datesListA[2][3];/*{{d1, m1, y1},{d2, m2, y2}*/
	int dayTotal[12] = { 1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
 	int dayTotalL[12] = { 1, 32, 61, 92, 122, 153, 183, 214, 245, 275, 306, 336};
 	int monthLength[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	time_t now;/*get system time*/
	time(&now);/*get system time*/
	struct tm *local = localtime(&now);/*get system time*/
	int todayDate[3] = {local->tm_mday,local->tm_mon +1,local->tm_year +1900};/*get system time   {systemDay,systemMonth,systemYear}*/

	char *dateIn[] = {argv[1],argv[2]};/*Array stores input from cmd line*/

	int i = 0;/*Extract the number values from the given date input with a for loop and multiplies by the correct digit*/
	for (i=0;i < 2;i++){
		datesListA[i][0] = ((dateIn[i][0] - '0') * 10) + (dateIn[i][1] - '0');
		datesListA[i][1] = ((dateIn[i][3] - '0') * 10) + (dateIn[i][4] - '0');
		datesListA[i][2] = ((dateIn[i][6] - '0') * 1000) + ((dateIn[i][7] - '0') * 100)+ ((dateIn[i][8] - '0') * 10) + (dateIn[i][9] - '0');
	}/*Extract the number values from the given date input with a for loop and multiplies by the correct digit*/
	
	if (strcmp(argv[1],"today") == 0 || strcmp(argv[2],"today") == 0){/*if either of the command lines are "today", check which one it is*/
		int t = 0;
		if (strcmp(argv[2],"today") == 0){
			t = 1;
		}
		int ty = 0;
		for (ty = 0;ty <= 2;ty++){
			datesListA[t][ty] = todayDate[ty];
		}
	}/*If today is in the input, determine which one it is and replace it with the corresponding values*/
	
	int swap = 0;
	if (datesListA[0][2] == datesListA[1][2]){/*if the year is the same, check the dayTotal*/
		if((datesListA[0][2] % 4 == 0 && datesListA[0][2] % 100 != 0) || (datesListA[0][2] % 400 == 0)){
			if(dayTotalL[datesListA[0][1]] + datesListA[0][0] >dayTotalL[datesListA[1][1]] + datesListA[1][0]){
				swap = 1;
			}
		}else{
			if(dayTotal[datesListA[0][1]] + datesListA[0][0] >dayTotal[datesListA[1][1]] + datesListA[1][0]){
				swap = 1;
			}
		}
	}else{
		if(datesListA[0][2] > datesListA[1][2]){/*if the second year is smaller than the first year,swap*/
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
	if (datesListA[0][2] != datesListA[1][2]){
	int t1 = 0;
	int t2 = 0;
	int t3 = 0;
	if((datesListA[0][2] % 4 == 0 && datesListA[0][2] % 100 != 0) || (datesListA[0][2] % 400 == 0)){
		t1+=(366 - (dayTotalL[datesListA[0][1]-1] + datesListA[0][0]));
	}else{
		t1+=(365 - (dayTotal[datesListA[0][1]-1] + datesListA[0][0]));
	}
	
	if((datesListA[1][2] % 4 == 0 && datesListA[1][2] % 100 != 0) || (datesListA[1][2] % 400 == 0)){
		t2+=((dayTotalL[datesListA[1][1]-1] + datesListA[1][0]));
	}else{
		t2+=(dayTotal[datesListA[1][1]-1] + datesListA[1][0]);
	}

	int yr = datesListA[0][2]+1;
	for(yr = datesListA[0][2]+1;yr < datesListA[1][2];yr++){
		if((yr % 4 == 0 && yr % 100 != 0) || (yr % 400 == 0)){
			t3+=1;
		}
		t3+= 365;
	}
	total += t1 + t2 + t3;
	}
	else {
		if((datesListA[0][2] % 4 == 0 && datesListA[0][2] % 100 != 0) || (datesListA[0][2] % 400 == 0)){
			total += (((dayTotalL[datesListA[1][1]-1] + datesListA[1][0])) - (((dayTotalL[datesListA[0][1]-1] + datesListA[0][0]))));
		}
		else{
				total += (((dayTotal[datesListA[1][1]-1] + datesListA[1][0])) - (((dayTotal[datesListA[0][1]-1] + datesListA[0][0]))));
		}
	}
	if (argc > 3 && strcmp("include",argv[3]) == 0){
		total++;
	}

	printf("%d\n",total);
	return (0);
}