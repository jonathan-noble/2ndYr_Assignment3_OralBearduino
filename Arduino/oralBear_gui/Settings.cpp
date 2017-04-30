
#include "Settings.h"

#include <EEPROM.h>


#define CURRENT_VERSION   1
#define MACHINE_NAME      "Oral Bearduino"


Settings::Settings() {
  // read from EEPROM
  EEPROM.get(0, _currentSettings);

  if (_currentSettings.version != CURRENT_VERSION) {
    reset();
  }
}

void Settings::reset() {
  // read from EEPROM
  _currentSettings.version = CURRENT_VERSION;
  //Values of the duration of the timer varies
  _currentSettings.startState = 0;
  _currentSettings.values[0] = 50;
  //  save();
}

//potential function to save the previous timer or the state
//void Settings::save() {
//  EEPROM.put(0, _currentSettings);
//}


int Settings::getStartState() {
  return _currentSettings.startState;
}

void Settings::setStartState(int startState) {
  _currentSettings.startState = startState;
  // save();
}

String Settings::getName() {
  return MACHINE_NAME;
}

String Settings::getVersion() {
  return String(_currentSettings.version);
}

long* Settings::getTimers() {
  return _currentSettings.values;
}


