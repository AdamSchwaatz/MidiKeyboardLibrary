#ifndef KEYPAD_H
#define KEYPAD_H

#include "Key.h"
#include "Adafruit_MCP23X17.h"

// Arduino versioning.
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

typedef unsigned int uint;
typedef unsigned long ulong;

#define LIST_MAX 20		// Max number of keys on the active list.
#define MAPSIZE 6		// MAPSIZE is the number of rows (times 16 columns)
#define makeKeymap(x) ((byte*)x)

//class Keypad : public Key, public HAL_obj {
class Keypad : public Key {
public:

	Keypad(byte *userKeymap, byte *row, byte *col, byte numRows, byte numCols);
	Adafruit_MCP23X17 mcp;
	virtual void pin_mode(byte pinNum, byte mode) { mcp.pinMode(pinNum, mode); }
	virtual void pin_write(byte pinNum, boolean level) { 
		mcp.digitalWrite(pinNum, level); 
		//Serial.print(pinNum);
		//Serial.println(level);
		}
	virtual int  pin_read(byte pinNum) { return mcp.digitalRead(pinNum); }

private:
	uint bitMap[MAPSIZE];	// 10 row x 16 column array of bits. Except Due which has 32 columns.
	uint bitMap2[MAPSIZE];

public:
	Key key[LIST_MAX];
	bool getKeys();
	void begin(byte *userKeymap);
	void setDebounceTime(uint);
	void setHoldTime(uint);
	void setScanTime(uint);
	int findInList(byte keyByte);
	int findInList(int keyCode);
	byte rows;
	byte cols;
	byte timing[6][10];

public:
	unsigned long startTime;
	byte *keymap;
    byte *rowPins;
    byte *colPins;
	uint debounceTime;
	uint holdTime;
	uint scanTime;
	unsigned long holdTimer;
	bool single_key;

	void scanKeys();
	bool updateList();
	void nextKeyState(byte n, boolean first, boolean second);
	void transitionTo(byte n, KeyState nextState);
};

#endif
