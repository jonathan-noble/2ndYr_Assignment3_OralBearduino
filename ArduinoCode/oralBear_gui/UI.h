#ifndef UI_h
#define UI_h

#include <Arduino.h>
#include <Adafruit_GFX.h>     // Core graphics library: https://github.com/adafruit/Adafruit-GFX-Library
#include <TouchScreen.h>      // https://github.com/adafruit/Touch-Screen-Library

#include "Button.h"
/******************* UI details */

#define NUM_SCREENS 4
#define WELCOME_SCREEN 0
#define BACK_SCREEN 1
#define MENU_SCREEN 2
#define TIMER_SCREEN 3


#define BUTTON_X_SPACING  10
#define BUTTON_HEIGHT     60

class UI {
  public:
    UI();

    void init();
    void display();
    void display2();
    
    void checkBtnPressed();
    void addButton(int btnId, void (*callback)());
    void activateButton(int btnId);

    void welcomeScreen();
    void menuScreen();
    void timerScreen();

  private:
    // Adafruit_GFX_Button buttons[15];    //used later since I'm leaning more on GFX vs TFT library
    //private pointer variables created hence the underscore for conventional purposes
    Button _buttons[NUM_SCREENS];
    int _activeButtonId;
    
    Adafruit_GFX *_gfx;
    TouchScreen *_ts;
};

#endif

