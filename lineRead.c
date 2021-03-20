#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 500   /* maximum size of input line */

/* 
 * Program Name: lineRead.c
 * Author(s): Deb Stacey
 * Date of Last Update: August 20, 2019
 * Purpose: reads input from stdin in line increments until
 *          EOF and prints them out again and counts the number
 *          of lines and characters.
 * Compilation: cc -ansi -o lineRead lineRead.c
 * Execution: cat testfile1.txt | ./lineRead
 * Testing: testfile(s): testfile1.txt testfile2.txt
 *          protocol: compare to wc results
 * Change Log:
 */ 

int main ( int argc, char *argv[] ) {
   char line[MAXSIZE];
   int numLines = 0;  /* number of lines */
   int numChars = 0;  /* number of chars */
   int numWords = 0;  /* number of words */
   int i = 0;

   while ( fgets ( line, MAXSIZE, stdin ) != NULL ) {
   	printf(line);
      numChars = numChars + (int)strlen(line);
      numLines++;
   }
   printf ( "Number of Lines = %d\n", numLines );
   printf ( "Number of Chars = %d\n", numChars );

   return ( 0 );
}
