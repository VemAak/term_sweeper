#include<stdlib.h>
#include<ncurses.h>

#include"helpers.h"

void draw_box(int start_y, int start_x, int size_y, int size_x) {
    for (int i = start_y; i <= size_y; i++) {
	for (int j = start_x; j <= size_x; j++){
	    mvaddch(i, j, ACS_BLOCK);
	}
    }
}

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

    int *board_ptr = calloc(size_y * size_x, sizeof(int));
    if (NULL == board_ptr) {
      printf("Memory allocation failed!");
      return 1;
    }

    int ch;
    int cur_y, cur_x;

    // handling input TODO: Make interact with the actual board
    while (1){
	ch = getch();
	switch (ch){
	    case 'h':
	    cur_x = proj_interval(--cur_x, size_x, 0);
	    break;
	    case 'j':
	    cur_y = proj_interval(++cur_y, size_y, 0);
	    break;
	    case 'k':
	    cur_y = proj_interval(--cur_y, size_y, 0);
	    break;
	    case 'l':
	    cur_x = proj_interval(++cur_x, size_x, 0);
	    break;
	    case 'a':
	    mvaddch(cur_y, cur_x, ACS_UARROW);
	    break;
	}
	mvprintw(start_y + size_y, start_x + size_y, "Current position y: %d, x: %d\n", cur_y, cur_x);
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
