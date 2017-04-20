#include "UI.h"

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


//int currentScreen = WELCOME_BTN;

UI::UI() {
  _content = -1;
}

void UI::init() {
  MCUFRIEND_kbv *tft = new MCUFRIEND_kbv();
  _gfx = tft;

  tft->reset();
  tft->begin(0x9341);
  tft->setRotation(1);
  _ts = new TouchScreen(XP, YP, XM, YM, 300);

  _gfx->fillScreen(BLACK);
  //  welcomeScreen();
  //  currentScreen = WELCOME_BTN;

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

    //Welcome Screen
    //    if (currentScreen == WELCOME_BTN) {
    //      if (p.x > 60 && p.x < 260 && p.y > 180 && p.y < 220) // The user has pressed inside the red rectangle
    //      {
    //        currentScreen = MENU1_BTN;
    //        menuScreen();
    //      }
    //    }
    //
    //    //Start Menu Screen
    //    if (currentScreen == MENU1_BTN) {
    //      //Back Button
    //      if (p.x > 15 && p.x < 55 && p.y > 20 && p.y < 70)
    //      {
    //        currentScreen = WELCOME_BTN;
    //        welcomeScreen();
    //      }
    //      //Timer Button
    //      if (p.x > 80 && p.x < 235 && p.y > 20 && p.y < 70)
    //      {
    //        currentScreen = TIMER_BTN;
    //        timerScreen();
    //      }
    //    }
    //
    //    //Timer Screen
    //    if (currentScreen == TIMER_BTN) {
    //      //Back Button
    //      if (p.x > 15 && p.x < 55 && p.y > 20 && p.y < 70)
    //      {
    //        currentScreen = MENU1_BTN;
    //        menuScreen();
    //      }
    //    }

    // checking every buttons if they are pressed within the touchpoints
    for (int i = MENU1_BTN; i < NUM_BTNS; i++) {
      if (_buttons[i].hit(p.x, p.y)) {
        break;
      }
    }

    delay(10); // UI debouncing

  }
}

void UI::updateContent(unsigned int newContent) {
  if (_content == newContent) {
    return;

    int hh = _gfx->height() / 2;
    int hw = _gfx->width() / 2;

    // clear former content
    _gfx->fillRect(hw - 46, hh - 22, 73, 30, BLACK);

    int offset = 0;
    if (newContent < 100) {
      offset = 20;
    }

    _gfx->setCursor(hw - 48 + offset, hh + 5);
    _gfx->print(newContent / 10.0, 1);

    _content = newContent;
  }
}

void UI::showSplashScreen() {//String name) {
  //_gfx->setCursor(_gfx->width() / 2 - 60, 100);
  //_gfx->print(name);

  //Print "Hello" Text
  _gfx->setCursor(100, 30);
  _gfx->setTextColor(WHITE);
  _gfx->setTextSize(4);
  _gfx->print("Hello");

  //Print "Master!" text
  _gfx->setCursor(80, 100);
  _gfx->setTextColor(RED);
  _gfx->setTextSize(4);
  _gfx->print("Master!");
}

//Calling back the parameters of the functions from the main
void UI::addButton(int btnId, void (*callback)()) {
  _buttons[btnId].callback = callback;
}

//Determines the visibility and activation of the button
void UI::activateButton(int btnId) {
  
  if (btnId == MENU1_BTN) {
    //every buttons that are not the btnId will not activate
    _buttons[_activeButtonId].activateButtonAndDraw(false);

    _activeButtonId = btnId;
    _buttons[_activeButtonId].activateButtonAndDraw(true);

    _buttons[TIMER1_BTN].enabled = _buttons[TIMER1_BTN].visible = false;
    _buttons[BACK_BTN].enabled = _buttons[BACK_BTN].visible = false;

    _buttons[MENU1_BTN].showButtonAndDraw(false);
    _buttons[TIMER1_BTN].showButtonAndDraw(true);
    _buttons[BACK_BTN].showButtonAndDraw(true);
    return;
  }

  if (btnId == TIMER1_BTN) {
    //every buttons that are not the btnId will not activate
    _buttons[_activeButtonId].activateButtonAndDraw(false);

    _activeButtonId = btnId;
    _buttons[_activeButtonId].activateButtonAndDraw(true);
    _buttons[MENU1_BTN].enabled = _buttons[MENU1_BTN].visible = false;

    _buttons[MENU1_BTN].showButtonAndDraw(false);
    return;
  }

  if (btnId == BACK_BTN) {
    //every buttons that are not the btnId will not activate
    _buttons[_activeButtonId].activateButtonAndDraw(false);

    _activeButtonId = TIMER1_BTN;
    _buttons[_activeButtonId].activateButtonAndDraw(true);
    _buttons[MENU1_BTN].enabled = _buttons[MENU1_BTN].visible = true;
    _buttons[TIMER1_BTN].enabled = _buttons[MENU1_BTN].visible = true;

    _buttons[MENU1_BTN].showButtonAndDraw(true);
    _buttons[TIMER1_BTN].showButtonAndDraw(false);
    return;
  }


}

void UI::display() {
  _gfx->fillScreen(BLACK);                 //Erase the screen
  _gfx->drawRect(0, 0, 319, 240, WHITE);   //Draw white frame

  int btnW = _gfx->width() / 3 - 8;
  int btnH = _gfx->height() /2;



  _buttons[MENU1_BTN].x = btnW + BUTTON_X_SPACING;
  _buttons[MENU1_BTN].y = 30;
  _buttons[MENU1_BTN].width = btnW;
  _buttons[MENU1_BTN].height = BUTTON_HEIGHT;
  _buttons[MENU1_BTN].visible = true;
  _buttons[MENU1_BTN].active = false;
  _buttons[MENU1_BTN].enabled = true;
  _buttons[MENU1_BTN].id = MENU1_BTN;

  _buttons[TIMER1_BTN].x = btnW + BUTTON_X_SPACING;
  _buttons[TIMER1_BTN].y = btnH + 60;
  _buttons[TIMER1_BTN].width = btnW + 50;
  _buttons[TIMER1_BTN].height = BUTTON_HEIGHT + 20;
  _buttons[TIMER1_BTN].visible = false;
  _buttons[TIMER1_BTN].active = false;
  _buttons[TIMER1_BTN].enabled = false;
  _buttons[TIMER1_BTN].id = TIMER1_BTN;

  _buttons[BACK_BTN].x = btnW;
  _buttons[BACK_BTN].y = btnH - BUTTON_HEIGHT ;
  _buttons[BACK_BTN].width = btnW;
  _buttons[BACK_BTN].height = BUTTON_HEIGHT;
  _buttons[BACK_BTN].visible = false;
  _buttons[BACK_BTN].active = false;
  _buttons[BACK_BTN].enabled = false;
  _buttons[BACK_BTN].id = BACK_BTN;

  for (int i = MENU1_BTN; i < NUM_BTNS; i++) {
    _buttons[i].gfx = _gfx;
    _buttons[i].drawButton();
  }

}


//void UI::welcomeScreen() {
//  _gfx->fillScreen(BLACK);                 //Erase the screen
//  _gfx->drawRect(0, 0, 319, 240, WHITE);   //Draw white frame
//
//  int btnW = _gfx->width() / 3 - 8;
//  int btnH = _gfx->height() - 1;
//
//
//
//  //**PROXY CODE**//
//  //Create Red Button
//  _gfx->fillRect(60, 180, 200, 40, RED);
//  _gfx->drawRect(60, 180, 200, 40, WHITE);
//  _gfx->setCursor(70, 188);
//  _gfx->setTextColor(WHITE);
//  _gfx->setTextSize(3);
//  _gfx->print("START MENU");
//
//  for (int i = WELCOME_BTN; i < NUM_BTNS; i++) {
//    _buttons[i].gfx = _gfx;
//    _buttons[i].drawButton();
//  }
//}
//
//void UI::menuScreen() {
//
//  _gfx->fillScreen(BLACK);                 //Erase the screen
//  _gfx->drawRect(0, 0, 319, 240, WHITE);   //Draw white frame
//
//  int btnW = _gfx->width() / 3 - 8;
//  int btnH = _gfx->height() - 1;
//
//  //**ORIGINAL CODE**//
//
//
//  //**PROXY CODE**//
//  _gfx->fillRect(80, 20, 155, 50, ORANGE);
//  _gfx->drawRect(80, 20, 155, 50, WHITE);
//  _gfx->setCursor(98, 27);
//  _gfx->setTextColor(BLACK);
//  _gfx->setTextSize(4);
//  _gfx->print("Timer");
//
//
//
//  for (int i = WELCOME_BTN; i < NUM_BTNS; i++) {
//    _buttons[i].gfx = _gfx;
//    _buttons[i].drawButton();
//  }
//}
//
//
//float timeDelta = 0;
//float timeAccumulator = 60;
//int last = 0;
//
//void UI::timerScreen() {
//  _gfx->fillScreen(BLACK);                 //Erase the screen
//  _gfx->drawRect(0, 0, 319, 240, WHITE);   //Draw white frame along the screen
//
//  _gfx->fillRect(15, 20, 40, 30, PURPLE);
//  _gfx->drawRect(15, 20, 40, 30, WHITE);
//  _gfx->setCursor(23, 27);
//  _gfx->setTextColor(BLACK);
//  _gfx->setTextSize(2.5);
//  _gfx->print("<-");
//
//  int now = millis();
//  timeDelta = (now - last) / 1000.0f;
//  last = now;
//
//  timeAccumulator -= timeDelta;
//
//  _gfx->setCursor(100, 100);
//  _gfx->setTextColor(TEAL);
//  _gfx->setTextSize(4);
//  _gfx->print(timeAccumulator);
//
//  if (timeAccumulator <= 1) {
//    timeAccumulator = 60;
//  }
//
//  delay(1000);
//
//}

