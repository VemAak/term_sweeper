#include<stdlib.h>
#include<string.h>
#include<ncurses.h>

#include"helpers.h"
#include"board_logic.h"
#include"color.h"
#include"definitions.h"


int main(int argc, char* argv[]){
    // Shift for board
    int start_y = 1;
    int start_x = 1;
    int size_y, size_x, max_size_y, max_size_x;
    int num_mines;

    if (1 == argc) {
	size_y = 16;
	size_x = 30;
	num_mines = 60;
    }
    else if (4 == argc) {
	size_y = atoi(argv[1]);
	size_x = atoi(argv[2]);
	num_mines = atoi(argv[3]);
	if (size_y < 1 || size_x < 1 ||  num_mines < 1) {
	    printf("Arguments cannot be negative!\n");
	    return 1;
	    }
	else if (num_mines > size_y*size_x) {
	    printf("Number of mines greater than available squares!\n");
	    return 1;
	}
    }
    else {
	printf("Incorrect selection of arguments. Correct is num_y, num_x, num_mines or no arguments\n");
	return 1;
    }

    initscr();
    noecho();
    cbreak();
    getmaxyx(stdscr, max_size_y, max_size_x);
    if (size_x > max_size_x - 2 || size_y > max_size_y - 2) {
	endwin();
	printf("Board greater than size of terminal!\n");
	return 1;
    }

    start_color();
    if (!has_colors()) {
	endwin();
	printf("Your terminal does not support color!\n");
	return 1;
    }
    else {
	define_colors();
    }


    int *board_ptr = calloc(size_y * size_x, sizeof(int));
    if (NULL == board_ptr) {
      printf("Memory allocation failed!\n");
      return 1;
    }

    init_board(board_ptr, size_y, size_x, num_mines); 
    draw_board(board_ptr, start_y, start_x, size_y, size_x);

    int ch;
    int cur_y, cur_x;

    while (1){
	ch = getch();
	switch (ch){
	    case 'R':
	    memset(board_ptr, 0, size_y * size_x * sizeof(int));
	    init_board(board_ptr, size_y, size_x, num_mines); 
	    draw_board(board_ptr, start_y, start_x, size_y, size_x);
	    break;
	    case 'H':
	    cur_x = proj_interval(cur_x - 5, size_x, start_x);
	    break;
	    case 'J':
	    cur_y = proj_interval(cur_y + 5, size_y, start_y);
	    break;
	    case 'K':
	    cur_y = proj_interval(cur_y - 5, size_y, start_y);
	    break;
	    case 'L':
	    cur_x = proj_interval(cur_x + 5, size_x, start_x);
	    break;
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
	    flag_square(board_ptr, size_y, size_x, (cur_y - start_y), (cur_x - start_x));
	    draw_board(board_ptr, start_y, start_x, size_y, size_x); 
	    break;
	    case 's':
	    open_square(board_ptr, size_y, size_x, (cur_y - start_y), (cur_x - start_x));
	    draw_board(board_ptr, start_y, start_x, size_y, size_x); 
	    break;

	}
	mvprintw(start_y + size_y + 3, start_x + size_y + 3, "Current position y: %d, x: %d\n", cur_y, cur_x);
	mvprintw(0, 0, "Remaining mines: %d\n", (num_mines - number_flagged(board_ptr, size_y, size_x)));
	if (check_closed_non_mine(board_ptr, size_y, size_x) == 0) {
	   mvprintw(size_y + 1, 0, "YOU WON!"); 
	}
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
