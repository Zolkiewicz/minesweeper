#include <stdio.h>
#include <stdbool.h>
#include "minesweeper.h"

/*** INIT FUNCTIONS ***/

static void clean_board(MinesweeperBoard *board) {
    for (int row = 0; row < board->height; row++) {
        for (int col = 0; col < board->width; col++)  {
            board->grid[row][col].hasMine = false;
            board->grid[row][col].hasFlag = false;
            board->grid[row][col].isRevealed = false;
        }
    }
}

void init_board(MinesweeperBoard *board) {
    board->width = 5;
    board->height = 7;

    clean_board(board);

    //test val
        // Row=0, column=0- has mine, has not flag, is not revealed
        // Row=1, column=1- has not mine, has not flag, is revealed
        // Row=0, column=2- has mine, has flag, is not revealed

    board->grid[0][0].hasMine = true;

    board->grid[1][1].isRevealed = true;

    board->grid[0][2].hasMine = true;
    board->grid[0][2].hasFlag = true;
}

/*** DISPLAY ***/

void display_board(const MinesweeperBoard *board) {
    for (int row = 0; row < board->height; row++) {
        for (int col = 0; col < board->width; col++)  {
            printf("[%c%c%c]",
                board->grid[row][col].hasMine == false ? '.': 'M',
                board->grid[row][col].hasFlag == false ? '.': 'F',
                board->grid[row][col].isRevealed == false ? '.': 'R'
            );
        }
        printf("\n");
    }
}

