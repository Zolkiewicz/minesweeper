#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "minesweeper.h"

int main (void) {
    srand(time(NULL));

    MinesweeperBoard board;

    init_board(EASY, &board);
    display_board(&board);

    return 0;
}
