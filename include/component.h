#ifndef COMPONENT_H
#define COMPONENT_H

#include "raylib.h"
#include <stdbool.h>

// Button struct
typedef struct {
    Rectangle rect;
    Color colorNormal;
    Color colorHover;
    const char *text;
    Color textColor;
    int fontSize;
} Button;

// Button functions
bool UpdateButton(Button *btn, Vector2 mouse); // returns true if clicked
void DrawButton(Button btn);

#endif
