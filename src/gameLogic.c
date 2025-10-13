#include "../include/gameLogic.h"


void gameStateStartGame(GameState *currentState, GamePhase *currentPhase, GameMode *currentMode, GridSize *currentGrid, Player *player, Game *game, Vector2 mouse) {
    switch(*currentPhase) {
    	case PHASE_GAMEMODE: 
    		drawPickingGameMode(currentState, currentPhase, currentMode, mouse);
    		break;
    
    	case PHASE_GRIDSIZE:
    		drawPickingGridSize(currentPhase, currentGrid, game, mouse);
    		break;
    		
    	case PHASE_SETUP: 
			drawSetupGrid(currentPhase, game->player1, game, mouse);
			break;	
	}
}

void setGridDimensions(Setup *setup, Cell *cell, GridSize *currentGrid) {
    switch (*currentGrid) {
    	case GRID_NONE:
    		setup->ROWS = 0;
            setup->COLS = 0;
            setup->NUM_SHIPS = 0;
            cell->size = 0;
            setup->OFFSET_X = 0;
            setup->OFFSET_Y = 0;
            break;
    		
        case GRID_5x5:
            setup->ROWS = 5;
            setup->COLS = 5;
            setup->NUM_SHIPS = 3;
            cell->size = 60;
            setup->OFFSET_X = 220;
            setup->OFFSET_Y = 150;
            break;
            
        case GRID_7x7:
            setup->ROWS = 7;
            setup->COLS = 7;
            setup->NUM_SHIPS = 4;
            cell->size = 50;
            setup->OFFSET_X = 180;
            setup->OFFSET_Y = 120;
            break;
            
        case GRID_10x10:
            setup->ROWS = 10;
            setup->COLS = 10;
            setup->NUM_SHIPS = 5;
            cell->size = 40;
            setup->OFFSET_X = 150;
            setup->OFFSET_Y = 100;
            break;
            
        default:
            setup->ROWS = 0;
            setup->COLS = 0;
            setup->NUM_SHIPS = 0;
            cell->size = 0;
            setup->OFFSET_X = 0;
            setup->OFFSET_Y = 0;
            break;
    }
}

void initGrid(char grid[][10], Setup *setup) {
    for (int i = 0; i < setup->ROWS; i++) {
        for (int j = 0; j < setup->COLS; j++) {
            grid[i][j] = ' ';  // Empty the cell
        }
    }
}

void initializePlayers(Game *game, GridSize *currentGrid) {
    setGridDimensions(&game->setup, &game->cell, currentGrid); // sets ROWS, COLS, NUM_SHIPS

    initGrid(game->player1.grid, &game->setup);
    initGrid(game->player2.grid, &game->setup);
    initGrid(game->player1.tracking, &game->setup);
    initGrid(game->player2.tracking, &game->setup);

    game->player1.ships = game->setup.NUM_SHIPS;
    game->player2.ships = game->setup.NUM_SHIPS;
}


