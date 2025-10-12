#include "raylib.h"

typedef enum {
    STATE_MENU,
    STATE_START_GAME,
    STATE_INSTRUCTIONS,
    STATE_EXIT
} GameState;

void drawGameStateGameMenu(GameState *currentState, Vector2 mouse);
void drawGameStateStartGame(GameState *currentState, Vector2 mouse);
void drawGameStateInstructions(GameState *currentState, Vector2 mouse);


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
}

void drawGameStateGameMenu(GameState *currentState, Vector2 mouse) {
	Rectangle btnStart = {300, 200, 200, 50};
    Rectangle btnInstructions = {300, 270, 200, 50};
    Rectangle btnExit = {300, 340, 200, 50};

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mouse, btnStart)) {
            *currentState = STATE_START_GAME;
        }
        else if (CheckCollisionPointRec(mouse, btnInstructions)) {
            *currentState = STATE_INSTRUCTIONS;
        }
        else if (CheckCollisionPointRec(mouse, btnExit)) {
            *currentState = STATE_EXIT;
        }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Welcome to Battleships!", 220, 100, 30, DARKBLUE);

    DrawRectangleRec(btnStart, CheckCollisionPointRec(mouse, btnStart) ? LIGHTGRAY : GRAY);
    DrawRectangleRec(btnInstructions, CheckCollisionPointRec(mouse, btnInstructions) ? LIGHTGRAY : GRAY);
    DrawRectangleRec(btnExit, CheckCollisionPointRec(mouse, btnExit) ? LIGHTGRAY : GRAY);

    DrawText("Start Game", 340, 215, 20, BLACK);
    DrawText("Instructions", 335, 285, 20, BLACK);
    DrawText("Exit", 380, 355, 20, BLACK);

    EndDrawing();
}

void drawGameStateStartGame(GameState *currentState, Vector2 mouse) {
	BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("GAME SCREEN", 300, 250, 30, DARKGREEN);
    DrawText("Press ESC to go back", 280, 300, 20, GRAY);
    EndDrawing();

    if (IsKeyPressed(KEY_ESCAPE)) {
        *currentState = STATE_MENU;
    }
}

void drawGameStateInstructions(GameState *currentState, Vector2 mouse) {
	BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Welcome to Battleships!", 200, 100, 30, DARKBLUE);
    DrawText("1. Each player places their ships on their own grid.", 50, 200, 20, BLACK);
    DrawText("2. Players take turns guessing the locations of their opponent's ships.", 50, 230, 20, BLACK);
    DrawText("3. The first player to sink all opponent ships wins.", 50, 260, 20, BLACK);
    DrawText("Press any key to return to menu", 50, 290, 20, GRAY);
    EndDrawing();

    if (GetKeyPressed() != 0) {
        *currentState = STATE_MENU;
    }
}