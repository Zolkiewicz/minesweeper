#include <stdio.h>
#include "minesweeper.h"

int main (void) {
    MinesweeperBoard board;

    init_board(&board);
    display_board(&board);

    return 0;
}
