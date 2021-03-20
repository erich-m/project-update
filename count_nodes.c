#include "ttt.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>

int main (int argc, char ** argv){
	init_boards();
 	init_board(START_BOARD);
    join_graph(START_BOARD);

    int total = 0;

    for(int t = 0;t < HSIZE;t++){
    	if(htable[t].init == 1){
    		total++;
    	}
    }

    printf("%d\n",total);
}