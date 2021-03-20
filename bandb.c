////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Auhtor: Erich MacLean
Assignment 1
Due: September 22, 11:59pm
Version 21*/
#include <stdlib.h>
#include <stdio.h>
#include "bandb.h"


//getbytes:
//Extracts the bytes from the src array and either copies directly, or reverses them into the dest array
//No return value
void getbytes(unsigned char dest[], int bytes, void *src, int reverse){
	unsigned char * source = src;
	if(reverse == 0){//if reverse is 0, copy the values straight into the dest from source		
		//instead of looping through the source array, I need to make ssure that there is enough space in the dest array. Therefore, I need to loop throught the dest array to copy the values.
		for(int d = 0;d<bytes;d++){
			//	printf("[%c]\n",source[d]);
			dest[d] = source[d];
		}
	}
	if (reverse != 0){
		int j = 0;
		for(int i = bytes -1;i >= 0;i--){//THis loop will start at the end of the dest array and loop backwards through it
			dest[i] = source[j];
			j++;//j is the index for the source array that jumps an equal step up from the start of source. This means that "abcdefgh" will become "hgfedcba" 
		}
	}
	dest[bytes] = '\0';//Reduntant but protective measure to ensure there is a null character at the end of the dest array
}



//getbtis:
//Extracts singular bits from each index of the src array
//No return value
void getbits(char dest[], int bytes, void *src, int start, int end){
	unsigned char * source = src;
	/*
	for(int k = 0;k < bytes;k++){
		printf("{%c %d}\n",source[k],source[k]);
	}
	*/
	int d = 0;//location of current bit in the dest array

	int s_src_index = bytes - (start/8) - 1;//index of the start bit
	int e_src_index = bytes - (end/8) - 1;//index of the end bit

	for(int cbyte = 0;cbyte < bytes;cbyte++){//Loop through each cbyte of source

		int bit_s_index = 0;//default start bit index within the cbyte
		int bit_e_index = 7;//default end bit index within the cbyte

		if(cbyte == s_src_index){//The current cbyte contains the starting bit
			bit_s_index = 7 - (start%8);
		}
		if(cbyte == e_src_index){//The current cbyte contains the ending bit
			bit_e_index = 7 - (end%8) - 1;
		}

	//	printf("[%d %d]\n",bit_s_index,bit_e_index);

		for(int b = bit_s_index;b <= bit_e_index;b++){//loop through each bit within range of indecies
			int bit_shift = 8 - 1 - b;//Calculate the bit shift to obtain the next bit
			int new_bit = (source[cbyte]>>bit_shift)&1;//Calculate bit
			if(new_bit == 0){//convert bit to char
				dest[d] = '0';
				d++;//add to the index of dest
			}else{
				dest[d] = '1';
				d++;//add to index of dest
			}
		}
		//printf("\nByte:%d\n",cbyte);
	}
	dest[d] = '\0';//terminate the end of dest
	//printf("\n");
}




//bits2ull:
//read bits (formatted as strings) in from char * bits, and make an unsigned long long equal to that input
//returns the unsigned long long
unsigned long long bits2ull(char * bits){
	int length = 0;//let length be the length for the char * bits

	//bits read in from left to right (-->0101110001101-->) need length of char * bits
	while (bits[length] != '\0'){
	//	printf("%c",bits[length]);
		length++;
	}
	//length-1 is the end character
	//printf("\n");
	unsigned long long ull = 0;
	unsigned long long power = 1;
	//loop again backwards through bits. Add the bit, then multiply the number by ten to shift everything to the left
	
	for (int i = length -1;i >= 0;i--){
		//printf("%d",bits[i]-48);
		ull += (bits[i] - 48) * power;
		//printf("%d : %llu\n",i,ull);
		power *= 2;
	}
	//ull += bit(as num) * pow(10,i)
	return(ull);
}



//bits2ll:
//read bits (formatted as strings) in from char * bits, and make a long long equal to the given input
//returns a long long
long long bits2ll(char * bits){
	int length = 0;//let length be the length of the char * bits
	int check_minus = 1;//if first bit is 0, then check_minus=1. If first bit is 1, then check_minus=-1
	//bits read in from left to right (-->0101110001101-->) need length of char * bits
	while (bits[length] != '\0'){
	//	printf("%c",bits[length]);
		if(bits[length] == 49 && length == 0){//Check the first bit for check_minus number
			check_minus = -1;
		}
		length++;
	}
	//length-1 is the end character

	long long ll = 0;
	unsigned long long power = 1;
	for (int i = length -1;i >= 0;i--){
		int bit = (bits[i] - 48);//create an int with the current bit

		if (check_minus == -1 && (bits[i] - 48)==0){//if the number is be negative, convert the bit to it's complement
			bit = 1;
		}else if (check_minus == -1 && (bits[i] - 48)==1){
			bit = 0;
		}
	 	ll += bit * power;
		power *= 2;
	}
	//printf("%lld\n",ll);
	//Multiply by check_minus which is negative if the number is negative
	//Then subtract 1
	if(check_minus == -1){
		ll *= check_minus;
		ll--;
	}
	return(ll);
}



//spff:
//create a binary number in the form of a the corresponding strings from the float src
//no return value
void spff (char * sign,char * exponent,char * significand,float * src){
	//1 bit for the sign
	//8 bits for the exponent
	//23 bits for the fraction
	float source = *src;
	//convert sign
	//convert integer part
	//convert fractional part
	int exp_lim = 8;//sets the limit of the number of bits in the exponent
	exp_lim--;
	int sig_lim = 23;//sets the limit on the number of bits in the significand
	sig_lim--;

	//printf("Source : %f\n",source);
	//convert sign
	if(source >= 0){
		*sign = '0';
	}else{
		*sign = '1';
		source *= -1;//Normalize the float to be always positive
	}

	//split into int and fraction parts
	int i = source;//Get integer
	float fraction = source - i;//Get fraction

	//convert integer
	for (int j = exp_lim; j >= 0;j--){//j is the number of bits to shift right by each time
		int bit = i>>j;//shift the integer byte right by j bits
		bit  = bit & 1;//Extract the bit from the byte
		if(bit == 0){
			exponent[exp_lim-j] = '0';//convert bit to char and add to exponent char array
		}else{
			exponent[exp_lim-j] = '1';//convert bit to char and add to exponent char array
		}
	}

	//convert fraction
	//Multiply fraction until the products fractional component is 0 or the precision limit is reached
	float f = fraction;
	int k = 0;//let k be the indexx of the significand
	float prod_frac = 1;
	int prod_int;

	//while loop will either loop through from 0-22 inclusive (sig_lim = 23 - 1) or until the stop case is reached for conversion
	while ((k <= sig_lim) && (prod_frac != 0)){//loop while the fractional portion of the product is not 0, and only while k is less than 23
		f = f * 2;//Multiply the fraction by 2
		//printf("Remainder %f\n",f);
		prod_int = f;//Split the integer of the product
		prod_frac = f - prod_int;//split the fraction of the product

		if(prod_int == 0){
			significand[k] = '0';//Convert bit to char in the significand
		}else{
			significand[k] = '1';//Convert bit to char in the significand
		}

		f = prod_frac;//Set f to the new fraction component
		k++;//increase k by 1
	}
	significand[k] = '\0';//set next char to EOF char
}



//dpff:
//create a binary number in the form of a the corresponding strings from the float src
//no return value
void dpff (char * sign, char * exponent,char * significand, double *src){
	//1 bit for the sign
	//11 bits for the exponent
	//52 bits for the fraction
	double source = *src;
	//convert sign
	//convert integer part
	//convert fractional part
	int exp_lim = 11;//sets the limit on the number of bits in the exponent
	exp_lim--;
	int sig_lim = 52;//sets the limit on the number of bits in the significand
	sig_lim--;

	//printf("Source : %f\n",source);
	//convert sign
	if(source >= 0){
		*sign = '0';
	}else{
		*sign = '1';
		source *= -1;//Normalize the float to be always positive
	}

	//split into int and fraction parts
	int i = source;//Get integer
	double fraction = source - i;//Get fraction

	//convert integer
	for (int j = exp_lim; j >= 0;j--){//j is the number of bits to shift right by each time
		int bit = i>>j;//shift the integer byte right by j bits
		bit  = bit & 1;//Extract the bit from the byte
		if(bit == 0){
			exponent[exp_lim-j] = '0';//convert bit to char and add to exponent char array
		}else{
			exponent[exp_lim-j] = '1';//convert bit to char and add to exponent char array
		}
	}

	//convert fraction
	//Multiply fraction until the products fractional component is 0 or the precision limit is reached
	double f = fraction;
	int k = 0;//let k be the indexx of the significand
	double prod_frac = 1;
	int prod_int;
	//while loop will either loop through from 0-51 inclusive (sig_lim = 52 - 1) or until the stop case is reached for conversion
	while ((k <= sig_lim) && (prod_frac != 0)){//loop while the fractional portion of the product is not 0, and only while k is less than 23
		f = f * 2;//Multiply the fraction by 2
		//printf("Remainder %f\n",f);
		prod_int = f;//Split the integer of the product
		prod_frac = f - prod_int;//split the fraction of the product

		if(prod_int == 0){
			significand[k] = '0';//Convert bit to char in the significand
		}else{
			significand[k] = '1';//Convert bit to char in the significand
		}

		f = prod_frac;//Set f to the new fraction component
		k++;//increase k by 1
	}
	significand[k] = '\0';//set next char to EOF char
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////