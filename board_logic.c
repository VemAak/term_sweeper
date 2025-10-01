#include<time.h>
#include<stdlib.h>
#include"definitions.h"

void init_board(int* board_ptr, int size_y, int size_x){
    for (int i = 0; i <= size_y*size_x; ++i){
	board_ptr[i] = IS_CLOSED;
    }
}
// TODO: combine these functions
void populate_mines(int* board_ptr, int num_mines, int size_y, int size_x){
    for (int i = 0; i <= num_mines; ++i){
	board_ptr[i] += IS_MINE;
    }
    srand(time(NULL));
    int rand_index;
    int temp_var;
    // Fisher-Yates Shuffle
    for (int i = size_y * size_x; i >=1; --i) {
	rand_index = rand() % (i + 1);
	temp_var = board_ptr[i];
	board_ptr[rand_index] = board_ptr[i];
	board_ptr[i] = temp_var;
    }

}
