/*
Written by Richard Langner, Sheffield Hackspace, UK 21 June 2024.
Latest code and examples on github.com/RichardLangner/BlinkDigits

Blinks out S-O-S using LED_BUILTIN.

Pins and active LED level is for Wemos D1 mini. Your device may be different.
*/
#include <Arduino.h>
#include "BlinkDigits.h"
BlinkDigits flasher1;               // Create an instance of a BlinkDigits object

int ledPin = D4;                    // Wemos D1 mini LED pin, active LOW
int myNumber = 30003 ;                // The digits to blink SOS

void setup() {
	Serial.begin(115200);             // Wemos D1 mini default baud rate
	pinMode(ledPin, OUTPUT);          // Set LED pin to be an output
    // Tweak the timing for best effect
    flasher1.config(100, 300, 300, 3000);
}

void loop() {
    flasher1.blink(ledPin, LOW, myNumber, 5);
    // ...
}