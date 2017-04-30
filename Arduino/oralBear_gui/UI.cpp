#include "UI.h"
#include "Debug.h"

#if defined(_GFXFONT_H_)           //are we using the new library?
#include <Fonts/FreeSansBold9pt7b.h>
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

//Starting number for new Content on timer
UI::UI() {
  _content = 1;
}

void UI::init() {
  MCUFRIEND_kbv *tft = new MCUFRIEND_kbv();
  _gfx = tft;

  tft->reset();
  tft->begin(0x9341);
  tft->setRotation(1);

  _gfx->fillScreen(WHITE);
#if defined(_GFXFONT_H_)
  _gfx->setFont(&FreeSansBold9pt7b);
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


    //Loop goes through every buttons possible and checks that all the buttons are hit
    for (int i = TIMER_BTN; i < NUM_BTNS; i++) {
      if (_buttons[i].hit(p.x, p.y)) {
        break;
      }
    }
    delay(10); // UI debouncing
  }
}

void UI::showSplashScreen(String name, String version) {
  _gfx->fillScreen(ORANGE);

  _gfx->fillRect(_gfx->width() / 2 - 145, _gfx->height() / 2 - 45, 290, 105, PURPLE);
  _gfx->setCursor(25, 115);
  _gfx->setTextColor(WHITE);
  _gfx->setTextSize(2);
  _gfx->print(name);

  _gfx->setCursor(_gfx->width() / 2 - 40, 165);
  _gfx->setTextColor(WHITE);
  _gfx->setTextSize(2);
  _gfx->print(" v.");
  _gfx->print(version);
}

void UI::showReminder1Screen() {
  _gfx->fillScreen(TEAL);

  _gfx->fillRect(0, 0, _gfx->width(), 50, BLUE);
  _gfx->setCursor(60, 20);
  _gfx->setTextColor(WHITE);
  _gfx->setTextSize(1.5);
  _gfx->print("BRUSH YOUR TEETH");
  _gfx->setCursor(70, 40);
  _gfx->print("FOR 120 SECONDS");

  _gfx->fillRect(0, _gfx->height() / 2 + 25, _gfx->width(), 50, BLUE);
  _gfx->setCursor(60, 165);
  _gfx->setTextColor(WHITE);
  _gfx->setTextSize(1);
  _gfx->print("So your teeth will be");
  _gfx->setCursor(57, 185);
  _gfx->print("clean and cavity free!");
}

void UI::showReminder2Screen() {
  _gfx->fillScreen(DARKGREEN);

  _gfx->fillRect(0, 60, _gfx->width(), 50, MAGENTA);
  _gfx->setCursor(60, 90);
  _gfx->setTextColor(WHITE);
  _gfx->setTextSize(1);
  _gfx->print("BRUSH TWICE A DAY");

  _gfx->fillRect(0, _gfx->height() / 2 + 15, _gfx->width(), 50, MAGENTA);
  _gfx->setCursor(57, 165);
  _gfx->setTextColor(WHITE);
  _gfx->setTextSize(1);
  _gfx->print("MORNING AND NIGHT");
}

void UI::showInstructionScreen() {
  _gfx->fillScreen(RED);

  _gfx->fillRect(_gfx->width() / 2 - 130, _gfx->height() / 2 - 60, 255, 85, DARKGREEN);
  _gfx->setCursor(30, 70);
  _gfx->setTextColor(WHITE);

  //Print Instruction on a random generated code
  int i = rand() % 6 + 1;
  if (i == 1 || i == 2 ) {
    _gfx->setCursor(_gfx->width() /2 - 125, _gfx->height() / 2 - 20);
    _gfx->setTextColor(WHITE);
    _gfx->setTextSize(2);
    _gfx->print("LET'S COUNT");
    _gfx->setCursor(_gfx->width()/2 - 113, _gfx->height() / 2 + 10);
    _gfx->print("TOGETHER!");

  }
  else if (i == 3 || i == 4) {
    _gfx->setCursor(5, 150);
    _gfx->setTextColor(WHITE);
    _gfx->print("I'LL COUNT WITH YOU!");
  }
  else if (i == 5 || i == 6) {
    _gfx->setCursor(10, 150);
    _gfx->setTextColor(WHITE);
    _gfx->print("Make sure you finish 120s!");
  }

}

//Refreshes the screen for the timer since LCD requires update per millis change
void UI::updateContent(unsigned int newContent) {
  if (_content == newContent)  {
    return;
  }

  int hh = _gfx->height() / 2;
  int hw = _gfx->width() / 2;

  // clear former content
  _gfx->fillRect(hw - 73, hh - 20, 85, 40, PURPLE);

  //ensures that when timer is on 10s+, the number will go back to its original position
  int offset = 0;
  if (newContent < 100) {
    offset = 20;
  }

  _gfx->setTextColor(CYAN);
  _gfx->setCursor(hw - 75 + offset, hh + 10);
  _gfx->setTextSize(2);
  _gfx->print(newContent / 10.0);

  _content = newContent;
}

//Calling back the parameters of the functions from the main
void UI::addButton(int btnId, void (*callback)()) {
  _buttons[btnId].callback = callback;
}

//Functionality of the buttons
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
    _buttons[PLAY_BTN].visible = true;

    _buttons[PLAY_BTN].drawButton();
    _buttons[PAUSE_BTN].drawButton();
    return;
  }
}

//All the buttons' attributes are called here
void UI::display() {
  _gfx->fillScreen(PURPLE);                //Erase the screen
  _gfx->drawRect(0, 0, 319, 240, WHITE);   //Draw white frame
  _gfx->fillRect(0, 65, _gfx->width(), 25, YELLOW);
  _gfx->fillRect(0, 157, _gfx->width(), 25, YELLOW);

  int btnW = _gfx->width() / 3 - 8;
  int btnH = _gfx->height();

  _buttons[TIMER_BTN].x = btnW + BUTTON_X_SPACING - 108;
  _buttons[TIMER_BTN].y = 10;
  _buttons[TIMER_BTN].width = btnW + 221;
  _buttons[TIMER_BTN].height = BUTTON_HEIGHT - 10;
  _buttons[TIMER_BTN].visible = true;
  _buttons[TIMER_BTN].active = false;
  _buttons[TIMER_BTN].enabled = true;
  _buttons[TIMER_BTN].id = TIMER_BTN;

  _buttons[PLAY_BTN].x = _buttons[TIMER_BTN].x + 100;
  _buttons[PLAY_BTN].y = btnH - BUTTON_HEIGHT - 1;
  _buttons[PLAY_BTN].width = btnW;
  _buttons[PLAY_BTN].height = BUTTON_HEIGHT;
  _buttons[PLAY_BTN].visible = true;
  _buttons[PLAY_BTN].active = false;
  _buttons[PLAY_BTN].enabled = true;
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

  _gfx->drawChar(_gfx->width() / 2 + 25, _gfx->height() / 2 + 10, 's', CYAN, BLACK, 2);

}

