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

UI ui;

int currentState = WELCOME_SCREEN;
unsigned int currentTimerValue = 0;

//logic
bool start = false;


// *** Begin Callback functions ***
//void onWelcomeClick();
//void onMenu1Click();

void setup() {
  Serial.begin(115200);
  ui.init();  // calling the initialized function of class UI
 // ui.addButton(WELCOME_SCREEN, onWelcomeClick);  //adding the button and its function to setup

  delay(2000);

  //ui.display();

}

void loop() {

  ui.checkBtnPressed();

}


//void onWelcomeClick() {
//  if (start) {
//    return;
//  }
//
//  if (currentState == WELCOME_SCREEN) {
//    return;
//  }
//
//
//  currentState = WELCOME_SCREEN;
//  ui.addButton(MENU_SCREEN, onMenu1Click);
//  ui.activateButton(currentState);
//}
//
//void onMenu1Click() {
//  if (start) {
//    return;
//  }
//
//  if (currentState == MENU_SCREEN) {
//    return;
//  }
//
//  currentState = MENU_SCREEN;
//  ui.activateButton(currentState);
//}

