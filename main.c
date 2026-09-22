#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "minesweeper.h"

void instructions(void);
void first_move(MinesweeperGame *game);

int main (void) {
    srand(time(NULL));

    char type;
    int row;
    int col;
    MinesweeperGame game;

    init_game(&game, EASY);
    instructions();

    if (game.mode != DEBUG) first_move(&game);

    while (game.state == RUNNING) {
        display_board(&(game.board));
        scanf(" %c %d %d", &type, &row, &col);
        if (type == 'F' || type == 'f') toggleFlag(&game, row, col);
        if (type == 'R' || type == 'r') revealField(&game, row, col);
    }

    display_board(&(game.board));

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

void first_move(MinesweeperGame *game) {
    char type;
    int row;
    int col;
    display_board(&(game->board));
    
    while (scanf(" %c %d %d", &type, &row, &col) != 3 ||
           row < 0 || row >= game->board.height || 
           col < 0 || col >= game->board.width) {
        
        while (getchar() != '\n');
        printf("Invalid input or move out of bounds! Try again (e.g. R 2 3): ");
    }

    place_mines(&game->board, game->board.mines_count, row, col);

    if (type == 'F' || type == 'f') {
        toggleFlag(game, row, col);
    } else if (type == 'R' || type == 'r') {
        revealField(game, row, col);
    }
}


void instructions(void) {
    printf("\nBOARD LEGEND:\n");
    printf("  [_] - Unrevealed empty field\n");
    printf("  [1] - Revealed field showing neighboring mine count (1-8)\n");
    printf("  [F] - Flagged field (marked as suspected mine)\n");
    printf("  [x] - Mine (revealed upon game over)\n\n");

    printf("COMMANDS / CONTROLS:\n");
    printf("  R row col   -> Reveal field at (row, col)\n");
    printf("  F row col   -> Toggle Flag at (row, col)\n");
    printf("  I           -> Show instructions\n\n");
}