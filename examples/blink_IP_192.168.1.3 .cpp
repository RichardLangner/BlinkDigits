/*
Written by Richard Langner, Sheffield Hackspace, UK 20 June 2024.
Latest code and examples on github.com/RichardLangner/BlinkDigits

Blinks out a full IP address - 4 octets of 3 digits each from a array of uint8.
192.168.1.3
using LED_BUILTIN.

This code is non-blocking, so please do not use delay(...) in your code.
Pins and active LED level is for Wemos D1 mini. Your device may be different.
*/
#include <Arduino.h>
#include "BlinkDigits.h"
BlinkDigits blinker;                // Create an instance of a BlinkDigits object

int ledPin = D4;                    // Wemos D1 mini LED pin, active LOW
uint8_t ip[] = {192, 168, 1, 3};    // May be obtained by WiFi.localIP() on ESP8266
int pointer=0;                      // Points to an array element

void setup() {
	pinMode(ledPin, OUTPUT);          // Set LED pin to be an output
}

void loop() {
    // Note 1: ip[array] is uint8 and blink expects int, so we have to cast it.
    // Note 2: Omit the ,3 if you don't want leading zeros.
    if (blinker.blink(ledPin, LOW, static_cast<int>(ip[pointer]),3))
    {
     pointer = (pointer + 1) % 4;
    }

    // Your other code here...
    }

