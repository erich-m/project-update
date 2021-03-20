/*Author: Erich MacLean 1096984
Completed 01/28/2020 2:22AM
Due       01/29/2020 7:00PM
print_foobarbaz; prints the array of foobarbaz structs*/
#include <stdio.h>
#include <stdlib.h>

#include "lab2_functions.h"

void print_foobarbaz(struct foobarbaz **many_fbb){/*one foobarbaz struct as parameter. void function; no return value. Prints out the contents of each struct*/
	printf("foo:   bar:         baz:\n");/*prints header to label; each column*/
	int m = 0;
	while(many_fbb[m] != NULL){/*while the array element is not null, it will print out the data in the struct*/
		printf("%02d     %03.6f    %02d \n",many_fbb[m]->foo,many_fbb[m]->bar,many_fbb[m]->baz);/*print data*/
		m++;
	}
	printf("\n");
}