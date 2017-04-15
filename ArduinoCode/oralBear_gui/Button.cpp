#include "Button.h"
#include"UI.h"

#define BUTTON_RADIUS 3

Button::Button() {
}

void Button::drawButton() {
  int x1, y1, w, h;
  x1 = x;
  y1 = y;
  w = width / 2;
  h = height / 2;

  if (!visible) {
    gfx->fillRect(x1 + 1, y1 + 1, w - 2, h - 2, BLACK); // clear previous drawing
    return;
  }

  //draw screen frame

  //draw frame
  int frameColor = WHITE;


}

void Button::animateButtonClick() {
  if (!visible) {
    return;
  }

  int x1, y1, w, h;
  // preserve button frame
  x1 = x + 1;
  y1 = y + 1;
  w = width - 2;
  h = height - 2;

  gfx->fillRect(x1, y1, w, h, LIGHTGREY);
  delay(150);
  gfx->fillRect(x1, y1, w, h, BLACK);
  drawButton();
}

bool Button::hit(uint16_t xpos, uint16_t ypos) {
  bool hitTest = visible && enabled && (xpos > x) && (xpos < (x + width)) && (ypos > y) && (ypos < (y + height));
  if (hitTest) {
    animateButtonClick();
    callback();
  }

  return hitTest;
}

