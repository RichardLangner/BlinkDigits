/*
Written by Richard Langner, Sheffield Hackspace, UK 25 November 2024.
Latest code and examples on github.com/RichardLangner/BlinkDigits

Blinks out an incrementing number (with leading zeros if less than 3 digits),
using LED_BUILTIN and starting with 8.

This code is non-blocking, so please do not use delay(...) in your code.
Pins and active LED level is for Wemos D1 mini. Your device may be different.
*/
#include <Arduino.h>
#include "BlinkDigits.h"
BlinkDigits flasher1;               // Create an instance of a BlinkDigits object

int ledPin = D4;                    // Wemos D1 mini LED pin, active LOW
int myNumber = 8 ;                  // The starting digit to blink

void setup() {
	pinMode(ledPin, OUTPUT);        // Set LED pin to be an output
}

void loop() {
    // Omit the ,3 if you don't want leading zeros.
    if(flasher1.blink(ledPin, LOW, myNumber ,3)){
        myNumber++;
    }
}