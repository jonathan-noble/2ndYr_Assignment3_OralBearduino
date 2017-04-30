#ifndef Settings_h
#define Settings_h

#include <Arduino.h>
#include <String.h>
#include "Debug.h"

#define maxTimer 1

struct EEPROMSettings {
  int version;
  int startState;
  int values[maxTimer];
};


class Settings {
public:
  Settings();
  
  void reset();
  void save();
  
  String getName();
  String getVersion();
  int* getTimers();
  int getStartState();
  void setStartState(int startState);
  
private:
  EEPROMSettings _currentSettings;
};

#endif
