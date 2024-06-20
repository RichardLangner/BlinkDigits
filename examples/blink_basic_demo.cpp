/*
Written by Richard Langner, Sheffield Hackspace, UK 20 June 2024.
Latest code and examples on github.com/RichardLangner/BlinkDigits

Blinks out an incrementing 3 digit number (with leading zeros if less than 3 digits),
using LED_BUILTIN and starting with 8.

The completed number is written to Serial for you to check your reading skills.

Pins and active LED level is for Wemos D1 mini. Your device may be different.
*/
#include <Arduino.h>
#include "BlinkDigits.h"
BlinkDigits flasher1;               // Create an instance of a BlinkDigits object

int ledPin = D4;                    // Wemos D1 mini LED pin, active LOW
int myNumber = 8 ;                  // The digits to blink

void setup() {
	Serial.begin(115200);             // Wemos D1 mini default baud rate
	pinMode(ledPin, OUTPUT);          // Set LED pin to be an output
    // Uncomment next line to really slow down the blinks
    // flasher1.config(400, 1500, 800, 5000);
}

void loop() {
    if(flasher1.blink(ledPin, LOW, myNumber, 3)){
        Serial.print("Flasher1 has just flashed ");
        Serial.print( myNumber++ );
        Serial.println(" with leading zeros.");
    }
}