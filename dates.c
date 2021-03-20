#include <stdio.h>
#include <stdlib.h>

/*
 *   Program name: dates.c
 *   Author: Erich MacLean
 *   Last Update: September 16, 2019
 *   Function: to print out date given on command line
 *   Compilation: gcc -ansi -o dates dates.c
 *   Execution: ./dates 23 8 2019
 */

int main ( int argc, char *argv[] ) {

   /* Names of the months */
   char *monthName[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September",
                      "October", "November", "December" };

   /* The number of days in each month */
   int monthLength[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   int dd = 0;
   int mm = 0;
   int yyyy = 0;

   if ( argc < 4 ) {
      printf ( "Usage: ./dates mm dd yyyy \n" );
      exit ( 1 );
   } else {
      dd = atoi ( argv[1] );
      mm = atoi ( argv[2] );
      yyyy = atoi ( argv[3] );
   }

   /* Remember that arrays like monthName and monthLength start their index at 0 and not 1. */
   /* The first entry in the array is monthName[0], monthLength[0] */
   

   /*Task 2*/
   if(mm > 12 || mm < 1){
   	   printf("Error - the month entered (%d) is not in the proper range (1-12)\n",mm);
   	   return(1);
   }
   /*Task 4*/
   if((yyyy % 4 == 0 && yyyy % 100 != 0) || (yyyy % 400 == 0)){
   	printf("%d is a leap year\n",yyyy);
   	monthLength[1]++;
   }


   /*Task 3*/
   if(dd > monthLength[mm-1] || mm < 1){
   	   printf("Error - you entered %d for the day and that is not in the range (1-%d)\n",monthLength[mm-1],monthLength[mm-1]);	
   	   return(1);
   }
   /*Task 2*/


   /*Task 1*/
   printf ( "The date is %s %02d, %04d\n",monthName[mm-1],dd,yyyy);
   /*Task 1*/
   printf ( "In %s there are %d days\n", monthName[mm-1], monthLength[mm-1] );

   return ( 0 );
}
