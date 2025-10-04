#include<stdlib.h>
#include<ncurses.h>

#include"helpers.h"
#include"board_logic.h"
#include"definitions.h"


int main(){
    initscr();
    noecho();
    cbreak();

    // Shift for board
    int start_y = 1;
    int start_x = 1;
    int size_y, size_x, max_size_y, max_size_x;
    getmaxyx(stdscr, max_size_y, max_size_x);

    // standard large board TODO: add other/custom bord sizes
    size_y = 16;
    size_x = 30;
    int num_mines = 99;

    int *board_ptr = calloc(size_y * size_x, sizeof(int));
    if (NULL == board_ptr) {
      printf("Memory allocation failed!");
      return 1;
    }

    init_board(board_ptr, size_y, size_x, num_mines); 
    draw_board(board_ptr, start_y, start_x, size_y, size_x);

    int ch;
    int cur_y, cur_x;

    // handling input TODO: Make interact with the actual board
    while (1){
	ch = getch();
	switch (ch){
	    case 'h':
	    cur_x = proj_interval(--cur_x, size_x, start_x);
	    break;
	    case 'j':
	    cur_y = proj_interval(++cur_y, size_y, start_y);
	    break;
	    case 'k':
	    cur_y = proj_interval(--cur_y, size_y, start_y);
	    break;
	    case 'l':
	    cur_x = proj_interval(++cur_x, size_x, start_x);
	    break;
	    case 'd':
	    board_ptr[(cur_y - start_y)*size_x + (cur_x - start_x)] ^= IS_FLAGGED;
	    draw_board(board_ptr, start_y, start_x, size_y, size_x); 
	    break;
	    case 's':
	    open_square(board_ptr, size_y, size_x, (cur_y - start_y), (cur_x - start_x));
	    draw_board(board_ptr, start_y, start_x, size_y, size_x); 
	    break;

	}
	mvprintw(start_y + size_y + 3, start_x + size_y + 3, "Current position y: %d, x: %d\n", cur_y, cur_x);
	move(cur_y, cur_x);
	refresh();
	if (ch == 'q'){
	    free(board_ptr);
	    break;
	}
    }
    
    refresh();
    endwin();

    return 0;
}
