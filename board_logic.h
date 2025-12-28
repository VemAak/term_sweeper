void init_board(int* board_ptr, int size_y, int size_x, int num_mines);
void draw_board(int* board_ptr, int start_y, int start_x, int size_y, int size_x);
void open_square(int* board_ptr, int size_y, int size_x, int y_pos, int x_pos);
void flag_square(int *board_ptr, int size_y, int size_x, int y_pos, int x_pos); 
int number_flagged(int *board_ptr, int size_y, int size_x);
int check_closed_non_mine(int *board_ptr, int size_y, int size_x);
