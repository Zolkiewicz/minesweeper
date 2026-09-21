#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "minesweeper.h"

int main (void) {
    srand(time(NULL));

    MinesweeperGame game;

    init_game(&game, DEBUG);
    display_board(&(game.board));

    revealField(&game, 2, 2);
    revealField(&game, 7, 3);
    toggleFlag(&game, 0, 3);

    display_board(&(game.board));
    
    return 0;
}
