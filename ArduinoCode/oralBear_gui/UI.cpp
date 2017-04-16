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


int currentScreen = WELCOME_SCREEN;

UI::UI() {
}

void UI::init() {
  MCUFRIEND_kbv *tft = new MCUFRIEND_kbv();
  _gfx = tft;

  tft->reset();
  tft->begin(0x9341);
  tft->setRotation(1);
  _ts = new TouchScreen(XP, YP, XM, YM, 300);

  welcomeScreen();
  currentScreen = WELCOME_SCREEN;

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
    if (currentScreen == WELCOME_SCREEN) {
      if (p.x > 60 && p.x < 260 && p.y > 180 && p.y < 220) // The user has pressed inside the red rectangle
      {
        currentScreen = MENU_SCREEN;
        menuScreen();
      }
    }

    //Start Menu Screen
    if (currentScreen == MENU_SCREEN) {
      //Back Button
      if (p.x > 15 && p.x < 55 && p.y > 20 && p.y < 70)
      {
        currentScreen = WELCOME_SCREEN;
        welcomeScreen();
      }
      //Timer Button
      if (p.x > 80 && p.x < 235 && p.y > 20 && p.y < 70)
      {
        currentScreen = TIMER_SCREEN;
        timerScreen();
      }
    }

    //Timer Screen
    if (currentScreen == TIMER_SCREEN) {
      //Back Button
      if (p.x > 15 && p.x < 55 && p.y > 20 && p.y < 70)
      {
        currentScreen = MENU_SCREEN;
        menuScreen();
      }
    }

    //checking every buttons if they are pressed within the touchpoints
    //    for (int i = WELCOME_SCREEN; i < NUM_SCREENS; i++) {
    //      if (_buttons[i].hit(p.x, p.y)) {
    //        break;
    //      }
  }

  delay(10); // UI debouncing

}

//Calling back the parameters of the functions from the main
void UI::addButton(int btnId, void (*callback)()) {
  _buttons[btnId].callback = callback;
}

//Toggles button to activate/deactivate
void UI::activateButton(int btnId) {
  if (btnId == WELCOME_SCREEN) {
    _buttons[_activeButtonId].activateButtonAndDraw(false);

    _activeButtonId = btnId;
    _buttons[_activeButtonId].activateButtonAndDraw(true);
    return;
  }
}

//void UI::display() {

// if (currentScreen == 1) {
//       _gfx->fillScreen(BLACK);                 //Erase the screen
//  _gfx->drawRect(0, 0, 319, 240, WHITE);   //Draw white frame
//
//  //Print "Hello" Text
//  _gfx->setCursor(100, 30);
//  _gfx->setTextColor(WHITE);
//  _gfx->setTextSize(4);
//  _gfx->print("Hello");
//
//  //Print "Master!" text
//  _gfx->setCursor(80, 100);
//  _gfx->setTextColor(RED);
//  _gfx->setTextSize(4);
//  _gfx->print("Master!");
//
//  int btnW = _gfx->width() / 3 - 8;
//  int btnH = _gfx->height() - 1;
//
//  _buttons[WELCOME_SCREEN].x = btnW + BUTTON_X_SPACING - 2;
//  _buttons[WELCOME_SCREEN].y = btnH - BUTTON_HEIGHT;
//  _buttons[WELCOME_SCREEN].width = btnW + 90;
//  _buttons[WELCOME_SCREEN].height = BUTTON_HEIGHT + 20;
//  _buttons[WELCOME_SCREEN].visible = true;
//  _buttons[WELCOME_SCREEN].active = false;
//  _buttons[WELCOME_SCREEN].enabled = true;
//  _buttons[WELCOME_SCREEN].id = WELCOME_SCREEN;
// }
//
//  _gfx->fillScreen(BLACK);                 //Erase the screen
//  _gfx->drawRect(0, 0, 319, 240, WHITE);   //Draw white frame
//  _buttons[MENU_SCREEN].x = btnW;
//  _buttons[MENU_SCREEN].y = btnH - BUTTON_HEIGHT * 2;
//  _buttons[MENU_SCREEN].width = btnW + 90;
//  _buttons[MENU_SCREEN].height = BUTTON_HEIGHT + 20;
//  _buttons[MENU_SCREEN].visible = true;
//  _buttons[MENU_SCREEN].active = false;
//  _buttons[MENU_SCREEN].enabled = true;
//  _buttons[MENU_SCREEN].id = MENU_SCREEN;

//for (int i = WELCOME_SCREEN; i < NUM_SCREENS; i++) {
//  _buttons[i].gfx = _gfx;
//  _buttons[i].drawButton();
//}


//}


void UI::welcomeScreen() {
  _gfx->fillScreen(BLACK);                 //Erase the screen
  _gfx->drawRect(0, 0, 319, 240, WHITE);   //Draw white frame

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

  int btnW = _gfx->width() / 3 - 8;
  int btnH = _gfx->height() - 1;

  //**ORIGINAL CODE**//
  //  _buttons[WELCOME_SCREEN].x = btnW + BUTTON_X_SPACING - 2;
  //  _buttons[WELCOME_SCREEN].y = btnH - BUTTON_HEIGHT;
  //  _buttons[WELCOME_SCREEN].width = btnW + 90;
  //  _buttons[WELCOME_SCREEN].height = BUTTON_HEIGHT + 20;
  //  _buttons[WELCOME_SCREEN].visible = true;
  //  _buttons[WELCOME_SCREEN].active = false;
  //  _buttons[WELCOME_SCREEN].enabled = true;
  //  _buttons[WELCOME_SCREEN].id = WELCOME_SCREEN;


  //**PROXY CODE**//
  //Create Red Button
  _gfx->fillRect(60, 180, 200, 40, RED);
  _gfx->drawRect(60, 180, 200, 40, WHITE);
  _gfx->setCursor(70, 188);
  _gfx->setTextColor(WHITE);
  _gfx->setTextSize(3);
  _gfx->print("START MENU");

  for (int i = WELCOME_SCREEN; i < NUM_SCREENS; i++) {
    _buttons[i].gfx = _gfx;
    _buttons[i].drawButton();
  }
}

void UI::menuScreen() {

  _gfx->fillScreen(BLACK);                 //Erase the screen
  _gfx->drawRect(0, 0, 319, 240, WHITE);   //Draw white frame

  int btnW = _gfx->width() / 3 - 8;
  int btnH = _gfx->height() - 1;

  //**ORIGINAL CODE**//

  //  _buttons[MENU_SCREEN].x = btnW;
  //  _buttons[MENU_SCREEN].y = btnH - BUTTON_HEIGHT * 2;
  //  _buttons[MENU_SCREEN].width = btnW + 90;
  //  _buttons[MENU_SCREEN].height = BUTTON_HEIGHT + 20;
  //  _buttons[MENU_SCREEN].visible = true;
  //  _buttons[MENU_SCREEN].active = false;
  //  _buttons[MENU_SCREEN].enabled = true;
  //  _buttons[MENU_SCREEN].id = MENU_SCREEN;


  //**PROXY CODE**//
  _gfx->fillRect(15, 20, 40, 30, PURPLE);
  _gfx->drawRect(15, 20, 40, 30, WHITE);
  _gfx->setCursor(23, 27);
  _gfx->setTextColor(BLACK);
  _gfx->setTextSize(2.5);
  _gfx->print("<-");

  _gfx->fillRect(80, 20, 155, 50, ORANGE);
  _gfx->drawRect(80, 20, 155, 50, WHITE);
  _gfx->setCursor(98, 27);
  _gfx->setTextColor(BLACK);
  _gfx->setTextSize(4);
  _gfx->print("Timer");



  for (int i = WELCOME_SCREEN; i < NUM_SCREENS; i++) {
    _buttons[i].gfx = _gfx;
    _buttons[i].drawButton();
  }
}


float timeDelta = 0;
float timeAccumulator = 60;
int last = 0;

void UI::timerScreen() {
  _gfx->fillScreen(BLACK);                 //Erase the screen
  _gfx->drawRect(0, 0, 319, 240, WHITE);   //Draw white frame along the screen

  _gfx->fillRect(15, 20, 40, 30, PURPLE);
  _gfx->drawRect(15, 20, 40, 30, WHITE);
  _gfx->setCursor(23, 27);
  _gfx->setTextColor(BLACK);
  _gfx->setTextSize(2.5);
  _gfx->print("<-");

  int now = millis();
  timeDelta = (now - last) / 1000.0f;
  last = now;

  timeAccumulator -= timeDelta;

  _gfx->setCursor(100, 100);
  _gfx->setTextColor(TEAL);
  _gfx->setTextSize(4);
  _gfx->print(timeAccumulator);

  if (timeAccumulator <= 1) {
    timeAccumulator = 60;
  }

  delay(1000);

}








