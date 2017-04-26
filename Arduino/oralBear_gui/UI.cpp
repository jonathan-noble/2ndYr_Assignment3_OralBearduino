#include "UI.h"
#include "Debug.h"

#if defined(_GFXFONT_H_)           //are we using the new library?
#include <Fonts/FreeSansBold18pt7b.h>
#define ADJ_BASELINE 11            //new fonts setCursor to bottom of letter
#else
#define ADJ_BASELINE 0             //legacy setCursor to top of letter
#endif
#include <MCUFRIEND_kbv.h>

//pins
#define YP A2   // analog
#define XM A3   // analog
#define YM 8    // digital
#define XP 9    // digital

//TouchScreen co-ordinates
#define TS_MINX 204
#define TS_MINY 195
#define TS_MAXX 948
#define TS_MAXY 910

#define MINPRESSURE 5
#define MAXPRESSURE 1000



UI::UI() {
  _content = -1;
}

void UI::init() {
  MCUFRIEND_kbv *tft = new MCUFRIEND_kbv();
  _gfx = tft;

  tft->reset();
  tft->begin(0x9341);
  tft->setRotation(1);

  _gfx->fillScreen(WHITE);
#if defined(_GFXFONT_H_)
  _gfx->setFont(&FreeSansBold18pt7b);
#endif
  _ts = new TouchScreen(XP, YP, XM, YM, 300);

}

void UI::checkBtnPressed() {
  TSPoint p = _ts->getPoint();  //p = touchPoint

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YM, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // scale from 0->1023 to _gfx->width
    p.x = map(p.x, TS_MAXX, TS_MINX, 0, _gfx->width());
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, _gfx->height());

    for (int i = TIMER_BTN; i < NUM_BTNS; i++) {
      if (_buttons[i].hit(p.x, p.y)) {
        break;
      }
    }
    delay(10); // UI debouncing
  }
}


void UI::updateContent(unsigned int newContent) {
  if (_content == newContent)  {
    return;
  }
  int hh = _gfx->height() / 2;
  int hw = _gfx->width() / 2;

  // clear former content
  _gfx->fillRect(hw - 58, hh - 22, 70, 30, BLACK);

  int offset = 0;
  if (newContent < 100) {
    offset = 20;
  }

  _gfx->setCursor(hw - 55 + offset, hh + 5);
  _gfx->print(newContent / 10.0, 1);

  _content = newContent;
}

void UI::showSplashScreen(String name, String version) {
  _gfx->fillScreen(ORANGE);

  _gfx->setCursor(30, 100);
  _gfx->setTextColor(WHITE);
  _gfx->print(name);

  _gfx->setCursor(_gfx->width() / 2 - 40, 150);
  _gfx->setTextColor(WHITE);
  _gfx->print(" v.");
  _gfx->print(version);
}

void UI::showLoadingScreen() {
  _gfx->fillScreen(DARKCYAN);

  _gfx->setCursor(_gfx->width() / 2 - 70, 70);;
  _gfx->setTextColor(WHITE);
  _gfx->print("Loading");

  //Print Loading
  _gfx->setCursor(10, 150);
  _gfx->setTextColor(WHITE);
  _gfx->print("the Timer 4 u Luv!");
}

void UI::showInstructionScreen() {
  _gfx->fillScreen(DARKGREEN);

  _gfx->setCursor(30, 70);;
  _gfx->setTextColor(WHITE);
  _gfx->print("Tip:");

  //Print Instruction on a random generated code
  int i = rand() % 6 + 1;
  if (i == 1 || i == 2 ) {
    _gfx->setCursor(30, 150);
    _gfx->setTextColor(WHITE);
    _gfx->print("Toothbrush for ");
    _gfx->setCursor(75, 220);
    _gfx->print("120-150s!");

  }
  else if (i == 3 || i == 4) {
    _gfx->setCursor(5, 150);
    _gfx->setTextColor(WHITE);
    _gfx->print("Brush teeth on circle motion!");
  }
  else if (i == 5 || i == 6) {
    _gfx->setCursor(10, 150);
    _gfx->setTextColor(WHITE);
    _gfx->print("Make sure you finish 120s!");
  }

}

//Calling back the parameters of the functions from the main
void UI::addButton(int btnId, void (*callback)()) {
  _buttons[btnId].callback = callback;
}

//Determines the visibility and activation of the button
void UI::activateButton(int btnId) {
  if (btnId == TIMER_BTN) {
    _buttons[_activeButtonId].activateButtonAndDraw(false);

    _activeButtonId = btnId;
    _buttons[_activeButtonId].activateButtonAndDraw(true);

    return;
  }

  if (btnId == PLAY_BTN) {
    for (int i = TIMER_BTN; i < NUM_BTNS; i++) {
      _buttons[i].enabled = true;
    }
    _buttons[PAUSE_BTN].enabled = _buttons[PAUSE_BTN].visible = false;
    _buttons[PLAY_BTN].visible = true;

    _buttons[PAUSE_BTN].drawButton();
    _buttons[PLAY_BTN].drawButton();
    return;
  }

  if (btnId == PAUSE_BTN) {
    for (int i = TIMER_BTN; i < NUM_BTNS; i++) {
      _buttons[i].enabled = false;
    }
    _buttons[PAUSE_BTN].enabled = _buttons[PAUSE_BTN].visible = true;
    _buttons[PLAY_BTN].visible = false;

    _buttons[PLAY_BTN].drawButton();
    _buttons[PAUSE_BTN].drawButton();
    return;
  }
}


void UI::display() {
  _gfx->fillScreen(BLACK);                 //Erase the screen
  _gfx->drawRect(0, 0, 319, 240, WHITE);   //Draw white frame

  int btnW = _gfx->width() / 3 - 8;
  int btnH = _gfx->height();

  _buttons[TIMER_BTN].x = btnW + BUTTON_X_SPACING - 15;
  _buttons[TIMER_BTN].y = 1;
  _buttons[TIMER_BTN].width = btnW + 20;
  _buttons[TIMER_BTN].height = BUTTON_HEIGHT;
  _buttons[TIMER_BTN].visible = true;
  _buttons[TIMER_BTN].active = false;
  _buttons[TIMER_BTN].enabled = true;
  _buttons[TIMER_BTN].id = TIMER_BTN;

  _buttons[PLAY_BTN].x = _buttons[TIMER_BTN].x + 10;
  _buttons[PLAY_BTN].y = btnH - BUTTON_HEIGHT - 1;
  _buttons[PLAY_BTN].width = btnW;
  _buttons[PLAY_BTN].height = BUTTON_HEIGHT;
  _buttons[PLAY_BTN].visible = true;
  _buttons[PLAY_BTN].active = false;
  _buttons[PLAY_BTN].enabled = false;
  _buttons[PLAY_BTN].id = PLAY_BTN;

  _buttons[PAUSE_BTN].x = _buttons[PLAY_BTN].x;
  _buttons[PAUSE_BTN].y = _buttons[PLAY_BTN].y;
  _buttons[PAUSE_BTN].width = btnW;
  _buttons[PAUSE_BTN].height = BUTTON_HEIGHT;
  _buttons[PAUSE_BTN].visible = false;
  _buttons[PAUSE_BTN].active = false;
  _buttons[PAUSE_BTN].enabled = false;
  _buttons[PAUSE_BTN].id = PAUSE_BTN;


  for (int i = TIMER_BTN; i < NUM_BTNS; i++) {
    _buttons[i].gfx = _gfx;
    _buttons[i].drawButton();
  }

  _gfx->drawChar(_gfx->width() / 2 + 25, _gfx->height() / 2 + 5, 's', CYAN, BLACK, 1);

}

