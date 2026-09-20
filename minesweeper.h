#ifndef MINESWEEPER
#define MINESWEEPER

#include <stdbool.h>

#define MAX_WIDTH 100
#define MAX_HEIGHT 100

typedef struct {
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
} Field;

typedef struct {
    int width;
    int height;
    Field grid[MAX_HEIGHT][MAX_WIDTH];
} MinesweeperBoard;

void init_board(MinesweeperBoard *board);

void display_board(const MinesweeperBoard *board);


#endif