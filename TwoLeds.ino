/*
 * TwoLeds – this example demonstrates using RotaryEncoder with a button.
 *
 * Dependencies for the library:
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * Dependencies for the example:
 *
 * RotaryEncoderWithButton library
 * SimpleTimer library
 *
 *  Created on: Aug 9, 2014
 *      Author: Konstantin Gredeskoul
 *
 *  (c) 2014 All rights reserved.  Please see LICENSE.
 */

#include <TaskScheduler.h>
#include <M5StickC.h>
#include <Arduino.h>
#include "RotaryEncoderWithButton.h"


//#include <SimpleTimer.h>

//RotaryEncoderWithButton rotary(2,3,4);
RotaryEncoderWithButton rotary(26,36,0);

uint32_t data;
int i;
void t1Callback();
Task t1(5, TASK_FOREVER, &RotaryEncoderWithButton::ReadAB);
Scheduler runner; 

void setup() {
	M5.begin();
	Serial.begin(115200);
	rotary.begin();

	runner.init();
  	runner.addTask(t1);

	delay(100);
	t1.enable();

}

void loop() {
	runner.execute();
}
