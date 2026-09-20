#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
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

static void place_mines(MinesweeperBoard *board, int mines_count) {
    if (board->width * board->height < mines_count) {
        printf("Error: mines count exceeds fields count");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < mines_count; i++) {
        int row = rand() % board->height;
        int col = rand() % board->width;
        
        if (board->grid[row][col].hasMine == true) {
            i--;
            continue;
        }

        board->grid[row][col].hasMine = true;
    }
}

void init_board(Game_mode game_mode, MinesweeperBoard *board) {
    
    int mines_count;
    switch (game_mode)
    {
    case EASY:
        board->width = EASY_WIDTH;
        board->height = EASY_HEIGHT;
        mines_count =  (board->width * board->height * 10 + 99) / 100;
        break;
    case NORMAL:
        board->width = NORMAL_WIDTH;
        board->height = NORMAL_HEIGHT;
        mines_count =  (board->width * board->height * 20 + 99) / 100;;
        break;
    case HARD:
        board->width = HARD_WIDTH;
        board->height = HARD_HEIGHT;
        mines_count =  (board->width * board->height * 30 + 99) / 100;;
        break;
    case DEBUG:
        board->width = DEBUG_WIDTH;
        board->height = DEBUG_HEIGHT;

        clean_board(board);

        for (int row = 0; row < board->height; row++) {
            for (int col = 0; col < board->width; col++)  {
                if (row == col || row == 0 || (col == 0 && row % 2 ==0))
                    board->grid[row][col].hasMine = true;
            }
        }
        return;
    }

    clean_board(board);
    place_mines(board, mines_count);
}

/*** DISPLAY ***/

void display_board(const MinesweeperBoard *board) {
    printf("     ");
    for (int col = 0; col < board->width; col++)  {
        printf(" %3d ", col);
    }
    printf("\n");

    for (int row = 0; row < board->height; row++) {
        printf(" %3d ", row);
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

