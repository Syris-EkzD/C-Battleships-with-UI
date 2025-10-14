#include "../include/ui.h"
#include <string.h>

// Menu screen
void drawGameStateGameMenu(GameState *currentState, Vector2 mouse) {
    Button btnStart = {{300, 200, 200, 50}, GRAY, LIGHTGRAY, "Start Game", BLACK, 20};
    Button btnInstructions = {{300, 270, 200, 50}, GRAY, LIGHTGRAY, "Instructions", BLACK, 20};
    Button btnExit = {{300, 340, 200, 50}, GRAY, LIGHTGRAY, "Exit", BLACK, 20};

	// Handle clicks
    if (UpdateButton(&btnStart, mouse)) *currentState = STATE_START_GAME;
    if (UpdateButton(&btnInstructions, mouse)) *currentState = STATE_INSTRUCTIONS;
    if (UpdateButton(&btnExit, mouse)) *currentState = STATE_EXIT;
    
    // Draw buttons
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Welcome to Battleships!", 220, 100, 30, DARKBLUE);

    DrawButton(btnStart);
    DrawButton(btnInstructions);
    DrawButton(btnExit);

    EndDrawing();
}

// Instructions screen
void drawGameStateInstructions(GameState *currentState, Vector2 mouse) {
	Button btnBack = {{10, 10, 90, 50}, GRAY, LIGHTGRAY, "<- Back", BLACK, 20};
	
	if (UpdateButton(&btnBack, mouse) || GetKeyPressed() != 0) *currentState = STATE_MENU;
	
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawButton(btnBack);
    DrawText("Welcome to Battleships!", 200, 100, 30, DARKBLUE);
    DrawText("1. Each player places their ships on their own grid.", 50, 200, 20, BLACK);
    DrawText("2. Players take turns guessing the locations of their opponent's ships.", 50, 230, 20, BLACK);
    DrawText("3. The first player to sink all opponent ships wins.", 50, 260, 20, BLACK);
    DrawText("Press any key to return to menu", 50, 290, 20, GRAY);
    EndDrawing();
}

void drawPickingGameMode(GameState *currentState, GamePhase *currentPhase, GameMode *currentMode, Vector2 mouse) {
	Button btnBack = {{10, 10, 90, 50}, GRAY, LIGHTGRAY, "<- Back", BLACK, 20};
	Button btnPVP = {{300, 200, 200, 50}, GRAY, LIGHTGRAY, "PvP", BLACK, 20};
    Button btnPVE = {{300, 270, 200, 50}, GRAY, LIGHTGRAY, "PvE", BLACK, 20};
    
    if (UpdateButton(&btnBack, mouse)) *currentState = STATE_MENU;
    if (UpdateButton(&btnPVP, mouse)) *currentPhase = PHASE_GRIDSIZE, *currentMode = MODE_PVP;
    if (UpdateButton(&btnPVE, mouse)) *currentPhase = PHASE_GRIDSIZE, *currentMode = MODE_PVE;
    
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Choose Gamemode!", 220, 100, 30, DARKBLUE);
    
    DrawButton(btnBack);
   	DrawButton(btnPVP);
   	DrawButton(btnPVE);
    EndDrawing();
}

void drawPickingGridSize(GamePhase *currentPhase, GridSize *currentGrid, Game *game, Vector2 mouse) {
	Button btnBack = {{10, 10, 90, 50}, GRAY, LIGHTGRAY, "<- Back", BLACK, 20};
	Button btn5x5 = {{300, 200, 200, 50}, GRAY, LIGHTGRAY, "5x5", BLACK, 20};
    Button btn7x7 = {{300, 270, 200, 50}, GRAY, LIGHTGRAY, "7x7", BLACK, 20};
    Button btn10x10 = {{300, 340, 200, 50}, GRAY, LIGHTGRAY, "10x10", BLACK, 20};
    
    if (UpdateButton(&btnBack, mouse)) {
		*currentPhase = PHASE_GAMEMODE;
	} else if (UpdateButton(&btn5x5, mouse)) {
		*currentPhase = PHASE_SETUPPLAYER1; 
		*currentGrid = GRID_5x5; 
		initializePlayers(game, currentGrid);
	} else if (UpdateButton(&btn7x7, mouse)) {
		*currentPhase = PHASE_SETUPPLAYER1;
		*currentGrid = GRID_7x7; 
		initializePlayers(game, currentGrid);
	} else if (UpdateButton(&btn10x10, mouse)) {
		*currentPhase = PHASE_SETUPPLAYER1;
		*currentGrid = GRID_10x10;
		initializePlayers(game, currentGrid);
	}
	
    BeginDrawing();
    ClearBackground(RAYWHITE);
	DrawText("Choose Grid Size!", 220, 100, 30, DARKBLUE);
	
	DrawButton(btnBack);
	DrawButton(btn5x5);
	DrawButton(btn7x7);
	DrawButton(btn10x10);
	EndDrawing();
}

void drawSetupGrid(GamePhase *currentPhase, Player *player, Game *game, Vector2 mouse) {
    Button btnBack = {{10, 10, 90, 50}, GRAY, LIGHTGRAY, "<- Back", BLACK, 20};
    Button btnConfirm = {{325, 480, 110, 50}, GRAY, LIGHTGRAY, "Confirm", BLACK, 20};
    
    static char temporaryGrid[10][10];
    static bool initialized = false;
    static int shipsPlaced = 0;
    
    if (UpdateButton(&btnBack, mouse)) {
        *currentPhase = PHASE_GRIDSIZE;
        initialized = false;
    }	
    
    if (UpdateButton(&btnConfirm, mouse)) {
	    memcpy(player->grid, temporaryGrid, sizeof(temporaryGrid));
	    if (player == &game->player1) {
	        *currentPhase = PHASE_SETUPPAUSE;
	    } else {
	    	game->currentPlayer = &game->player1;
			game->opponent = &game->player2;
	        *currentPhase = PHASE_GAMEPLAY;
	    }
	    initialized = false;
	}
    
    if (!initialized) {
        initGrid(temporaryGrid, &game->setup);
        initialized = true;
        shipsPlaced = 0;
    }
    
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    DrawButton(btnBack);
    DrawText(player->name, 220, 50, 30, DARKBLUE);
    DrawText(TextFormat("Ships placed: %d/%d", shipsPlaced, game->setup.NUM_SHIPS), 
             50, 550, 20, DARKGRAY);
    
    // Draw the grid
    int cellSize = game->cell.size;
    int offsetX = game->setup.OFFSET_X;
    int offsetY = game->setup.OFFSET_Y;
    
    for (int row = 0; row < game->setup.ROWS; row++) {
	    for (int col = 0; col < game->setup.COLS; col++) {
	        Rectangle cellRect = { (float)(offsetX + col * cellSize), 
								   (float)(offsetY + row * cellSize), 
								   (float)cellSize, 
								   (float)cellSize };
			
			CellPhase phase;
			if (temporaryGrid[row][col] == 'S') {
				phase = CELL_CLICKED;
			} else if (CheckCollisionPointRec(mouse, cellRect)) {
				phase = CELL_HOVER;
			} else {
				phase = CELL_NORMAL;
			}
			
	        // Click detection (toggle)
	        if (CheckCollisionPointRec(mouse, cellRect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
	            if (temporaryGrid[row][col] == 'S') {
    				temporaryGrid[row][col] = ' ';
    				shipsPlaced--;
				} else if (shipsPlaced < game->setup.NUM_SHIPS) {
    				temporaryGrid[row][col] = 'S';
    				shipsPlaced++;
				}
	        }
	        
	        if (shipsPlaced >= game->setup.NUM_SHIPS) {
	        	DrawButton(btnConfirm);
			}
	
	        Color color = (phase == CELL_NORMAL) ? LIGHTGRAY :
              (phase == CELL_HOVER) ? SKYBLUE : DARKBLUE;
	                      
	        DrawRectangleRec(cellRect, color);
	        DrawRectangleLines(cellRect.x, cellRect.y, cellRect.width, cellRect.height, BLACK);
	    }
	}
    EndDrawing();
}

void drawSetupPause(GamePhase *currentPhase, Vector2 mouse) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Player 1 has finished setting up their ships!", 150, 250, 25, DARKBLUE);
    DrawText("Pass the computer to Player 2", 150, 300, 20, GRAY);
    DrawText("Press ENTER or click to continue...", 150, 340, 20, DARKGRAY);

    EndDrawing();

    // Wait for player input to continue
    if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *currentPhase = PHASE_SETUPPLAYER2;
    }
}

void drawShootingPhase(GamePhase *currentPhase, Player *currentPlayer, Player *opponent, Game *game, Vector2 mouse) {
    Button btnConfirm = {{325, 480, 110, 50}, GRAY, LIGHTGRAY, "Confirm", BLACK, 20};

    static bool initialized = false;
    static bool shotMade = false;
    static int targetRow = -1, targetCol = -1;

    if (!initialized) {
        shotMade = false;
        targetRow = targetCol = -1;
        initialized = true;
    }

    int cellSize = game->cell.size;
    int offsetX = game->setup.OFFSET_X;
    int offsetY = game->setup.OFFSET_Y;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText(TextFormat("%s's Turn", currentPlayer->name), 250, 50, 30, DARKBLUE);
    DrawText("Click a cell to shoot", 250, 90, 20, DARKGRAY);

    // Draw current player's tracking grid
    for (int row = 0; row < game->setup.ROWS; row++) {
        for (int col = 0; col < game->setup.COLS; col++) {
            Rectangle cellRect = {
                (float)(offsetX + col * cellSize),
                (float)(offsetY + row * cellSize),
                (float)cellSize,
                (float)cellSize
            };

            Cell cell = { cellSize, true, CELL_NORMAL };
            char val = currentPlayer->tracking[row][col];

            // Determine the visual state of the cell
            if (val == 'X') {
                cell.phase = CELL_HIT;
                cell.isClickable = false;
            } else if (val == 'O') {
                cell.phase = CELL_MISS;
                cell.isClickable = false;
            } else {
                // Allow selection / re-selection before confirmation
                if (CheckCollisionPointRec(mouse, cellRect)) {
                    cell.phase = CELL_HOVER;
                    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                        // Allow reselecting another cell before confirm
                        targetRow = row;
                        targetCol = col;
                        shotMade = true;
                    }
                }

                // Highlight currently selected cell
                if (shotMade && row == targetRow && col == targetCol) {
                    cell.phase = CELL_CLICKED;
                }
            }

            // Choose color based on phase
            Color color;
            switch (cell.phase) {
                case CELL_HIT:     color = RED; break;
                case CELL_MISS:    color = DARKGRAY; break;
                case CELL_CLICKED: color = YELLOW; break;
                case CELL_HOVER:   color = SKYBLUE; break;
                default:           color = LIGHTGRAY; break;
            }

            DrawRectangleRec(cellRect, color);
            DrawRectangleLines(cellRect.x, cellRect.y, cellRect.width, cellRect.height, BLACK);

            // Draw marks
            if (cell.phase == CELL_HIT)
                DrawText("X", cellRect.x + cellSize / 3, cellRect.y + cellSize / 5, 30, BLACK);
            else if (cell.phase == CELL_MISS)
                DrawText("O", cellRect.x + cellSize / 3, cellRect.y + cellSize / 5, 30, BLACK);
        }
    }

    // Show Confirm button after a cell is selected
    if (shotMade && targetRow >= 0 && targetCol >= 0) {
        DrawButton(btnConfirm);
        if (UpdateButton(&btnConfirm, mouse)) {
            // Apply the confirmed shot
            if (opponent->grid[targetRow][targetCol] == 'S') {
                opponent->grid[targetRow][targetCol] = 'X';
                currentPlayer->tracking[targetRow][targetCol] = 'X';
            } else {
                opponent->grid[targetRow][targetCol] = 'O';
                currentPlayer->tracking[targetRow][targetCol] = 'O';
            }

            // Proceed to next phase (pause before swapping)
            *currentPhase = PHASE_GAMEPLAYPAUSE;
            initialized = false;
        }
    }

    EndDrawing();
}



