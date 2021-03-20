#include <stdlib.h>
#include <stdio.h>

#include "a2_functions.h"

struct Double_Array *shallow_copy (struct Double_Array *d_array){
	struct Double_Array *d_array_copy = d_array;
	return d_array_copy;
}