#ifndef UI_h
#define UI_h

#include <Arduino.h>
#include <Adafruit_GFX.h>     // Core graphics library: https://github.com/adafruit/Adafruit-GFX-Library
#include <TouchScreen.h>      // https://github.com/adafruit/Touch-Screen-Library

//all inputs from button class is implemented here
#include "Button.h"
#include "Settings.h"

/******************* Button UI details */
#define NUM_BTNS     3
#define TIMER_BTN    0
#define PLAY_BTN     1
#define PAUSE_BTN    2

#define BUTTON_X_SPACING  10
#define BUTTON_HEIGHT     50

class UI {
  public:
    UI();

    void init();
    void display();

    void updateContent(unsigned int newContent);
    void showSplashScreen(String name, String version);
    void showReminder1Screen();
    void showReminder2Screen();
    void showInstructionScreen();

    void checkBtnPressed();
    void addButton(int btnId, void (*callback)());
    void activateButton(int btnId);


  private:
    //private pointer variables created hence the underscore for conventional purposes
    Button _buttons[NUM_BTNS];
    Settings _settings;
    int _activeButtonId;
    unsigned int _content;

    Adafruit_GFX *_gfx;
    TouchScreen *_ts;
};

#endif

