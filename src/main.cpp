/*
Written by Richard Langner, Sheffield Hackspace, UK 25 November 2024.
Latest code and examples on github.com/RichardLangner/BlinkDigits

Blinks out an incrementing number using LED_BUILTIN and starting with 8.
See the examples to add leading digits, or configure timings.

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
    if(flasher1.blink(ledPin, LOW, myNumber)){
        myNumber++;
    }
}