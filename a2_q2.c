#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "a2_functions.h"

#define rowSize 5
#define colSize 9

int main(int argc,char *argv[]){
	srand(time(0));
	printf("---------------------\nQuestion 2 A\n---------------------\n");/*print question header*/
	struct Double_Array *a1 = double_array(rowSize,colSize);/*Declare a variable called a1 that holds aDouble_Array struct thatcontains a6 x9 array(as in Q1)*/
	randomize_array(a1,0,10);/*Initializea1to random values between 0.0 and 10.*/
	printf("The address of a1 is %p\n",a1);/*Print the address of a1 using the printf command "the address of a1 is %p"*/
	print_struct(a1,"The structure pointed to by a1 is:\n");/*Print the structure pointed to by a1 with the header "The structure is pointed to by a1 is:"*/
	struct Double_Array *a2 = a1;/*Decalre a variable a2 that can hold the same struct pointer as a1 and set a2=a1*/
	printf("The address of a2 is %p\n",a2);/*Print the address of a2 using the printf command "the address of a1 is %p"*/
	print_struct(a2,"The structure pointed to by a2 is:\n");/*Print the structure pointed to by a2 with the header "The structre pointed to by a2 is:"*/
	struct Double_Array *a_shallow = shallow_copy(a1);/*Create a shallow copy of a1 and store it in the vairable a_shallow*/
	printf("The address of a_shallow is %p\n",a_shallow);/*Print the address of a_shallow using the printf command "the address of a_shallow is %p"*/
	print_struct(a_shallow,"The structure pointed to by a_shallow is:\n");/*Print the structure pointed to by a2 with the header "the structure pointed to by a_shallow is:"*/
	struct Double_Array *a_deep = deep_copy(a1);/*Create a deep copy of a1 and store it in a varriable called a_deep*/
	printf("The address of a_deep is %p\n",a_deep);/*Print the address of a_deep using the printf command "the address of a_deep in %p*/
	print_struct(a_deep,"The structure pointed to by a_deep is:\n");/*Print the strucure pointed to by a2 with the header "The structure pointed to by a_deep is:"*/
	printf("\n\n\n");/*Print 3 blank lines*/


	printf("---------------------\nQuestion 2 B\n---------------------\n");/*print question header*/
	a1->array[0][1] = 100.0;
	a2->array[1][2] = 200.0;
	a_shallow->array[2][3] = 300.0;
	a_deep->array[3][4] = 400.0;
	print_struct(a1,"Struct a1 :\n");
	print_struct(a2,"Struct a2 :\n");
	print_struct(a_shallow,"Struct a_shallow :\n");
	print_struct(a_deep,"Struct a_deep :\n");
	printf("\n\n\n");


	printf("---------------------\nQuestion 2 C\n---------------------\n");/*print question header*/
	struct Double_Array *b1 = double_array(rowSize,colSize);
	randomize_array(b1,10,20);
	a2->array = b1->array;
	print_struct(a1,"Struct a1 :\n");
	print_struct(a2,"Struct a2 :\n");
	print_struct(a_shallow,"Struct a_shallow :\n");
	print_struct(a_deep,"Struct a_deep :\n");
	a1->array[0][1] = 5000.0;
	a2->array[1][2] = 6000.0;
	a_shallow->array[2][3] = 7000.0;
	a_deep->array[3][4] = 8000.0;
	b1->array[4][5] = 9000.0;
	print_struct(a1,"Struct a1 :\n");
	print_struct(a2,"Struct a2 :\n");
	print_struct(a_shallow,"Struct a_shallow :\n");
	print_struct(a_deep,"Struct a_deep :\n");
	print_struct(b1,"Struct b1 :\n");

	/*Question 2 D*//*
	int f = 0;
	for(f = 0;f < rowSize;f++){
		a1->array[0] = NULL;
		free(a1->array[f]);
		a1->array[0] = NULL;
		b1->array[0] = NULL;
		free(b1->array[f]);
		b1->array[0] = NULL;
	}*/

	/*this part is commented out because I kept double freeing memory somehow and I do not know where it is happening*/

	a1->array = NULL;
	free(a1->array);
	a1->array = NULL;
	b1->array = NULL;
	free(b1->array);
	b1->array = NULL;
	a1 = NULL;
	free(a1);
	a1 = NULL;
	b1=NULL;
	free(b1);
	b1=NULL;
	return(0);
}