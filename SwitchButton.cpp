/*
 * SwitchButton.cpp - Basic switch button library.
 * Created by Halil İbrahim İvedi, July 14, 2023.
 * */

#include "Arduino.h"
#include "SwitchButton.h"

SwitchButton::SwitchButton(byte pin) {
  buttonPin = pin;
  pressed = false;
  _currentState = LOW;
  _lastFlickerableState = LOW;
  _lastSteadyState = LOW;
  _lastDebounceTime = 0;
}

void SwitchButton::begin() {
  pinMode(buttonPin, INPUT_PULLUP);
}

bool SwitchButton::update(byte debounceTime = 50) {
  bool stateChanged = false;
  // read the state of the button
  _currentState = digitalRead(buttonPin);

  // check to see if you just pressed the button (LOW to HIGH)
  // and you've waited long enough
  // since the last press to ignore any noise:
  
  // If the button changed, due to noise or pressing:
  if (_currentState != _lastFlickerableState) {
    // reset the bouncing timer
    _lastDebounceTime = millis();
    // save the last flickerable state
    _lastFlickerableState = _currentState;
  }

  if ((millis() - _lastDebounceTime) > debounceTime) {
    // whatever the reading is at, it's been there for longer than
    // debounce delay, so take it as the actual current state:

    // if the button has changed:
    if (_lastSteadyState == HIGH && _currentState == LOW) {
      pressed = true;
      stateChanged = true;
    } else if (_lastSteadyState == LOW && _currentState == HIGH) {
      pressed = false;
      stateChanged = true;
    }

    // save the last steady state
    _lastSteadyState = _currentState;
  }

  return stateChanged;
}
