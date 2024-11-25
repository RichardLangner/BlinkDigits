#ifndef FLASHNUMBER
#define FLASHNUMBER
#include <Arduino.h>

/**
 * Blink (up to) a 5 digit number on a single LED.
 * User can define the on/off blink times, interdigit gap, zero digit duration, and intergroup delay.
 * Repeats after the intergroup delay. Returns 'true' when it completes a group of digits.
 * 
 * Written by Richard Langner, Sheffield Hackspace, UK 18 June 2024.
 * Latest code and examples on github.com/RichardLangner/SimpleTimer
 */

/** @return - true if all the digits have been flashed.
 *  @param number_to_blink number to blink, up to 5 digits, max 99999.
 *  @param width (optional) number of digit places to blink. If not specified, or zero, means with no leading zeros.
 *  @brief Displays a number 0-99999 by blinking a LED for each digit in turn. 
 *  Written by Richard Langner
 */
class BlinkDigits
{
private:
    int _LED_pin, _LED_on;
    int ms = 10, blinkCounter = 0, arrayIndex = 0, offset = 0;
    int blink_ms = 200, interdigit_gap_ms = 500, zero_digit_ms = 1000, intergroup_ms = 3000;
    int array[11] = {-500, 0, -500, 0, -500, 0, -500, 0, -500, 0, -2500};

    unsigned long _setMillis = 0, _prevMillis = 0;
    bool firstRun = true;

    bool timedOut(unsigned long u) {
        _setMillis = u;
        return (millis() - _prevMillis >= _setMillis);
    }

    void _start(unsigned long u) {
        _setMillis = u;
        _prevMillis = millis();
    }

    bool done(unsigned long msecs) {
        if (!timedOut(msecs)) {
            return false;
        }
        _start(msecs);
        return true;
    }

public:
    virtual ~BlinkDigits() {}

/** 
 *  Sets the on/off times of the blinking LED in milliseconds (default ms in brackets). 
 *  Written by Richard Langner
 *  @param blink on/off time for the blink (200)
 *  @param zero on time for the zero (1000)
 *  @param interdigit time between digits (500)
 *  @param intergroup time before repeating (3000)
 */
    void config(int blink, int zero, int interdigit, int intergroup) {
        blink_ms = blink;
        interdigit_gap_ms = interdigit;
        zero_digit_ms = zero;
        intergroup_ms = intergroup;
    }

/** 
 *  @brief Blinks out a number up to 99999. Leading zeros are supressed by default. 
 *  @brief To show leading zeros set the width as required. 
 *  @param LED_pin the LED pin to blink
 *  @param active_Level HIGH or LOW to turn on LED
 *  @param number_to_blink integer between 0 and 99999
 *  @param width (optional 0 to 5) force number of digits displayed, 
 *   if omitted or 0 it will not display leading zeros
 */
    bool blink(int LED_pin, bool active_Level, int number_to_blink, int width = 0) {
        if (number_to_blink > 99999 || number_to_blink < 0) {
            return false;
        }
        _LED_pin = LED_pin;
        _LED_on = active_Level;

        if (!done(ms)) {
            return false;
        }

        if (arrayIndex == 0) {
            for (int ii = 1, divisor = 10000; ii < 10; ii += 2, divisor /= 10) {
                array[ii] = (number_to_blink / divisor) % 10;
            }

            offset = width == 0 ? 10 - (2 * ((int)log10(number_to_blink) + 1)) : 10 - 2 * width;
            arrayIndex = offset;
        }

        if (array[arrayIndex] < 0) {
            digitalWrite(_LED_pin, !_LED_on);
            ms = array[arrayIndex] == -2500 ? intergroup_ms : interdigit_gap_ms;
        } else {
            blinkCounter++;
            digitalWrite(_LED_pin, blinkCounter % 2 ? _LED_on : !_LED_on);

            if (array[arrayIndex] == 0) {
                digitalWrite(_LED_pin, _LED_on);
                ms = zero_digit_ms;
            } else if (blinkCounter < array[arrayIndex] * 2) {
                ms = blink_ms;
                return false;
            }
        }

        blinkCounter = 0;
        arrayIndex = (arrayIndex + 1) % 11;
        firstRun = arrayIndex == 0;

        return arrayIndex == 0;
    }
};

#endif
