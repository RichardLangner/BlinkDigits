/*
Written by Richard Langner, Sheffield Hackspace, UK 20 June 2024.
Latest code and examples on github.com/RichardLangner/BlinkDigits

Blinks out an 3 digit number 26 (with leading zeros i.e. 026),
using LED_BUILTIN.

Pins and active LED level is for Wemos D1 mini. Your device may be different.
*/
#include <Arduino.h>
#include "BlinkDigits.h"
BlinkDigits blinker;                // Create an instance of a BlinkDigits object

int ledPin = D4;                    // Wemos D1 mini LED pin, active LOW
int myNumber = 26 ;                 // The digits to blink, width=3 to show leading zeros

void setup() {
	pinMode(ledPin, OUTPUT);        // Set LED pin to be an output
}

void loop() {
    blinker.blink(ledPin, LOW, myNumber,3);
    // Your other code here...
}