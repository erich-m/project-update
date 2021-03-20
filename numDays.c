#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*AUthor Erich MacLean
Lab4
Date Adder
compile: gcc -ansi -o numDays numDays.c
execution: ./daysCalculatorA dd mm yyyy numOfDays 
*/
int main (int argc, char *argv[]){
	/*if argc[4] is greater than 300 or invalid date from lab 2, print and invalid statement and return not 0*/
		/*an invalid date: month does not fit into the year range, or the month is the wrong length, or the day does not fit into the month*/


	int dayTotal[12] = { 1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
 	int dayTotalL[12] = { 1, 32, 61, 92, 122, 153, 183, 214, 245, 275, 306, 336};
 	int monthLength[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 	int monthLengthL[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

 	int dd,mm,yyyy,add;
 	dd = atoi ( argv[1] );
    mm = atoi ( argv[2] );
    yyyy = atoi ( argv[3] );
    add = atoi(argv[4]);

    int newD = 0;
    int newM = 0;
    int newY = yyyy;

if (add > 300){
	printf("Invalid number of days\n");
	return(1);
}
if ((yyyy % 4 == 0 && yyyy % 100 != 0) || (yyyy % 400 == 0)){/*if the year is a leap year*/
	if((mm<0||mm>12) || (dd < 0 || dd > monthLengthL[mm-1])){
		printf("Invalid date\n");
		return(1);
	}
}else{
	if((mm<0||mm>12) || (dd < 0 || dd > monthLength[mm-1])){/*if the year is not a leap year*/
		printf("Invalid date\n");
		return(1);
	}
}

/*if the program doesnt exit on an error in the input, the prgoram will continue to run without need for an if statement*/

int daysum = dd;
int sameyear = 0;/*if 0, then same year, if 1, different year*/
if ((yyyy % 4 == 0 && yyyy % 100 != 0) || (yyyy % 400 == 0)){
	daysum += dayTotalL[mm-1];
	if(daysum + add > 366){
		sameyear = 1;
	}
}else {
	daysum += dayTotal[mm-1];
	if (daysum + add > 365){
		sameyear = 1;
	}
}
daysum+=add;
if(sameyear == 1){
	newY++;
	if ((yyyy % 4 == 0 && yyyy % 100 != 0) || (yyyy % 400 == 0)){
		daysum -= 366;
	}else {
		daysum -= 365;
	}
}

int i = 0;
int msum = 0;
if ((newY % 4 == 0 && newY % 100 != 0) || (newY % 400 == 0)){
	while(msum + monthLengthL[i] < daysum){
		msum += monthLengthL[i];
		i++;
	}
}
else{
	while(msum + monthLength[i] < daysum){
		msum += monthLength[i];
		i++;
	}
}
newM = i+1;
newD = daysum - msum - 1;
printf("%02d %02d %04d\n",newD,newM,newY);
return(0);
}