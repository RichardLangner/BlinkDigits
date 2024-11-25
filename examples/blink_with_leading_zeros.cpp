/*
Written by Richard Langner, Sheffield Hackspace, UK 25 November 2024.
Latest code and examples on github.com/RichardLangner/BlinkDigits

Blinks out an 3 digit number '26' using LED_BUILTIN
Set width=3 to show leading zeros(i.e. 026),

This code is non-blocking, so please do not use delay(...) in your code.
Pins and active LED level is for Wemos D1 mini. Your device may be different.
*/
#include <Arduino.h>
#include "BlinkDigits.h"
BlinkDigits blinker;                // Create an instance of a BlinkDigits object

int ledPin = D4;                    // Wemos D1 mini LED pin, active LOW
int myNumber = 26 ;                 // Digits to blink, use the last parameter
//                                  // 

void setup() {
	pinMode(ledPin, OUTPUT);        // Set LED pin to be an output
}

void loop() {
    blinker.blink(ledPin, LOW, myNumber,3);
    // Your other code here...
}