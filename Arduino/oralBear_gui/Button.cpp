#include "Button.h"
#include"UI.h"

#define BUTTON_RADIUS 3

Button::Button() {
}

void Button::drawButton() {
  int x1, y1, w, h, hw, hh;
  x1 = x;
  y1 = y;
  w = width;
  h = height;
  hw = w / 2;
  hh = h / 2;

  if (!visible) {
    gfx->fillRect(x1 + 1, y1 + 1, w - 2, h - 2, BLACK); // clear previous drawing
    return;
  }

  // draw frame
  int frameColor = CYAN;
  if (active) {
    frameColor = GREEN;
  }
  //draw buttons
  if (id == TIMER_BTN || PAUSE_BTN || PLAY_BTN) {
    gfx->drawRoundRect(x1, y1, w, h, BUTTON_RADIUS, frameColor);
    gfx->fillRoundRect(x1, y1, w, h, BUTTON_RADIUS, WHITE);
  }

  if (id == PAUSE_BTN) {
    gfx->fillRect(x1 + hw - 12, y1 + 7, 10, h - 16, YELLOW);
    gfx->fillRect(x1 + hw + 2, y1 + 7, 10, h - 16, YELLOW);
    return;
  }
  else if (id == PLAY_BTN) {
    gfx->fillTriangle(x1 + 30, y1 + 7, x1 + 30, y1 + h - 7, x1 + w - 30, y1 + hh, GREEN);
    return;
  }

  //The string inside the timer button
  String label;
  if (id == TIMER_BTN) {
    label = "TIMER";
  }

  gfx->setTextColor(BLACK);
  gfx->setTextSize(1);
  gfx->setCursor(x1 + 2, y1 + 35);
  gfx->print(label);

  //Color for the timer
  gfx->setTextColor(CYAN);

  if (!active) {
    frameColor = BLACK;
  }

  //Emphasise frame
  gfx->drawRoundRect(x1 + 1, y1 + 1, w - 2, h - 2, BUTTON_RADIUS, frameColor);
  gfx->drawRoundRect(x1 + 2, y1 + 2, w - 4, h - 4, BUTTON_RADIUS, frameColor);

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

//error-check to test if buttons are hit inside the touchPoint
bool Button::hit(uint16_t xpos, uint16_t ypos) {
  bool hitTest = visible && enabled &&
                 (xpos > x) && (xpos < (x + width)) &&
                 (ypos > y) && (ypos < (y + height));
  if (hitTest) {
    animateButtonClick();
    callback();
  }

  return hitTest;
}

//show buttons if visible is true THEN if not visible, call the code from drawButton
void Button::showButtonAndDraw(bool isVisible) {
  visible = isVisible;
  drawButton();
}

// when buttons pressed and activated, call function draw
void Button::activateButtonAndDraw(bool activate) {
  active = activate;
  drawButton();
}



