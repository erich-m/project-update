#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "a2_functions.h"

struct Double_Array *deep_copy (struct Double_Array *d_array){
	struct Double_Array *d_array_copy;
	d_array_copy = malloc(sizeof(struct Double_Array));

	d_array_copy->rowsize = d_array->rowsize;
	d_array_copy->colsize = d_array->colsize;
	d_array_copy->array = d_array->array;
	return d_array_copy;
}