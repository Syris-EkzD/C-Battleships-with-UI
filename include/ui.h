#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "../include/component.h"
#include "gameLogic.h"

void drawGameStateGameMenu(GameState *currentState, Vector2 mouse);
void drawGameStateStartGame(GameState *currentState, Vector2 mouse);
void drawGameStateInstructions(GameState *currentState, Vector2 mouse);

#endif
