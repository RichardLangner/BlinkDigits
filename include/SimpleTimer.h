/*SimpleTimer v2.2,  30 April 2023
* By Richard Langner, Sheffield, UK
* A light-weight non-blocking interrupt-free timer
* with millisecond accuracy.
*
* INITIALISE
* 		SimpleTimer timer1;
* 
* AUTO-REPEAT every 500ms until disabled
* 		if(timer1.done(500, 0){...}
*		the second parameter is optional, so
*			if(timer1.done(500){...}
* 
* AUTO-REPEAT every 500ms, do this 10 times
* 		if(timer1.done(500, 10){...}
*
* SINGLE-SHOT after 500ms, do it once
* 		if(timer1.done(500, 1){...}
*
* ENABLE
* 		timer1.enabled(true);
* 		timer1.enabled(false);
* 		if(timer1.isEnabled()){...}
* 	NOTE .enabled does not actually start the timer, but
*			allows the timer to start from the next if(timer1.done(....
* 
* TIME ELAPSED since a timing period began
* 		unsigned long t = timer1.elapsed();
*
*	NEW feature in v2.2
*	Dymanically change the 'done' timeout during a timing period e.g.
*			if(timer1.done(5000)){...};
*			if(timer1.done(200)){...}
*			will time out at 200ms. Previously it would have ignored 
*			the 200ms until 5000ms expired.
*/
#ifndef SIMPLE_TIMER
#define SIMPLE_TIMER
#include <Arduino.h>

/** Timer with millisecond accuracy */
class SimpleTimer	
{
//------------------ Private ----------------
private:
	unsigned long _setMillis=0, _prevMillis = 0;
	int  _eventCount;
	bool _enabled=true;
	bool timedOut(unsigned long u){_setMillis=u; return (millis() - _prevMillis >= _setMillis);}
	void _start(unsigned long u){	_setMillis=u; _prevMillis=millis();}
	bool firstRun=true;

//------------------ Public -----------------
public:
// General purpose variables, free to use
int				intA, 	intB;
bool			boolA, 	boolB;
unsigned long	longA,	longB;
virtual ~ SimpleTimer(){}

/** @return true if the timing period has elapsed
*	@param msecs timing period in milliseconds
*	@param cycles (optional) number of cycles required (0 means continuous)*/
bool done(unsigned long msecs, int cycles=0){
	if(!_enabled){return false;}				// Not valid timeOut
	if(!timedOut(msecs)){return false;}				// Not valid timeOut
	if(cycles==0){_start(msecs);return true;}	// Auto restart
	if(firstRun){_start(msecs); firstRun=false; return false;}
	if(cycles > _eventCount++ ){_start(msecs);return true;}	// Valid timeOut
	_enabled=false;	
	firstRun=true;								// Sleep now ...
	return false;
}
/**	@return 'true' if the timer is enabled */
bool enabled(){return _enabled;}

/** @param enabled 'true' enables, 'false' disables the timer */
void enabled(bool enabled=true){_enabled=enabled; _eventCount=0; firstRun=true;}

/**	@return milliseconds since timing period began, 0 if disabled or timed out */
unsigned long elapsed(){
	if(timedOut(_setMillis) || !_enabled){return 0;} else {return millis() - _prevMillis;}}

};
#endif