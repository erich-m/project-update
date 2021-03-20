#include <stdlib.h>

double rand_double(double a, double b){/*2 integers as parameter. Returns double. gives random double within range of parameters*/
	if(b > a){/*if b is greater than a, b is max and a is the min*/
		return (((double) rand() / (double) RAND_MAX) * (b-a) + a);
	}else if (b < a){/*if a is greater than b, a is max and b is the min*/
		return (((double) rand() / (double) RAND_MAX) * (a-b) + b);
	}else{/*if neither of them are greater, the function returns a because there are no in between values if a=b*/
		return (double)a;
	}
	return(0);/*default return is 0*/
}