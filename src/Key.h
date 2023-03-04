
#ifndef KEY_H
#define KEY_H

// Arduino versioning.
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"	// for digitalRead, digitalWrite, etc
#else
#include "WProgram.h"
#endif

#define KEY_OPEN LOW
#define KEY_CLOSED HIGH

typedef unsigned int uint;
typedef enum{ IDLE, ONE_BUTTON, PRESSED, RELEASED} KeyState;

const byte NO_KEY = 0;
const int UNASSIGNED=-1;        // kcode is not assigned.

class Key {
public:
	// members
	byte kbyte;
	int kcode;
	KeyState kstate;
	boolean stateChanged;
	boolean first;
	boolean second;
	byte firstButtonTime;
	byte secondButtonTime;
	byte velocity;

public:
	// methods
	Key();
	Key(byte userByte);
	void calculateVelocity();
};

#endif

