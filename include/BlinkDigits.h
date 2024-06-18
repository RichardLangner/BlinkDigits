/* 
Blink (up to) a 5 digit number on a single LED. 500ms gap between each digit.
Repeats after 3000ms. Returns 'true' when it completes a group of digits.
The flash 'on' and 'off' period is 200ms each. A zero is 1000ms 'on'.
Interdigit gap is defined by a negative number of ms.

You can set enable to true/false to start/stop the flasher:
    flasher1.enabled(true);
    flasher1.enabled(false);

To check if enabled:
    if(flasher1.enabled()){...}
    
Written by Richard Langner, Sheffield Hackspace, UK 27 May 2023.
Latest code and examples on github.com/RichardLangner/SimpleTimer
*/
#ifndef FLASHNUMBER
#define FLASHNUMBER
#include <Arduino.h>
#include "SimpleTimer.h"

/** @return - true if all the digits have been flashed.
*	@param num number to flash, max 99999.
*	@param width (opional) number of digit places to flash. If not specified, or zero, means with no leading zeros.
*/
class BlinkDigits
{
private:
bool    _enabled=true;
int     _LED_pin = LED_BUILTIN, _LED_on = LOW;  // Defaults
SimpleTimer timer1;
int ms = 10, flashCounter =0, arrayIndex=0, offset=0;
int array[11] = {-500,0,-500,0,-500,0,-500,0,-500,0,-2500};

public:
virtual ~ BlinkDigits(){}

    bool flash(int num, int width=0){
        // Exit if disabled
        if(!_enabled){return false;}
        // Return if nothing to do; starts timer if not already running.
        if (!timer1.done(ms, 0)){return false;}
        // Validate arguments
        if(num <0 or width <0 or width >5) {return false;}

        if(arrayIndex==0){
            // Split into 10Th,Th,H,T,Units and put in the alternate array locations
            for(int ii = 1, divisor = 10000; ii < 10; ii += 2, divisor /= 10){
                array[ii] = (num / divisor) % 10;
            }
            // Calculate the offset array position to start at for auto-width
            if(width==0){offset= 10-(2 * ((int)log10(num) +1));} else {offset = 10 - 2*width;}
            arrayIndex= offset;
        }
        
        // Gaps between digits (indicated by a minus value)
        if(array[arrayIndex] < 0){                // Check if minus
            digitalWrite(_LED_pin, !_LED_on);     // Turn LED off
            ms = -array[arrayIndex];              // Make gap value positive
        }
        else{
            // Change the LED state; if flashCounter is 'even' turn off LED
            flashCounter++; 
            digitalWrite(_LED_pin, flashCounter %2 ? _LED_on : !_LED_on);  // Odd count = on

            // If the digit value is zero
            if(0 == array[arrayIndex]){
                digitalWrite(_LED_pin,_LED_on);
                ms = 1000;
            }

            // Digit value is non-zero. Either do more flashes, or get next digit
            if(flashCounter < array[arrayIndex] *2 ){
                ms = 200; 
                return false;
            }
        }
        // Get next digit
        flashCounter = 0; ++arrayIndex %=11;
        return(arrayIndex==0);
    }

/**	@return 'true' if the flasher is enabled */
    bool enabled(){return _enabled;}

/** @param enabled 'true' enables, 'false' disables the flasher */   
    void enabled(bool enabled){_enabled=enabled;}

/** @param LED_pin the LED pin number
    @param level logic level to turn on the LED **/
    void setup(int LED_pin = D4, int led_on = LOW){
        _LED_pin=LED_pin; _LED_on=led_on;
    }   
};
#endif