#ifndef GAMELOGIC_H
#define GAMELOGIC_H

typedef enum {
    STATE_MENU,
    STATE_START_GAME,
    STATE_INSTRUCTIONS,
    STATE_EXIT
} GameState;

typedef enum {
	PHASE_GAMEMODE,
	PHASE_GRIDSIZE,
	PHASE_SETUP,
	PHASE_GAMEPLAY,
	PHASE_GAMEOVER,
} GamePhase;

typedef enum {
	MODE_NONE,
	MODE_PVP,
	MODE_PVE,
} GameMode;

typedef enum {
	GRID_NONE,
	GRID_5x5,
	GRID_7x7,
	GRID_10x10,
} GridSize;

typedef struct {
	GridSize currentGrid;
	int ROWS;
	int COLS;
	int NUM_SHIPS;
	int CELL_SIZE;
	int OFFSET_X;
	int OFFSET_Y;
} Setup;

typedef struct {
	char grid[10][10];
	char tracking[10][10];
	int ships;	
} Player;

typedef struct {
	Player player1;
	Player player2;
	Setup setup;
} Game;

void setGridDimensions(Setup *setup);
void initGrid(char grid[][10], Setup *setup);
void initializePlayers(Game *game);

#endif
