typedef struct element{
	int value;
	double key1;
	double key2;
	struct element *next;
	struct element *sort1;
	struct element *sort2;
}Node;
Node * create_nodes ();
double rand_double(int a,int b);
void display_list (Node * head,int version,int sizez);
Node * sort_1(Node *head, int size);
Node * sort_2(Node *head, int size);
Node * mult_value(Node *head,int factor);