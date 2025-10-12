#include "../include/component.h"

// Returns true if the button was clicked
bool UpdateButton(Button *btn, Vector2 mouse) {
    bool hovered = CheckCollisionPointRec(mouse, btn->rect);
    bool clicked = hovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
    return clicked;
}

// Draws the button with hover effect
void DrawButton(Button btn) {
    bool hovered = CheckCollisionPointRec(GetMousePosition(), btn.rect);
    Color color = hovered ? btn.colorHover : btn.colorNormal;
    DrawRectangleRec(btn.rect, color);
    DrawText(btn.text, btn.rect.x + 20, btn.rect.y + 15, btn.fontSize, btn.textColor);
}
