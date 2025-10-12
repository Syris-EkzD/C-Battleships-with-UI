#include "raylib.h"
#include "../include/ui.h"
#include "../include/gameLogic.h"

int main(void) {
    InitWindow(800, 600, "Battleships Menu");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    GameState currentState = STATE_MENU;

    while (!WindowShouldClose() && currentState != STATE_EXIT) {
        Vector2 mouse = GetMousePosition();
        switch(currentState) {
            case STATE_MENU:
                drawGameStateGameMenu(&currentState, mouse);
                break;
            case STATE_START_GAME:
                drawGameStateStartGame(&currentState, mouse);
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
