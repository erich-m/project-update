#include <stdio.h>

#define IN  1   /* inside a word */
#define OUT 0   /* outside a word */

/* 
 * Program Name: wcount.c
 * Author(s): Deb Stacey
 * Date of Last Update: August 4, 2019
 * Purpose: reads input from stdin and counts the lines, words, and
 *          sentences and prints these counts to stdout.
 *          Modern version of code on page 20 of K&R (section 1.5.4).
 *          Similar to Linux command wc.
 * Compilation: cc -ansi -o wcount wcount.c
 * Execution: cat testfile1.txt | ./wcount
 * Testing: testfile(s): testfile1.txt testfile2.txt
 *          protocol: compare to wc results
 * Change Log:
 */ 

int main ( int argc, char *argv[] ) {
   char c;
   int numLines = 0;  /* number of lines */
   int numWords = 0;  /* number of words */
   int numChars = 0;  /* number of characters */

   int state = OUT;
   
   while ( (c = getchar()) != EOF ) {
      numChars++;

      if ( c == '\n' ) {
         numLines++;
      }

      if ( c == ' ' || c == '\n' || c == '\t' ) {
         state = OUT;
      } else if (state == OUT) {
         state = IN;
         numWords++;
      } 
   }
   printf ( "%d %d %d\n", numLines, numWords, numChars );

   return ( 0 );
}
