/*
    User interface for Robobearduino,
    will be displayed on the tft lcd screen
    1.home menu
      options:
        -timer
        -game
        -tips/advice on how to brush teeth
*/

//Libraries
#include <Arduino.h>
#include "UI.h"
#include "Settings.h"

UI ui;
Settings settings;

int currentState = MENU1_BTN;
unsigned int currentTimerValue = 0;

//logic
bool start = false;


// *** Begin Callback functions ***
void onMenu1Click();
void onTimer1Click();
void onBackClick();

void setup() {
  Serial.begin(115200);
  ui.init();  // calling the initialized function of class UI

  ui.showSplashScreen();

  ui.addButton(MENU1_BTN, onMenu1Click);
  ui.addButton(TIMER1_BTN, onTimer1Click);
  ui.addButton(BACK_BTN, onBackClick);

  delay(2000);

  ui.display();

  ui.activateButton(MENU1_BTN);

}

void loop() {

  if (start) {
    if (currentState == MENU1_BTN) {
       ui.activateButton(TIMER1_BTN);
       ui.activateButton(BACK_BTN);
      // ui.updateContent();
    }
  }

  ui.checkBtnPressed();

}

void onMenu1Click() {
  if (start) {
    return;
  }

  if (currentState == MENU1_BTN) {
    return;
  }

  currentState = MENU1_BTN;
  ui.activateButton(MENU1_BTN);
//  ui.activateButton(TIMER1_BTN);
//  ui.activateButton(BACK_BTN);
}

void onTimer1Click() {
  if (start) {
    return;
  }

  if (currentState == TIMER1_BTN) {
    return;
  }

  currentState = TIMER1_BTN;
  ui.activateButton(TIMER1_BTN);
  ui.activateButton(BACK_BTN);
}

void onBackClick() {
  if (start) {
    return;
  }

  if (currentState == TIMER1_BTN) {
    return;
  }

  currentState = TIMER1_BTN;
  ui.activateButton(MENU1_BTN);
}

