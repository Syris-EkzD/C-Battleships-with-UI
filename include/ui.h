#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "../include/component.h"
#include "../include/gameLogic.h"

void drawGameStateGameMenu(GameState *currentState, Vector2 mouse);
void drawGameStateInstructions(GameState *currentState, Vector2 mouse);
void drawPickingGameMode(GameState *currentState, GamePhase *currentPhase, GameMode *currentMode, Vector2 mouse);
void drawPickingGridSize(GamePhase *currentPhase, GridSize *currentGrid, Game *game, Vector2 mouse);
void drawShipSetupPhase(Game *game, Player *player, GamePhase *currentPhase, Vector2 mouse);

#endif
