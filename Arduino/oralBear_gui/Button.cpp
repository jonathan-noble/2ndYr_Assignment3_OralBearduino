#include "Button.h"
#include"UI.h"

#define BUTTON_RADIUS 3

Button::Button() {
}

void Button::drawButton() {
  int x1, y1, w, h;
  x1 = x;   //values of x and y are passed down here
  y1 = y;
  w = width / 2;
  h = height / 2;

  //if not pressed(or visible), then just fill the buttons into black
  if (!visible) {
    gfx->fillRect(x1, y1, width - 2, height - 2, BLACK); // clear previous drawing
    return;
  }

  //draw screen frame

  //draw frame
  int frameColor = WHITE;
  if (active) {
    frameColor = GREEN;
  }

  //draw buttons
  if (id != BACK_BTN) {
    gfx->drawRoundRect(x1, y1 -60, width, height, BUTTON_RADIUS, frameColor);
  }

   if (id == BACK_BTN) {
    gfx->fillRect(15, 20, 40, 30, PURPLE);
    gfx->drawRect(15, 20, 40, 30, WHITE);
    gfx->setCursor(23, 27);
    gfx->setTextColor(BLACK);
    gfx->setTextSize(2.5);
    gfx->print("<-");
    return;
  }

  String label;
  if (id == MENU1_BTN) {
    label = "TIMER";
  }

  gfx->setTextColor(frameColor);
  gfx->setCursor(x1, y1);
  gfx->setTextSize(3);
  gfx->print(label);
  gfx->setTextColor(WHITE);

  if (!active) {
    frameColor = BLACK;
  }

  //Emphasise frame
  gfx->drawRoundRect(x1 + 1, y1 + 1, width - 2, height - 2, BUTTON_RADIUS, frameColor); //60, 180, 200, 40, WHITE);

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



