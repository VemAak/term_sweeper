#include<ncurses.h>
#include"definitions.h"

void define_colors(){
    //custom colors
    /*
    init_color(8, 0, 0, 556); //Dark blue
    init_color(9, 556, 0, 0); //Dark red
    init_color(10, 512, 512, 512); //Grey
    */

    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, 21, COLOR_WHITE);   // Bright blue for 1
    init_pair(3, 28, COLOR_WHITE);   // Green for 2
    init_pair(4, 196, COLOR_WHITE);  // Red for 3
    init_pair(5, 18, COLOR_WHITE);   // Dark blue for 4
    init_pair(6, 88, COLOR_WHITE);   // Maroon for 5
    init_pair(7, 51, COLOR_WHITE);   // Cyan for 6
    init_pair(8, 0, COLOR_WHITE);    // Black for 7
    init_pair(9, 240, COLOR_WHITE);  // Gray for 8

    /*
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_GREEN, COLOR_WHITE);
    init_pair(4, COLOR_RED, COLOR_WHITE);
    init_pair(5, COLOR_BLUE, COLOR_WHITE);
    init_pair(6, COLOR_YELLOW, COLOR_WHITE);
    init_pair(7, COLOR_CYAN, COLOR_WHITE);
    init_pair(8, COLOR_BLACK, COLOR_WHITE);
    init_pair(9, COLOR_BLACK, COLOR_WHITE);
    */

    init_pair(COLOR_CLOSED, COLOR_BLACK, COLOR_WHITE); // Closed square
    init_pair(COLOR_OPEN, COLOR_BLACK, COLOR_WHITE); // Open square
    init_pair(COLOR_FLAG, COLOR_MAGENTA, COLOR_WHITE); // Flagged square
    init_pair(COLOR_EXPL, COLOR_RED, COLOR_WHITE); // Exploded square
}
