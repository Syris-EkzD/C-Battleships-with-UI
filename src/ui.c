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

// Game screen
void drawGameStateStartGame(GameState *currentState, Vector2 mouse) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("GAME SCREEN", 300, 250, 30, DARKGREEN);
    DrawText("Press ESC to go back", 280, 300, 20, GRAY);
    EndDrawing();

    if (IsKeyPressed(KEY_ESCAPE)) *currentState = STATE_MENU;
}

// Instructions screen
void drawGameStateInstructions(GameState *currentState, Vector2 mouse) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Welcome to Battleships!", 200, 100, 30, DARKBLUE);
    DrawText("1. Each player places their ships on their own grid.", 50, 200, 20, BLACK);
    DrawText("2. Players take turns guessing the locations of their opponent's ships.", 50, 230, 20, BLACK);
    DrawText("3. The first player to sink all opponent ships wins.", 50, 260, 20, BLACK);
    DrawText("Press any key to return to menu", 50, 290, 20, GRAY);
    EndDrawing();

    if (GetKeyPressed() != 0) *currentState = STATE_MENU;
}
