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
            board->grid[row][col].mines = 0;
        }
    }
}

void place_mines(MinesweeperBoard *board, int mines_count, const int first_move_row, const int first_move_col) {
    if (board->width * board->height < mines_count) {
        printf("Error: mines count exceeds fields count");
        return;
    }

    for (int i = 0; i < mines_count; i++) {
        int row = rand() % board->height;
        int col = rand() % board->width;
        
        if (board->grid[row][col].hasMine == true ||
            ((row >= first_move_row - 1 && row <= first_move_row + 1) &&
            (col >= first_move_col - 1 && col <= first_move_col + 1))) {
            i--;
            continue;
        }

        board->grid[row][col].hasMine = true;
    }
}

static void init_board(MinesweeperBoard *board, Game_mode game_mode) {
    board->revealed_fields = 0;

    int mines_count = 0;
    switch (game_mode)
    {
    case EASY:
        board->width = EASY_WIDTH;
        board->height = EASY_HEIGHT;
        mines_count = (board->width * board->height * 10 + 99) / 100;
        break;
    case NORMAL:
        board->width = NORMAL_WIDTH;
        board->height = NORMAL_HEIGHT;
        mines_count = (board->width * board->height * 20 + 99) / 100;
        break;
    case HARD:
        board->width = HARD_WIDTH;
        board->height = HARD_HEIGHT;
        mines_count = (board->width * board->height * 30 + 99) / 100;
        break;
    case DEBUG:
        board->width = DEBUG_WIDTH;
        board->height = DEBUG_HEIGHT;

        clean_board(board);

        for (int row = 0; row < board->height; row++) {
            for (int col = 0; col < board->width; col++)  {
                if (row == col || row == 0 || (col == 0 && row % 2 ==0)) {
                    board->grid[row][col].hasMine = true;
                    mines_count++;
                }
            }
        }
        board->mines_count = mines_count;
        board->empty_fields = board->width * board->height - mines_count;
        return;
    }

    clean_board(board);
    board->mines_count = mines_count;
    board->empty_fields = board->width * board->height - mines_count;
}


void init_game(MinesweeperGame *game, Game_mode mode) {
    game->state = RUNNING;
    game->mode = mode;
    init_board(&(game->board), mode);
}


/*** GAME PLAY ***/

static int countMines(const MinesweeperBoard *board, const int row, const int col) {
    int x, y;
    int mines = 0;

    if (row == 0) y = 0;
    else y = row - 1;

    while (y < board->height && y <= row + 1) {
        if (col == 0) x = 0;
        else x = col - 1;
        while (x < board->width && x <= col + 1) {
            if (board->grid[y][x].hasMine) mines++;
            x++;
        }
        y++;
    }

    return mines;
}

void toggleFlag(MinesweeperGame *game, const int row, const int col) {
    if (row < 0 || row >= game->board.height || col < 0 || col >= game->board.width) return;
    game->board.grid[row][col].hasFlag = !(game->board.grid[row][col].hasFlag);
}

void revealField(MinesweeperGame* game, const int row, const int col) {
    if (row < 0 || row >= game->board.height || col < 0 || col >= game->board.width) return;
    if (game->board.grid[row][col].isRevealed || game->board.grid[row][col].hasFlag) return;
    
    game->board.grid[row][col].isRevealed = true;

    if (game->board.grid[row][col].hasMine) {
        game->state = FINISHED_LOSS;
        return;
    }

    game->board.revealed_fields++;
    game->board.grid[row][col].mines = countMines(&(game->board), row, col);

    if (game->board.grid[row][col].mines == 0) {
        int x, y;

        if (row == 0) y = 0;
        else y = row - 1;

        while (y < game->board.height && y <= row + 1) {
            if (col == 0) x = 0;
            else x = col - 1;
            while (x < game->board.width && x <= col + 1) {
                if (!(game->board.grid[y][x].isRevealed)) revealField(game, y, x);
                x++;
            }
            y++;
        }
    }
    
    if (game->board.revealed_fields == game->board.empty_fields) 
        game->state = FINISHED_WIN;

}

/*** DISPLAY ***/

// if row or col is outside board - '#'
// if the field is not revealed and has a flag - 'F'
// if the field is not revealed and does not have a flag - '_;
// if the field is revealed and has mine - 'x'
// if the field is revealed and has 0 mines around - ' '
// if the field is revealed and has some mines around - '1' ... '8'

static char getFieldInfo(const MinesweeperBoard *board, const int row, const int col) {
    if (row < 0 || row >= board->height || col < 0 || col >= board->width) return '#';

    if (!(board->grid[row][col].isRevealed)) {
        if (board->grid[row][col].hasFlag) return 'F';
        else return '_';
    }

    if (board->grid[row][col].hasMine) return 'x';
    if (board->grid[row][col].mines == 0) return ' ';

    return board->grid[row][col].mines + '0';
}


void display_board(const MinesweeperBoard *board) {
    printf("   ");
    for (int col = 0; col < board->width; col++)  {
        printf("%3d", col);
    }
    printf("\n");

    for (int row = 0; row < board->height; row++) {
        printf("%3d", row);
        for (int col = 0; col < board->width; col++)  {
            printf("[%c]", getFieldInfo(board, row, col));
        }
        printf("\n");
    }
}


