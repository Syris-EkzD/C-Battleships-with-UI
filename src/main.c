#include "raylib.h"
#include "../include/ui.h"
#include "../include/gameLogic.h"

int main(void) {
    InitWindow(800, 600, "Battleships Menu");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);	

    GameState currentState = STATE_MENU;
    GamePhase currentPhase = PHASE_GAMEMODE;
    GameMode currentMode = MODE_NONE;
    GridSize currentGrid = GRID_NONE;
    Game game;
    
    char player1Grid[10][10], player2Grid[10][10]; // max size
	char player1Tracking[10][10], player2Tracking[10][10];
	int player1Ships, player2Ships;

    while (!WindowShouldClose() && currentState != STATE_EXIT) {
        Vector2 mouse = GetMousePosition();
        switch(currentState) {
            case STATE_MENU:
                drawGameStateGameMenu(&currentState, mouse);
                break;
                
            case STATE_START_GAME:
                gameStateStartGame(&currentState, &currentPhase, &currentMode, &currentGrid, &game, mouse);
                break;
                
            case STATE_INSTRUCTIONS:
                drawGameStateInstructions(&currentState, mouse);
                break;
                
            case STATE_EXIT:
                CloseWindow();
                break;
        }
    }

    CloseWindow();
    return 0;
}
