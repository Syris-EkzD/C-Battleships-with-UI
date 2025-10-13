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
		initializePlayers(game, currentGrid);
	} else if (UpdateButton(&btn7x7, mouse)) {
		*currentPhase = PHASE_SETUP; 
		*currentGrid = GRID_7x7; 
		initializePlayers(game, currentGrid);
	} else if (UpdateButton(&btn10x10, mouse)) {
		*currentPhase = PHASE_SETUP;
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
    
    if(UpdateButton(&btnBack, mouse)) {
        *currentPhase = PHASE_GRIDSIZE;
    }	
    
    static char temporaryGrid[10][10];
    static bool initialized = false;
    
    if (!initialized) {
        initGrid(temporaryGrid, &game->setup);
        initialized = true;
    }
    
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    DrawText(player->name, 220, 50, 30, DARKBLUE);
    DrawButton(btnBack);
    
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
				} else {
    				temporaryGrid[row][col] = 'S';
				}
	        }
	
	       
	        Color color = (phase == CELL_NORMAL) ? LIGHTGRAY :
              (phase == CELL_HOVER) ? SKYBLUE : DARKBLUE;
	                      
	        DrawRectangleRec(cellRect, color);
	        DrawRectangleLines(cellRect.x, cellRect.y, cellRect.width, cellRect.height, BLACK);
	    }
	}
    EndDrawing();
}




