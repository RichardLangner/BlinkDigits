#include <Arduino.h>
/* Uses flashNumber.h to blink (up to) a 5 digit number on a single LED, with 500ms gap between each digit.
Returns 'true' when it completes a group of digits, then repeats after several seconds. 
The blink 'on' and 'off' period is 200ms each. A zero is represented by 1000ms 'on'.

FlashNumber is a class, so you can have several independent flashers at once.
This example code below uses two LEDs:
    One flashes out an incrementing number starting from zero and stops after 11.
    The other increases by 2 each time and stops after 30.

Uses:
    Heatbeat showing the last 3 digits of an IP address.
    Flashing out an error code.
    Flashing out a software mode...

To create a Flashdigits object called 'flasher1':
   FlashDigits flasher1;  

NOTE this is non-blocking code and needs to be in a fast loop, so don't use delay() or other blocking code.

Written by Richard Langner, Sheffield Hackspace, UK 27 May 2023.
Latest code and examples on github.com/RichardLangner/SimpleTimer
*/

#include "BlinkDigits.h"            // github.com/RichardLangner/SimpleTimer/tree/main/SimpleTimer_examples/
BlinkDigits flasher1;               // Create an instance of a flasher object
BlinkDigits flasher2;               // Create a second instance

int ledPin = D4;                    // Wemos D1 mini LED pin, active LOW
int counter1=302 ;           // How many time the complete number flashes

void setup() {
	Serial.begin(74880);            // Wemos D1 mini default baud rate
	pinMode(ledPin, OUTPUT);        // Set LED pin to be an output
    digitalWrite(ledPin, HIGH);     // LED is active LOW
    delay(3000);                    // Not required
    flasher1.setup(ledPin, LOW);    // Define the LED 1 pin and its active level
}

void loop() {
    if(flasher1.blink(counter1)){
        Serial.printf("Flasher1 has just flashed %d\n", counter1++ );
    };
}