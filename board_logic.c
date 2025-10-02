#include<time.h>
#include<stdlib.h>
#include<ncurses.h>

#include"definitions.h"

void init_board(int* board_ptr, int size_y, int size_x, int num_mines){
    for (int i = 0; i < size_y*size_x; ++i){
	board_ptr[i] = IS_CLOSED;
    }

    for (int i = 0; i < num_mines; ++i){
	board_ptr[i] += IS_MINE;
    }

    srand(time(NULL));

    int rand_index;
    int temp_var;

    // Fisher-Yates Shuffle
    for (int i = size_y * size_x - 1; i >=1; --i) {
	rand_index = rand() % (i + 1);
	temp_var = board_ptr[i];
	board_ptr[rand_index] = board_ptr[i];
	board_ptr[i] = temp_var;
    }
    //TODO get mines in vicinity
}

void draw_board(int* board_ptr, int start_y, int start_x, int size_y, int size_x) {
    for (int i = 0; i < size_y; i++) {
	for (int j = 0; j < size_x; j++){
	    int board_val, ch_to_scr;	    
	    board_val = board_ptr[i*size_x + j]; 
	    if(board_val & IS_FLAGGED){
		ch_to_scr = ACS_UARROW;
	    }
	    else if (board_val & IS_CLOSED) {
		ch_to_scr = ACS_BLOCK;
	    }
	    else {
		ch_to_scr = board_val & 15; 
		//ch_to_scr = 'a';
	    }
	    mvaddch(i + start_y, j + start_x, ch_to_scr);
	}
    }
}
