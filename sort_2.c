/*List Sort function by Erich MacLean Timestamp 03/12/2020*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

#include "lab4_functions.h"

Node * sort_2(Node *head, int size){
	/*The following briefly describes this list sort function designed by Erich MacLean (Timestamp: 03/12/2020 10:12pm)
	This list sort function takes in a singly linked list and performs the following: 
	1.Finds the initial minimum of the full list, where if there are multiples, it is the location nearest the end of the list.
	2.Resets the stepping and steps to that minimum Node
	3.Either starts or continues the sorted list 
	(setting a temp to the first node and then the sort to that temp)
	or (setting the temp to the next node and step through)
	4.If there are duplicates, add them to the end of the list
	5.Store the current minimum which is used as a lower, noninclusive bound int the next loop
	6.Return the new list (not stepped through yet*/
	Node * temp2 = NULL;/*creates a second list to build the sorted list from*/
	Node * sort2_head;/*creates the sort list where only after the first node is added to temp2, this points to that node and does not get reset*/
	Node * temp = head;/*create temp to step through that is equal to head and gets reset to the original head*/
	/* find the minimum and set to the head of the sorted list*/
	double old_min = DBL_MIN;
	int i = 0;
	for(i = 0;i < size;i++){
		/*find the index of the minimum of the list*/
		double min = DBL_MAX;
		int min_index = 0;
		int m = 0;
		while(temp != NULL){
			if(temp->key2 <= min && temp->key2 > old_min){/*by using the <= sign, I will find the minimum that is closest to the end of the list, if there are any duplicates*/
				min = temp->key2;
				min_index = m;
			}
			temp = temp->next;
			m++;
		}
		/*find the index of the minimum of the list*/

		/*Step back through to find that minimum*/
		temp = head;
		int s = 0;
		while(s < min_index){
			s++;
			temp = temp->next;
		}
		/*Step back through to find that minimum*/
		if(temp2 == NULL){/*only on the first loop*/
			temp2 = temp;/*created new list as set equal to temp.Sort1 pointer is still NULL*/
			sort2_head = temp2;
		}else{
			temp2->sort2 = temp;
			temp2 = temp2->sort2;
		}
		/*printf("2 Min : %f  Location : %d\n",temp2->key2,min_index);print out the minimum of the set and the location*/
		
		/*check for duplicates of that minimum*/
		int dup_count = 0;
		temp = head;
		while(temp != NULL){
			if(temp->key2 == min){
				dup_count++;
			}
			temp = temp->next;
		}
		/*check for duplicates of that minimum*/
		/*printf("Count for min %f is %d\n",min,dup_count);*/
		/*If there are duplicates, step through and link them to the list under sort2 Node pointer*/
		temp = head;
		if(dup_count > 1){
			int p = 0;
			while(temp != NULL && p < min_index){
				if(temp->key2 == min){
					temp2->sort2 = temp;
					temp2 = temp2->sort2;/*this is allowed because the list will have been created and sort2 is not NULL anymore*/
				}
				temp = temp->next;
				p++;
			}
		}
		/*If there are duplicates, step through and link them to the list under sort2 Node pointer*/

		/*now all the mins for this loop are added to the list*/

		/*change old min to this current one.Next loop will make sure new min is greater than current min*/
		old_min = min;
		/*change old min to this current one.Next loop will make sure new min is greater than current min*/
		/* find the minimum and set to the head of the sorted list*/
	}
	return(sort2_head);
}/*List Sort function by Erich MacLean Timestamp 03/12/2020*/