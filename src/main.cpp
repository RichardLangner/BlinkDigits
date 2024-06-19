#include <Arduino.h>
/* Uses BlinkDigits.h to blink (up to) a 5 digit number on a single LED, with 500ms gap between each digit.
Returns 'true' when it completes a group of digits, then repeats after several seconds. 
The blink 'on' and 'off' period is 200ms each. A zero is represented by 1000ms 'on'.

BlinkDigits is a class, so you can have several independent flashers at once.

What can I use it for?
    Wifi heatbeat showing the last 3 digits of an IP address.
    Flashing out an error code.
    Flashing out a software mode...

To create a Flashdigits object called 'flasher1':
   BlinkDigits flasher1;  

NOTE this is non-blocking code and needs to be in a fast loop, so don't use delay() or other blocking code.

Written by Richard Langner, Sheffield Hackspace, UK 19 June 2024.
Latest code and examples on github.com/RichardLangner/BlinkDigits
*/

#include "BlinkDigits.h"            // github.com/RichardLangner/SimpleTimer/tree/main/SimpleTimer_examples/
BlinkDigits flasher1;               // Create an instance of a flasher object

int ledPin = D4;                    // Wemos D1 mini LED pin, active LOW
int myNumber=92 ;                   // The digits to blink

void setup() {
	Serial.begin(115200);            // Wemos D1 mini default baud rate
	pinMode(ledPin, OUTPUT);        // Set LED pin to be an output
    digitalWrite(ledPin, HIGH);     // Turn off LED (on is active LOW)
    delay(3000);                    // Not required
    flasher1.config(200,1000,500, 3000); // slower timings.
}

void loop() {
    if(flasher1.blink(ledPin, LOW, myNumber,3)){
        Serial.printf("Flasher1 has just flashed %d\n", myNumber++ );
    };
}