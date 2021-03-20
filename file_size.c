/*Author: Professor Wineberg (Provided for the assignment)
Assignment Part 1: file_size()
Execution and Operation Can be found in the read.me*/

#include <stdio.h>
int file_size(FILE *fp){
	int sz = 0;
	fseek(fp, 0L, SEEK_END);
	sz = ftell(fp);
	rewind(fp);
	return sz;
}