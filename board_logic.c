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
	board_ptr[i] = board_ptr[rand_index];
	board_ptr[rand_index] = temp_var;
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
	    //Check if left hand side of board
	    if (0 == (i % size_x) && (0 == offset_index || 3 == offset_index || 5 == offset_index)){
		continue;
	    }
	    //Check if right hand side of board
	    if (0 == ((i +1) % size_x) && (2 == offset_index || 4 == offset_index || 7 == offset_index)){
		    continue;
		}
	    check_mine_index = i + offsets[offset_index];
	    if (check_mine_index >= max_size_board | check_mine_index < 0){
		continue;
	    }
	    else if(board_ptr[check_mine_index] & IS_MINE){
		mine_count += 1;
	    }
	}
	board_ptr[i] += mine_count;
    }
}

void draw_board(int* board_ptr, int start_y, int start_x, int size_y, int size_x) {
    int color_pair_id;
    int num_mines;
    int board_val, ch_to_scr;	    
    for (int i = 0; i < size_y; i++) {
	for (int j = 0; j < size_x; j++){
	    num_mines = 0;
	    board_val = board_ptr[i*size_x + j]; 
	    if (board_val & IS_EXPLODED) {
		ch_to_scr = ACS_NEQUAL;
		color_pair_id = COLOR_EXPL;
	    }
	    else if(board_val & IS_FLAGGED){
		ch_to_scr = ACS_UARROW;
		color_pair_id = COLOR_FLAG; 
	    }
	    else if (board_val & IS_CLOSED) {
		ch_to_scr = ACS_BLOCK;
		color_pair_id = COLOR_CLOSED;
	    }
	 //   else if (board_val & IS_MINE) {
		//ch_to_scr = ACS_NEQUAL;
	    //}
	    else {
		num_mines = board_val & 15;
		ch_to_scr = (num_mines) + 48; 
		if (0 == num_mines) {
		    ch_to_scr = ' ';
		}
		//ch_to_scr = 'a';
		color_pair_id = num_mines + 1;
	    }
	    mvaddch(i + start_y, j + start_x, ch_to_scr | COLOR_PAIR(color_pair_id));
	}
    }
}

void fail_game(int *board_ptr, int size_y, int size_x){
    for (int board_index = 0; board_index < size_y*size_x -1; ++board_index){
	if (board_ptr[board_index] & IS_MINE) {
	    board_ptr[board_index] += IS_EXPLODED;
	}
    }
    //TODO Stop input and allow restarts
}

void open_square(int *board_ptr, int size_y, int size_x, int y_pos, int x_pos) {
  int square_val = board_ptr[y_pos * size_x + x_pos];
  if (square_val & IS_FLAGGED) {
    return;
  }
    if (square_val & IS_MINE) {
	fail_game(board_ptr, size_y, size_x);
	return;
    }
  if (square_val & IS_CLOSED) {
    board_ptr[y_pos * size_x + x_pos] ^= IS_CLOSED;
      if (0 == (square_val & 15)) {
	int deltas[] = {-1, 0, 1};
	for (int y_delta = 0; y_delta < 3; ++y_delta) {
	  for (int x_delta = 0; x_delta < 3; ++x_delta) {
	    open_square(board_ptr, size_y, size_x,
			proj_interval(y_pos + deltas[y_delta], size_y - 1, 0),
			proj_interval(x_pos + deltas[x_delta], size_x - 1, 0));
          }
        }
      }
  }
}

void flag_square(int *board_ptr, int size_y, int size_x, int y_pos, int x_pos) {
    if (board_ptr[(y_pos)*size_x + (x_pos)] & IS_CLOSED) {
	board_ptr[(y_pos)*size_x + (x_pos)] ^= IS_FLAGGED;
    }
    else {
	return;
    }

}
