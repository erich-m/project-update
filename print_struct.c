#include <stdlib.h>
#include <stdio.h>

#include "a2_functions.h"

void print_struct(struct Double_Array *d_array,char *header){
	printf("%s\n",header);
	printf("Struct address=%p\n",d_array);
	printf("row_size=%d, col_size=%d\n",d_array->rowsize,d_array->colsize);
	printf("Array address=%p, with contents:\n\n",d_array->array);

	print_array(d_array);

	printf("\n\n");
}