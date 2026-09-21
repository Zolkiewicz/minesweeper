#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "minesweeper.h"

int main (void) {
    srand(time(NULL));

    MinesweeperGame game;

    init_game(&game, DEBUG);

    char type;
    int row;
    int col;

    while (game.state == RUNNING) {
        display_board(&(game.board));
        scanf(" %c %d %d", &type, &row, &col);
        if (type == 'F') toggleFlag(&game, row, col);
        if (type == 'R') revealField(&game, row, col);
    }

    if (game.state == FINISHED_WIN) {
        printf("\n=============================\n");
        printf("            VICTORY          \n");
        printf("=============================\n");
    } else if (game.state == FINISHED_LOSS) {
        printf("\n=============================\n");
        printf("          GAME OVER          \n");
        printf("=============================\n");
    }
        
    return 0;
}
