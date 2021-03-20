#include <stdio.h>

#include "bandb.h"

int main( int argc, char **argv )
{
  unsigned short num = 12101; /* 0010111101000101-> /E */
  unsigned char bytes[2];
  char string[17];

  getbits( string, sizeof(unsigned short), &num, 15, -1 );
  printf( "%s\n", string );
 
  getbytes( bytes, sizeof(unsigned short), &num, 1 );

  getbits( string, sizeof(unsigned short), bytes, 15, -1 );
  printf( "%s\n", string );
   
  getbits( string, sizeof(unsigned short), bytes, 15, 7 );
  printf( "%s\n", string );

  getbits( string, sizeof(unsigned short), bytes, 7, -1 );
  printf( "%s\n", string );

  getbits( string, sizeof(unsigned short), bytes, 11, 3 );
  printf( "%s\n", string );

  return 0;
}
