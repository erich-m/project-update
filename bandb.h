//Author: Erich MacLean
//Due: Spetember 22, 11:59pm
//Version 21
//bandb.h contains all the function definitions used in bandb.o
void getbytes(unsigned char dest[], int bytes, void *src, int reverse);
void getbits(char dest[], int bytes, void * src, int start, int end);
unsigned long long bits2ull(char * bits);
long long bits2ll(char * bits);
void spff(char * sign,char * exponent, char * significand, float * src);
void dpff(char * sign,char * exponent, char * significand, double * src);