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

#define MINPRESSURE 0
#define MAXPRESSURE 1000

int currentState = 1;

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
  currentState = 1;
}


void UI::btnPressed() {
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
    if (currentState == 1) {
      if (p.x > 60 && p.x < 260 && p.y > 180 && p.y < 220) // The user has pressed inside the red rectangle
      {
        currentState = 2;
        menuScreen();
      }
    }

    //Start Menu Screen
    if (currentState == 2) {
      //Back Button
      if (p.x > 15 && p.x < 55 && p.y > 20 && p.y < 70)
      {
        currentState = 1;
        welcomeScreen();
      }
      //Timer Button
      if (p.x > 80 && p.x < 235 && p.y > 20 && p.y < 70)
      {
        currentState = 3;
        timerScreen();
      }
    }

    //Timer Screen
    if (currentState == 3) {
      //Back Button
      if (p.x > 15 && p.x < 55 && p.y > 20 && p.y < 70)
      {
        currentState = 2;
        menuScreen();
      }
    }

    for (int i = HOME_BTN; i < NUM_BTNS; i++) {
      if(_buttons[i].hit(p.x, p.y)) {
        break;
      }
    }
    
  }

 
  delay(10); // UI debouncing  
}


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

  //Create Red Button
  _gfx->fillRect(60, 180, 200, 40, RED);
  _gfx->drawRect(60, 180, 200, 40, WHITE);
  _gfx->setCursor(70, 188);
  _gfx->setTextColor(WHITE);
  _gfx->setTextSize(3);
  _gfx->print("START MENU");

}

void UI::menuScreen() {
  _gfx->fillScreen(BLACK);                 //Erase the screen
  _gfx->drawRect(0, 0, 319, 240, WHITE);   //Draw white frame

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








