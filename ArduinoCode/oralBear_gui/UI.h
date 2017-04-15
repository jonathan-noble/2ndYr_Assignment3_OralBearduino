#ifndef UI_h
#define UI_h

#include <Arduino.h>
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <Adafruit_GFX.h>     // Core graphics library: https://github.com/adafruit/Adafruit-GFX-Library
#include <TouchScreen.h>      // https://github.com/adafruit/Touch-Screen-Library

/******************* UI details */
#define BUTTON_X 120
#define BUTTON_Y 100
#define BUTTON_W 60
#define BUTTON_H 30
#define BUTTON_SPACING_X 20
#define BUTTON_SPACING_Y 20
#define BUTTON_TEXTSIZE 2

class UI {
public:
 // UI();

  void init();
  void btnPressed();
  void welcomeScreen();
  void menuScreen();
  void timerScreen();

private:
 // Adafruit_GFX_Button buttons[15];    //used later since I'm leaning more on GFX vs TFT library

TouchScreen *_ts;   //private variables created
};

#endif

