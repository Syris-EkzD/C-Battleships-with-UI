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
    Cell cell;
    Setup setup;
    Game game;
    
	game.player1 = (Player){ "Player 1", {{' '}}, {{' '}}, 0 };
	game.player2 = (Player){ "Player 2", {{' '}}, {{' '}}, 0 };
    
    while (!WindowShouldClose() && currentState != STATE_EXIT) {
        Vector2 mouse = GetMousePosition();
        switch(currentState) {
            case STATE_MENU:
                drawGameStateGameMenu(&currentState, mouse);
                break;
                
            case STATE_START_GAME:
                gameStateStartGame(&currentState, &currentPhase, &currentMode, &currentGrid, &game.player1, &game, mouse);
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
