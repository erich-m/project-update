#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "lab4_functions.h"

int main (int argc,char * argv[]){
	srand(time(0));/*generates different random values using time as a seed for the random values.*/
	printf("Enter the size of list you want:\n");
	int size = 0;
	fscanf(stdin,"%d",&size);
	while(size < 5){
		printf("Please eneter a size greater than or equal to 5:\n");
		fscanf(stdin,"%d",&size);
	}
	Node *head = NULL;/*create node called head*/
	head = create_nodes(size);/*make a list with size of size*/

	display_list(head,0,size);/*prints the three numbers in each node of the list*/
	Node *sort1_head = sort_1(head,size);
	display_list(sort1_head,1,size);
	Node *sort2_head = sort_2(head,size);
	display_list(sort2_head,2,size);

	Node * new_head = head;
	new_head = mult_value(new_head,10);
	display_list(new_head,0,size);/*prints the three numbers in each node of the list*/
	sort1_head = sort_1(new_head,size);
	display_list(sort1_head,1,size);
	sort2_head = sort_2(new_head,size);
	display_list(sort2_head,2,size);
	return(0);
}