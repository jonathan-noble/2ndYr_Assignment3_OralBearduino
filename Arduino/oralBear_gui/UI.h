#ifndef UI_h
#define UI_h

#include <Arduino.h>
#include <Adafruit_GFX.h>     // Core graphics library: https://github.com/adafruit/Adafruit-GFX-Library
#include <TouchScreen.h>      // https://github.com/adafruit/Touch-Screen-Library

//all inputs from button class is implemented here
#include "Button.h"
/******************* UI details */

#define NUM_BTNS     3
//#define WELCOME_BTN  0
#define MENU1_BTN    0
#define TIMER1_BTN   1
#define BACK_BTN     2


#define BUTTON_X_SPACING  10
#define BUTTON_HEIGHT     60

class UI {
  public:
    UI();

    void init();
    void display();

    void updateContent(unsigned int newContent);
    void showSplashScreen();

    void checkBtnPressed();
    void addButton(int btnId, void (*callback)());
    void activateButton(int btnId);

//    void welcomeScreen();
//    void menuScreen();
//    void timerScreen();

  private:
    // Adafruit_GFX_Button buttons[15];    //used later since I'm leaning more on GFX vs TFT library
    //private pointer variables created hence the underscore for conventional purposes
    Button _buttons[NUM_BTNS];
    int _activeButtonId;
    unsigned int _content;

    Adafruit_GFX *_gfx;
    TouchScreen *_ts;
};

#endif

