#include<time.h>
#include<stdlib.h>
#include<ncurses.h>

#include"definitions.h"
#include"helpers.h"

void init_board(int* board_ptr, int size_y, int size_x, int num_mines){
    int max_size_board = size_y * size_x;
    for (int i = 0; i < num_mines; ++i){
	board_ptr[i] += IS_MINE;
    }

    srand(time(NULL));

    int rand_index;
    int temp_var;

    // Fisher-Yates Shuffle
    for (int i = max_size_board - 1; i >=1; --i) {
	rand_index = rand() % (i + 1);
	temp_var = board_ptr[i];
	board_ptr[rand_index] = board_ptr[i];
	board_ptr[i] = temp_var;
    }
    int mine_count, check_mine_index;
    int offsets[] = {-size_x-1, -size_x, -size_x + 1, -1, 1, size_x -1, size_x, size_x + 1}; 
    for (int i = 0; i < max_size_board; ++i){
	board_ptr[i] ^= IS_CLOSED;

	if (board_ptr[i] & IS_MINE){
	    continue;
	}
	
	mine_count = 0;
	
	for (int offset_index = 0; offset_index < 8; ++offset_index){
	    check_mine_index = proj_interval(i + offsets[offset_index], max_size_board, 0);
	    check_mine_index = i + offsets[offset_index];
	    if (check_mine_index >= max_size_board && check_mine_index < 0){
		continue;
	    }
	    else if(board_ptr[check_mine_index] & IS_MINE){
		mine_count += 1;
	    }
	    board_ptr[i] += mine_count;
	}
    }
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
