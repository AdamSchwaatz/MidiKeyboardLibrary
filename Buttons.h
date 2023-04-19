/*
	Buttons - a small library for Arduino to handle button debouncing
	
	MIT licensed.
*/

#ifndef Buttons_h
#define Buttons_h
#include "Arduino.h"

class Buttons
{
	public:
		Buttons(uint8_t pin);
		void begin();
		bool read();
		bool toggled();
		bool pressed();
		bool released();
		bool has_changed();
		
		const static bool PRESSED = LOW;
		const static bool RELEASED = HIGH;
	
	private:
		uint8_t  _pin;
		uint16_t _delay;
		bool     _state;
		bool     _has_changed;
		uint32_t _ignore_until;
};

#endif
