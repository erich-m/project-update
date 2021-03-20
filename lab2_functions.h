/*Author: Erich MacLean 1096984
Completed 01/28/2020 2:22AM
Due       01/29/2020 7:00PM
Header file for the functions for Lab assignment 2*/
double rand_double(int a, int b);
struct foobarbaz{
	int foo;
	double bar;
	int baz;
};
struct foobarbaz *rand_foobarbaz();
struct foobarbaz **many_foobarbaz();
void print_foobarbaz(struct foobarbaz **many_fbb);
void swap_foobarbaz (struct foobarbaz **many_fbb, int index_1, int index_2);
void free_foobarbaz (struct foobarbaz **many_fbb);