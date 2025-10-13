#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include "raylib.h"

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

typedef enum {
    TURN_PLAYER1,
    TURN_PLAYER2
} PlayerSetupTurn;

typedef enum {
    CELL_NORMAL,
    CELL_HOVER,
    CELL_CLICKED
} CellPhase;

typedef struct {
	int size;
	bool isClickable;
	CellPhase phase;
} Cell;

typedef struct {
	GridSize currentGrid;
	int ROWS;
	int COLS;
	int NUM_SHIPS;
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
	Cell cell;
} Game;

void gameStateStartGame(GameState *currentState, GamePhase *currentPhase, GameMode *currentMode, GridSize *currentGrid, Game *game, Vector2 mouse);
void setGridDimensions(Setup *setup, Cell *cell);
void initGrid(char grid[][10], Setup *setup);
void initializePlayers(Game *game);

#endif
