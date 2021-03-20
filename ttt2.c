//void init_boards();
//int depth (Board board);
//char winner(Board board);
//char turn (Board board);
//void init_board
//void join_graph(Board board);
//void compute_score
//int best_move(int board);

#include "ttt.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>

void init_boards(){
	for(int c = 0;c < HSIZE;c++){//goes through the htable and sets each init variable in the structures to 0
		htable[c].init = 0;
	}
}

int depth (Board board){
	int count = 0;
	for(int c = 0;c <= 8;c++){
		if(board[pos2idx[c]] == 'X' || board[pos2idx[c]] == 'O'){
			count++;
		}
	}
	return count;
}

char winner (Board board){
	char initial = '?';
	if(depth(board) == 9){
		initial = '-';
	}

	for(int w = 0;w < 8;w++){//loop through all possible board positions
		if(initial == '?' || initial == '-'){
			if(board[pos2idx[WINS[w][0]]] == 'X' && board[pos2idx[WINS[w][1]]] == 'X' && board[pos2idx[WINS[w][2]]] == 'X'){
				initial = 'X';
			}else if(board[pos2idx[WINS[w][0]]] == 'O' && board[pos2idx[WINS[w][1]]] == 'O' && board[pos2idx[WINS[w][2]]] == 'O'){
				initial = 'O';
			}
		}
	}
	return initial;
}

char turn(Board board){
	int currentDepth = depth(board);
	char turn = '-';

	if(currentDepth % 2 == 0){
		turn = 'X';
	}else{
		turn = 'O';
	}

	if(currentDepth == 9){
		turn = '-';
	}

	return turn;
}

void init_board(Board board){
	int index = board_hash(board);

	htable[index].init = 1;
	htable[index].turn = turn(board);
	htable[index].depth = depth(board);
	strcpy(htable[index].board,board);
	htable[index].winner = winner(board);
}

void join_graph(Board board){
	for(int p = 0;p <= 8;p++){//loop through all possible move positions
		int index = board_hash(board);//get the index of the current board
		if(board[pos2idx[p]] == 'X' || board[pos2idx[p]] == 'O'){//if there is a piece here already
			htable[index].move[p] = -1;//set move at the current index to -1
		}else{//there is no piece at the current location
			Board copy = "0|1|2\n-+-+-\n3|4|5\n-+-+-\n6|7|8\n";//make a copy of the board
			strcpy(copy,board);//strcpy into new board
			char piece = turn(board);//get the turn for the new board
			copy[pos2idx[p]] = piece;//set the current spot in the new board to the new piece
			int newIndex = board_hash(copy);//get a new index for the copy of the board
			htable[index].move[p] = newIndex;
			if(htable[newIndex].init == 0){//if the board is not initialized, initialize it, and call join_graph on it
				init_board(copy);
				join_graph(copy);
			}
		}
	}
}

void compute_score(){for(int d = 9;d >= 0;d--){
	for(int h = 0;h < HSIZE;h++){
		if(htable[h].init == 1){
			if(htable[h].depth == d){
				char current_turn = htable[h].turn;//get the current turn
				char current_winner = htable[h].winner;

				if(current_winner == 'X'){
					htable[h].score = 1;
				}else if(current_winner == 'O'){
					htable[h].score = -1;
				}else if(current_winner == '-'){
					htable[h].score = 0;
				}else{//current_winner == ?
					if(current_turn == 'X'){
						int max_score = -1;

						for(int m = 0;m < 9;m++){
							int current_next = htable[h].move[m];
							if(current_next != -1){
								if(htable[current_next].score > max_score){
									max_score = htable[current_next].score;
								}
							}
						}

						htable[h].score = max_score;
					}else{//current_turn == 'O'
						int min_score = 1;

						for(int m = 0;m < 9;m++){
							int current_next = htable[h].move[m];
							if(current_next != -1){
								if(htable[current_next].score < min_score){
									min_score = htable[current_next].score;
								}
							}
						}

						htable[h].score = min_score;
						}
					}
				}
			}
		}
	}
}

int best_move(int board){
	int best_score = -1;
	int best_index = 0;
	for(int m = 0;m < 9;m++){
		int current_next = htable[board].move[m];
		if(htable[current_next].score > best_score){
			best_score = htable[current_next].score;
			best_index = current_next;
		}
	}
	return best_index;
}