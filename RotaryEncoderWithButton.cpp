/*
 * RotaryEncoderWithButton.cpp
 *
 *  Created on: Aug 9, 2014
 *      Author: Konstantin Gredeskoul
 *
 *  (c) 2014 All rights reserved.  Please see LICENSE.
 */

#include "RotaryEncoderWithButton.h"

 int aState;
 int aLastState;  

RotaryEncoderWithButton::RotaryEncoderWithButton(
		uint8_t rotaryPinA,
		uint8_t rotaryPinB,
		uint8_t buttonPin) {

	_lastButtonPressedAt = 0;
	_rotaryPinA = rotaryPinA;
	_rotaryPinB = rotaryPinB;
	_buttonPin = buttonPin;
	_hasNotReadRotary = true;
}

void RotaryEncoderWithButton::begin() {
	pinMode(_rotaryPinA, INPUT);
	pinMode(_rotaryPinB, INPUT);
	pinMode(_buttonPin, INPUT);
}

uint8_t RotaryEncoderWithButton::GetCounter(){
   return counter;
}

void RotaryEncoderWithButton::ReadAB(){
	aState = digitalRead(_rotaryPinA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(_rotaryPinB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState;
}


bool RotaryEncoderWithButton::buttonClicked() {
	bool currentState;
	bool previousState;
	bool pressed = false;

	if (millis() - _lastButtonPressedAt < BUTTON_PRESS_DELAY)
		return false;

	previousState = currentState = digitalRead(_buttonPin);      // store switch state
	for (int counter = 0; counter < DEBOUNCE_DELAY; counter++) {
		delay(1); // wait for 1 millisecond
		currentState = digitalRead(_buttonPin);  // read the pin
		if (currentState != previousState) {
			pressed = true;
			_lastButtonPressedAt = millis();
			//counter = 0; // reset the counter if the state changes
			previousState = currentState;  // and save the current currentState
		}
	}

	// here when the switch currentState has been stable longer than the debounce period
	return pressed;
}
