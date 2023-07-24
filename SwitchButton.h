/*
 * SwitchButton.h - Basic switch button library.
 * Created by Halil İbrahim İvedi, July 14, 2023.
 * */
#ifndef SwitchButton_h
#define SwitchButton_h

#include "Arduino.h"

class SwitchButton
{
  public:
    SwitchButton(byte buttonPin);
    byte buttonPin;
    bool pressed;
    bool released;
    void begin();
    bool update(byte debounceTime = 50);
  private:
    int _currentState;
    int _lastFlickerableState;
    int _lastSteadyState;
    unsigned long _lastDebounceTime;
};

#endif
