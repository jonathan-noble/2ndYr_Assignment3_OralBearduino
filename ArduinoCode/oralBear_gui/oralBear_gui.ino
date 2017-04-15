/*
    User interface for Robobearduino,
    will be displayed on the tft lcd screen
    1.home menu
      options:
        -timer
        -game
        -tips/advice on how to brush teeth
*/

#include <Arduino.h>
#include "UI.h"

UI ui;

//char btnlabels[15][5] = {"Timer", "", "", "Game", "", "", "Guide" , "", "", "", "", "", "", "", "" };
//uint16_t btncolors[3] = {DARKGREEN, CYAN, ORANGE};

void setup() {
  Serial.begin(9600);
  ui.init();
}

void loop() {

  digitalWrite(13, HIGH);
  digitalWrite(13, LOW);
  ui.btnPressed();

}

