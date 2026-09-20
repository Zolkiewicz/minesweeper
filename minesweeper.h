#ifndef MINESWEEPER
#define MINESWEEPER

#include <stdbool.h>

#define MAX_WIDTH 100
#define MAX_HEIGHT 100

#define EASY_WIDTH 5
#define EASY_HEIGHT 7

#define NORMAL_WIDTH 10 
#define NORMAL_HEIGHT 12

#define HARD_WIDTH 15 
#define HARD_HEIGHT 20

#define DEBUG_WIDTH 10
#define DEBUG_HEIGHT 10

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

typedef enum {
    EASY,
    NORMAL,
    HARD,
    DEBUG
} Game_mode;

void init_board(Game_mode game_mode, MinesweeperBoard *board);

void display_board(const MinesweeperBoard *board);


#endif