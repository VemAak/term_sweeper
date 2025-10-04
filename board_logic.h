void init_board(int* board_ptr, int size_y, int size_x);
void populate_mines(int* board_ptr, int num_mines,int size_y, int size_x);
void draw_board(int* board_ptr, int start_y, int start_x, int size_y, int size_x);
void open_square(int* board_ptr, int size_y, int size_x, int y_pos, int x_pos);
