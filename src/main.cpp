/*
Written by Richard Langner, Sheffield Hackspace, UK 20 June 2024.
Latest code and examples on github.com/RichardLangner/BlinkDigits

Blinks out an array of integers using LED_BUILTIN.

Pins and active LED level is for Wemos D1 mini. Your device may be different.
*/
#include <Arduino.h>
#include "BlinkDigits.h"
BlinkDigits blinker;                // Create an instance of a flasher object

int ledPin = D4;                    // Wemos D1 mini LED pin, active LOW
int array[] = {22, 51};             // You can have any size of array
int pointer=0;                      // Points to an octet

void setup() {
	pinMode(ledPin, OUTPUT);        // Set LED pin to be an output
    // ...
}

void loop() {
    if (blinker.blink(ledPin, LOW, array[pointer]))
    {
     pointer = (pointer + 1) % (sizeof(array)/sizeof(array[0]));
    }

    // Your other code here...
    }

