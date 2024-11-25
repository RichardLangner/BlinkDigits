/*
Written by Richard Langner, Sheffield Hackspace, UK 25 November 2024.
Latest code and examples on github.com/RichardLangner/BlinkDigits

Blinks out an (any sized) array of integers using LED_BUILTIN.
Each number can be up to 99999, and you can set the minimum width for each digit,
padding with leading zeros if required (below is padded to 3 wide).

LED pin and active level is for Wemos D1 mini. Your device may be different.
This code is non-blocking, so please do not use delay(...) in your code.
*/
#include <Arduino.h>
#include "BlinkDigits.h"
BlinkDigits blinker;                // Create an instance of a BlinkDigits object

int ledPin = D4;                    // Wemos D1 mini LED pin, active LOW
int array[] = {22, 51};             // You can have any size of array of integers
int pointer=0;                      // Points to an array element

void setup() {
	pinMode(ledPin, OUTPUT);        // Set LED pin to be an output
}

void loop() {
    // Omit the ,3 if you don't want leading zeros.
    if (blinker.blink(ledPin, LOW, array[pointer]),3)
        {
        pointer = (pointer + 1) % (sizeof(array)/sizeof(array[0]));
        }

    // Your other code here...
    }

