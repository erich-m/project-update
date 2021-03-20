#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "a3_functions.h"

int to_decode (int shift){/*takes the encode shift and returns the shift that will decode it*/
	shift = 26 - shift;
	return shift;
}