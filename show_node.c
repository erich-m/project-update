#include "ttt.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv){
	init_boards();
 	init_board(START_BOARD);
    join_graph(START_BOARD);
    compute_score();

    for(int a = 1;a < argc;a++){
    	print_node(htable[atoi(argv[a])]);
    }
}