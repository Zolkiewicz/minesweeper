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
    int mines;
} Field;

typedef struct {
    int width;
    int height;
    int empty_fields;
    int revealed_fields;
    Field grid[MAX_HEIGHT][MAX_WIDTH];
} MinesweeperBoard;

typedef enum {
    EASY,
    NORMAL,
    HARD,
    DEBUG
} Game_mode;

typedef enum {
    RUNNING,
    FINISHED_WIN,
    FINISHED_LOSS
} Game_state;

typedef struct {
    Game_mode mode;
    Game_state state;
    MinesweeperBoard board;
} MinesweeperGame;

void init_game(MinesweeperGame *game, Game_mode mode);

void display_board(const MinesweeperBoard *board);

void toggleFlag(MinesweeperGame *game, const int row, const int col);
void revealField(MinesweeperGame* game, const int row, const int col);

#endif