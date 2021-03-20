#Makefile
CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -g

all: ttt1.o ttt2.o  alphatoe show_node count_nodes

ttt1.o : ttt1.c
	$(CC) $(CLFAGS) -c ttt1.c -o ttt1.o

ttt2.o : ttt2.c
	$(CC) $(CFLAGS) -c ttt2.c -o ttt2.o

show_node: show_node.o
	$(CC) $(CFLAGS) show_node.o ttt1.o ttt2.o -o show_node
show_node.o : show_node.c
	$(CC) $(CFLAGS) -c show_node.c -o show_node.o

count_nodes : count_nodes.o
	$(CC) $(CLFAGS) count_nodes.o ttt1.o ttt2.o -o count_nodes
count_nodes.o : count_nodes.c
	$(CC) $(CLFAGS) -c count_nodes.c -o count_nodes.o

alphatoe : alphatoe.o
	$(CC) $(CFLAGS) alphatoe.o ttt1.o ttt2.o -o alphatoe
alphatoe.o : alphatoe.c
	$(CC) $(CFLAGS) -c alphatoe.c -o alphatoe.o

clean :
	rm -i *.o alphatoe show_node count_nodes
clean-np:
	rm *.o alphatoe show_node count_nodes
