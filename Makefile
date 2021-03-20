all : a2_q1 a2_q2
a2_q1 : a2_q1.c double_array.o print_struct.o deep_copy.o randomize_array.o rand_double.o print_array.o free_array.o swap_rows.o swap_columns.o shallow_copy.o
	gcc -ansi -Wall a2_q1.c double_array.o print_struct.o deep_copy.o randomize_array.o rand_double.o print_array.o free_array.o swap_rows.o swap_columns.o shallow_copy.o -o a2_q1
a2_q2 : a2_q2.c double_array.o print_struct.o deep_copy.o randomize_array.o rand_double.o print_array.o free_array.o swap_rows.o swap_columns.o shallow_copy.o
	gcc -ansi -Wall a2_q2.c double_array.o print_struct.o deep_copy.o randomize_array.o rand_double.o print_array.o free_array.o swap_rows.o swap_columns.o shallow_copy.o -o a2_q2
double_array.o : double_array.c
	gcc -ansi -Wall -c double_array.c
randomize_array.o : randomize_array.c
	gcc -ansi -Wall -c randomize_array.c
rand_double.o : rand_double.c
	gcc -ansi -Wall -c rand_double.c
print_array.o : print_array.c
	gcc -ansi -Wall -c print_array.c
free_array.o : free_array.c 
	gcc -ansi -Wall -c free_array.c
swap_rows.o : swap_rows.c
	gcc -ansi -Wall -c swap_rows.c
swap_columns.o : swap_columns.c
	gcc -ansi -Wall -c swap_columns.c
shallow_copy.o : shallow_copy.c
	gcc -ansi -Wall -c shallow_copy.c
deep_copy.o : deep_copy.c
	gcc -ansi -Wall -c deep_copy.c
print_struct.o : print_struct.c
	gcc -ansi -Wall -c print_struct.c
clean :
	rm *.o a2_q1 a2_q2