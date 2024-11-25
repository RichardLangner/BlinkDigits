# 'BlinkDigits' by Richard Langner, Nov 2024
## Bink out numbers on a single LED.

Display any number from 0 to 99999. For example 390 is blinked as

- **3** brief flashes, <br>
- **9** brief flashes, <br>
- **0** (one long flash).<br><br>
After each digit there is a brief pause before the next digit is flashed.<br>
When all digits in your number have been flashed, there is a longer pause, and then it all repeats if you want it to.
## How can BlinkDigits improve my project?
- Use as a heartbeat LED to indicate the status of the program.
- Indicate an analog reading
- Indicate a digital counter
- When connected to wifi, blink out the last 3 digits of the IP address, so you know where to find your device on the network.

## How to use BlinkDigits
Example :<br>
`flasher1.blink ( D4, LOW, 1883 )`<br>
- **D4** is the pin number of the LED (e.g. LED_BUILTIN) <br>
- **LOW**  (or HIGH) is set to define the level required to turn on the LED<br>
- **1883** is the number you want to blink (in the range of 0-99999)<br><br>
The BlinkDigits funtion returns 'true' when all the digits have been flashed. See **examples** for why this is useful.<br>

## Example code
Here is a simple example which uses one line of code in loop( ) to blink out 23 repeatedly<br>

```
#include "BlinkDigits.h"
BlinkDigits flasher1;
int ledPin = D4;

void setup() {
	pinMode(ledPin, OUTPUT);`
}

void loop() {
    flasher1.blink(ledPin, LOW, 23);
}
```
The **examples** folder has some useful code.
### Leading zeros
If you want to blink out leading zeros, for example 023, simply state the number of places you want - using the optional 'width' parameter - in this case 3.

`flasher1.blink(ledPin, LOW, myNumber,3);`<br>
## Customisation
 Blinking too fast for you to read? <br>
 Here we slow things right down.<br>
`flasher1.config(400,1500,800, 5000); // slower timings in milliseconds.`<br>
- &nbsp;400 : the on/off digit 'flash' times,<br>
- 1500 : the zero digit's longer 'on' time<br>
- &nbsp;800 : the delay between digits<br>
- 5000 : the delay before repeating the whole number.<br>
- Defaults are 200, 1000, 500, 3000.

## Trouble shooting
- **Eratic timing of blinks** : ensure you haven't used blocking code elsewhere in your project, such as delay(200). BlinkDigits relies on fast non-blocking code in loop().

- **LED not blinking** : Ensure you have the correct pin for the LED, and it is defined as output.

- **Still not blinking** : Ensure the number is between 0 and 99999, and not negative.

- **Wrong number of blinks** : do not add your own leading zero in code, as this denotes octal numbers i.e. do not use 023 (19 in octal), simply use 23 instead.