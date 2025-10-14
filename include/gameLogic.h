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
	PHASE_SETUPPLAYER1,
	PHASE_SETUPPAUSE,
	PHASE_SETUPPLAYER2,
	PHASE_GAMEPLAY,
	PHASE_GAMEPLAYPAUSE,
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
    CELL_NORMAL,
    CELL_HOVER,
    CELL_CLICKED,
    CELL_HIT,
    CELL_MISS,
} CellPhase;

typedef struct {
	int size;
	bool isClickable;
	CellPhase phase;
} Cell;

typedef struct {
	int ROWS;
	int COLS;
	int NUM_SHIPS;
	int OFFSET_X;
	int OFFSET_Y;
} Setup;

typedef struct {
	char name[50];
	char grid[10][10];
	char tracking[10][10];
	int ships;	
} Player;

typedef struct {
	Player player1;
	Player player2;
	Player *currentPlayer;
    Player *opponent;
	Setup setup;
	Cell cell;
} Game;

void gameStateStartGame(GameState *currentState, GamePhase *currentPhase, GameMode *currentMode, GridSize *currentGrid, Player *player, Game *game, Vector2 mouse);
void setGridDimensions(Setup *setup, Cell *cell, GridSize *currentGrid);
void initGrid(char grid[][10], Setup *setup);
void initializePlayers(Game *game, GridSize *currentGrid);
bool hasLost(Player *p, Game *game);

#endif
