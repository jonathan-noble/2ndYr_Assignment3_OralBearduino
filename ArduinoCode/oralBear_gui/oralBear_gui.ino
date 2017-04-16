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

int currentState = WELCOME_BTN;

//logic
bool start = false;


// *** Begin Callback functions ***
void onWelcomeClick();

void setup() {
  Serial.begin(115200);
  ui.init();  // calling the initialized function of class UI
  ui.addButton(WELCOME_BTN, onWelcomeClick);  //adding the button and its function to setup


  // delay(2000);

  ui.display();
}

void loop() {
  //  digitalWrite(13, HIGH);
  //  digitalWrite(13, LOW);
  if (start && (currentState != WELCOME_BTN)) {
    // motor.stop();
    start = false;

  }
  
  ui.checkBtnPressed();

}


void onWelcomeClick() {
  if (start) {
    return;
  }

  if (currentState == WELCOME_BTN) {
    return;
  }

  currentState = WELCOME_BTN;
  ui.activateButton(currentState);
}

