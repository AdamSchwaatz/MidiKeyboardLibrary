/*
	Buttons - a small library for Arduino to handle button debouncing
	
	MIT licensed.
*/

#include "Buttons.h"
#include <Arduino.h>

Buttons::Buttons(uint8_t pin)
:  _pin(pin)
,  _delay(500)
,  _state(HIGH)
,  _ignore_until(0)
,  _has_changed(false)
{
}

void Buttons::begin()
{
	pinMode(_pin, INPUT_PULLUP);
}

// 
// public methods
// 

bool Buttons::read()
{
	// ignore pin changes until after this delay time
	if (_ignore_until > millis())
	{
		// ignore any changes during this period
	}
	
	// pin has changed 
	else if (digitalRead(_pin) != _state)
	{
		_ignore_until = millis() + _delay;
		_state = !_state;
		_has_changed = true;
	}
	
	return _state;
}

// has the button been toggled from on -> off, or vice versa
bool Buttons::toggled()
{
	read();
	return has_changed();
}

// mostly internal, tells you if a button has changed after calling the read() function
bool Buttons::has_changed()
{
	if (_has_changed == true)
	{
		_has_changed = false;
		return true;
	}
	return false;
}

// has the button gone from off -> on
bool Buttons::pressed()
{
	if (read() == PRESSED && has_changed() == true)
		return true;
	else
		return false;
}

// has the button gone from on -> off
bool Buttons::released()
{
	if (read() == RELEASED && has_changed() == true)
		return true;
	else
		return false;
}
