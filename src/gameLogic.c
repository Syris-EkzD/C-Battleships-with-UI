#include "../include/gameLogic.h"


void gameStateStartGame(GameState *currentState, GamePhase *currentPhase, GameMode *currentMode, GridSize *currentGrid, Player *player, Game *game, Vector2 mouse) {
    switch(*currentPhase) {
        case PHASE_GAMEMODE: 
            drawPickingGameMode(currentState, currentPhase, currentMode, mouse);
            break;
    
        case PHASE_GRIDSIZE:
            drawPickingGridSize(currentPhase, currentGrid, game, mouse);
            break;
            
        case PHASE_SETUPPLAYER1: 
            drawSetupGrid(currentPhase, &game->player1, game, mouse);
            break;  
            
        case PHASE_SETUPPAUSE:
            drawSetupPause(currentPhase, mouse);
            break;
            
        case PHASE_SETUPPLAYER2:
            drawSetupGrid(currentPhase, &game->player2, game, mouse);
            break;
            
        case PHASE_GAMEPLAY:
            drawShootingPhase(currentPhase, game->currentPlayer, game->opponent, game, mouse);
            break;
            
        case PHASE_GAMEPLAYPAUSE: {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText(TextFormat("%s's Turn Ended!", game->currentPlayer->name), 200, 250, 25, DARKBLUE);
            DrawText("Press ENTER to continue...", 200, 300, 20, GRAY);

            EndDrawing();

            if (IsKeyPressed(KEY_ENTER)) {
                // Check if opponent lost
                if (hasLost(game->opponent, game)) {
                    *currentPhase = PHASE_GAMEOVER;
                } else {
                    // Swap turns
                    Player *temp = game->currentPlayer;
                    game->currentPlayer = game->opponent;
                    game->opponent = temp;

                    *currentPhase = PHASE_GAMEPLAY;
                }
            }
            break;
        }

        case PHASE_GAMEOVER:
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(TextFormat("Game Over! Winner: %s", game->currentPlayer->name), 200, 250, 30, RED);
            EndDrawing();
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

bool hasLost(Player *p, Game *game) {
    for (int row = 0; row < game->setup.ROWS; row++) {
        for (int col = 0; col < game->setup.COLS; col++) {
            if (p->grid[row][col] == 'S')
                return false; // Still has a ship
        }
    }
    return true; // All ships destroyed
}


