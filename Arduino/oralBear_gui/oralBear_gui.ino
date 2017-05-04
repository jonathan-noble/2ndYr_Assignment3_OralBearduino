/*
    User interface touch-screen for Oral Bearduino
    that will be displayed on the TFT LCD screen!
    1. Splash Screen
    2. Reminder and Instruction screen
    3. Tips on how to brush teeth with Timer
    4. Timer
*/

#include <Arduino.h>

#include "Debug.h"
#include "UI.h"
#include "Settings.h"

Settings settings;
UI ui;

int currentState = TIMER_BTN;
unsigned long currentTimerValue = 0;
unsigned long targetTime = 0;


// logic
bool prog = false;
bool start = false;
bool pause = false;


// *** Begin Callback functions ***
void onInfoClick();
void onTimerClick();
void onPlayClick();
void onPauseClick();
// *** End Callback functions ***


void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif

  ui.init();

  ui.showSplashScreen(settings.getName(), settings.getVersion());

  ui.addButton(TIMER_BTN, onTimerClick);
  ui.addButton(PLAY_BTN, onPlayClick);
  ui.addButton(PAUSE_BTN, onPauseClick);


  currentState = settings.getStartState();
  if (currentState == TIMER_BTN ) {
    currentTimerValue = settings.getTimers()[currentState - 1];
  }

  delay(1500);
  ui.showReminder1Screen();
  delay(3000);
  ui.showReminder2Screen();
  delay(3000);
  ui.showInstructionScreen();
  delay(2500);
  ui.display();

  ui.activateButton(PLAY_BTN);

  ui.activateButton(currentState);

  ui.updateContent(currentTimerValue);
}


void loop() {

  if (start) {
    if (currentState == TIMER_BTN) {
      currentTimerValue = millis() - targetTime;
    }
    else {
      currentTimerValue = targetTime - millis();
    }
    currentTimerValue /= 100;
    ui.updateContent(currentTimerValue);
  }

  ui.checkBtnPressed();
}


// *********************** CLICK LOGIC ****************************************
void onTimerClick() {
  if (start) {
    return;
  }

  if (currentState == TIMER_BTN) {
    return;
  }

  DEBUG_PRINTLN("Timer pressed");

  currentState = TIMER_BTN;
  ui.activateButton(currentState);
  settings.setStartState(currentState);

  currentTimerValue = 0;
  ui.updateContent(currentTimerValue);

  prog = false;
}

void onPlayClick() {
  if (start) {
    return;
  }

  DEBUG_PRINTLN("Play pressed");

  DEBUG_PRINT("start with time=");
  DEBUG_PRINTLN(currentTimerValue);

  ui.activateButton(PAUSE_BTN);
  delay(200);

  start = true;
  pause = false;
  prog = false;


  targetTime = millis();
  if (currentState == TIMER_BTN) {
    if (pause) {
      // continue
      targetTime -= currentTimerValue * 100;
    }
  }
  else {
    targetTime += currentTimerValue * 100;
  }
}

void onPauseClick() {
  if (!start) {
    return;
  }

  DEBUG_PRINTLN("Pause pressed");

  DEBUG_PRINT("pause with time=");
  DEBUG_PRINTLN(currentTimerValue);


  start = false;
  pause = true;
  prog = false;

  ui.activateButton(PLAY_BTN);

  delay(300);
}


