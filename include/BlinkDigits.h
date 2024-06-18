/* 
Blink (up to) a 5 digit number on a single LED. 500ms gap between each digit.
Repeats after 3000ms. Returns 'true' when it completes a group of digits.
The blink 'on' and 'off' period is 200ms each. A zero is 1000ms 'on'.
Interdigit gap is defined by a negative number of ms.
    
Written by Richard Langner, Sheffield Hackspace, UK 18 June 2024.
Latest code and examples on github.com/RichardLangner/SimpleTimer
*/
#ifndef FLASHNUMBER
#define FLASHNUMBER
#include <Arduino.h>

/** @return - true if all the digits have been flashed.
*	@param num number to blink, max 99999.
*	@param width (opional) number of digit places to blink. If not specified, or zero, means with no leading zeros.
*/
class BlinkDigits
{
private:
// bool    _enabled=true;
int     _LED_pin = LED_BUILTIN, _LED_on = LOW;  // Defaults
int ms = 10, blinkCounter =0, arrayIndex=0, offset=0;
int array[11] = {-500,0,-500,0,-500,0,-500,0,-500,0,-2500};

unsigned long _setMillis=0, _prevMillis = 0;
bool firstRun=true;
bool timedOut(unsigned long u){_setMillis=u; return (millis() - _prevMillis >= _setMillis);}
void _start(unsigned long u){_setMillis=u; _prevMillis=millis();}
bool done(unsigned long msecs, int cycles=0){
	// if(!_enabled){return false;}				// Not valid timeOut
	if(!timedOut(msecs)){return false;}				// Not valid timeOut
	_start(msecs); return true;	// Auto restart
	if(firstRun){_start(msecs); firstRun=false; return false;}
	firstRun=true;								// Sleep now ...
	return false;
}

public:
virtual ~ BlinkDigits(){}

    bool blink(int pin, bool activeLevel, int num, int width=0){
        _LED_pin = pin;
        _LED_on = activeLevel;
        // Return if nothing to do; starts timer if not already running.
        if (!done(ms, 0)){return false;}
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
            // Change the LED state; if blinkCounter is 'even' turn off LED
            blinkCounter++; 
            digitalWrite(_LED_pin, blinkCounter %2 ? _LED_on : !_LED_on);  // Odd count = on

            // If the digit value is zero
            if(0 == array[arrayIndex]){
                digitalWrite(_LED_pin,_LED_on);
                ms = 1000;
            }

            // Digit value is non-zero. Either do more flashes, or get next digit
            if(blinkCounter < array[arrayIndex] *2 ){
                ms = 200; 
                return false;
            }
        }
        // Get next digit
        blinkCounter = 0; ++arrayIndex %=11;
        return(arrayIndex==0);
    }
};
#endif