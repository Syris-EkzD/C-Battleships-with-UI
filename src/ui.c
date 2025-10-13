#include "../include/ui.h"

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
		*currentPhase = PHASE_SETUP; 
		*currentGrid = GRID_5x5; 
		initializePlayers(game);
	} else if (UpdateButton(&btn7x7, mouse)) {
		*currentPhase = PHASE_SETUP; 
		*currentGrid = GRID_7x7; 
		initializePlayers(game);
	} else if (UpdateButton(&btn10x10, mouse)) {
		*currentPhase = PHASE_SETUP;
		*currentGrid = GRID_10x10;
		initializePlayers(game);
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

void drawShipSetupPhase(Game *game, Player *player, GamePhase *currentPhase, Vector2 mouse) {
    static char tempGrid[10][10];
    static bool initialized = false;
    static bool confirmPrompt = false;	
    static int shipsPlaced = 0; // number of ships placed so far

    // Initialize temporary grid
    if (!initialized) {
        for (int i = 0; i < game->setup.ROWS; i++) {
            for (int j = 0; j < game->setup.COLS; j++) {
                tempGrid[i][j] = ' ';
            }
        }
        shipsPlaced = 0;
        initialized = true;
    }

    int cellSize = game->cell.size;
    int offsetX = game->setup.OFFSET_X;
    int offsetY = game->setup.OFFSET_Y;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    
    DrawText(
    TextFormat("%s - Place Your Ships (%d/%d)",
               (player == &game->player1) ? "Player 1" : "Player 2",
               shipsPlaced, game->setup.NUM_SHIPS),
    offsetX, offsetY - 60, 25, DARKBLUE
	);
             
    

    // --- Draw Grid ---
    for (int i = 0; i < game->setup.ROWS; i++) {
        for (int j = 0; j < game->setup.COLS; j++) {
            Rectangle cell = { offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize };
            Color color = (tempGrid[i][j] == 'S') ? DARKGRAY : LIGHTGRAY;

            DrawRectangleRec(cell, color);
            DrawRectangleLinesEx(cell, 1, BLACK);

            // Handle clicks (only if not confirming yet)
            if (!confirmPrompt && CheckCollisionPointRec(mouse, cell) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                if (tempGrid[i][j] == ' ' && shipsPlaced < game->setup.NUM_SHIPS) {
                    tempGrid[i][j] = 'S';
                    shipsPlaced++;
                } 
                else if (tempGrid[i][j] == 'S') {
                    tempGrid[i][j] = ' ';
                    shipsPlaced--;
                }
            }
        }
    }

    // --- Show confirm button only when all ships are placed ---
    if (shipsPlaced == game->setup.NUM_SHIPS) {
        Rectangle confirmBtn = { offsetX, offsetY + game->setup.ROWS * cellSize + 40, 120, 40 };
        DrawRectangleRec(confirmBtn, GRAY);
        DrawText("Confirm", confirmBtn.x + 20, confirmBtn.y + 10, 20, BLACK);

        if (CheckCollisionPointRec(mouse, confirmBtn) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            confirmPrompt = true;
        }
    }

    // --- Confirm prompt logic ---
    if (confirmPrompt) {
        DrawRectangle(offsetX + 150, offsetY + 100, 300, 150, Fade(GRAY, 0.9f));
        DrawText("Confirm placement?", offsetX + 170, offsetY + 120, 25, BLACK);

        Rectangle yesBtn = { offsetX + 170, offsetY + 170, 100, 40 };
        Rectangle noBtn = { offsetX + 300, offsetY + 170, 100, 40 };

        DrawRectangleRec(yesBtn, GREEN);
        DrawRectangleRec(noBtn, RED);
        DrawText("YES", yesBtn.x + 25, yesBtn.y + 10, 20, BLACK);
        DrawText("NO", noBtn.x + 30, noBtn.y + 10, 20, BLACK);

        // YES = commit placements
        if (CheckCollisionPointRec(mouse, yesBtn) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < game->setup.ROWS; i++) {
                for (int j = 0; j < game->setup.COLS; j++) {
                    player->grid[i][j] = tempGrid[i][j];
                }
            }

            confirmPrompt = false;
            initialized = false;
            *currentPhase = PHASE_GAMEPLAY;
        }
        // NO = cancel confirmation
        else if (CheckCollisionPointRec(mouse, noBtn) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            confirmPrompt = false;
        }
    }

    EndDrawing();
}

