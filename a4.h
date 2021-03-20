typedef struct NODE{
	value_t value;
	ley_t key;
	struct NODE * next;
	struct NODE * sort;
	struct NODE * prev;
	struct NODE * prev_sorted;
}Node;
/*Need a head called 'head' and one for the sorted forward list called 'head_sort'*/
/*Need a tail called 'tail' and one for the sorted list called 'tail_sort'*/
/*Need a field for the size of the list*/
/*The datatype should be called Sorted_List*/