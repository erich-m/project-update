all : lab4
lab4 : lab4.c rand_double.o create_nodes.o display_list.o sort_1.o sort_2.o mult_value.o
	gcc -ansi -Wall lab4.c rand_double.o create_nodes.o display_list.o sort_1.o sort_2.o mult_value.o -o lab4
rand_double.o : rand_double.c
	gcc -ansi -Wall -c rand_double.c
create_nodes.o : create_nodes.c
	gcc -ansi -Wall -c create_nodes.c
display_list.o : display_list.c 
	gcc -ansi -Wall -c display_list.c
sort_1.o : sort_1.c
	gcc -ansi -Wall -c sort_1.c
sort_2.o : sort_2.c
	gcc -ansi -Wall -c sort_2.c
mult_value.o : mult_value.c
	gcc -ansi -Wall -c mult_value.c
clean : 
	rm *.o lab4