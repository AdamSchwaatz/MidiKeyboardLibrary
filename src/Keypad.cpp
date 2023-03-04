#include "Keypad.h"
#include "Adafruit_MCP23X17.h"

// <<constructor>> Allows custom keymap, pin configuration, and keypad sizes.
Keypad::Keypad(byte *userKeymap, byte *row, byte *col, byte numRows, byte numCols) {
	rowPins = row;
	colPins = col;
	rows = numRows;
	cols = numCols;

	begin(userKeymap);
	setDebounceTime(20);
	setHoldTime(500);
	setScanTime(0);

	startTime = 0;
}

// Let the user define a keymap - assume the same row/column count as defined in constructor
void Keypad::begin(byte *userKeymap) {
    keymap = userKeymap;

	//set up the inputs and outputs
	for (byte r = 0; r < rows; r++){
		pin_mode(rowPins[r], INPUT);
	}
	for (byte c = 0; c < cols; c++){
		pin_mode(colPins[c], OUTPUT);
		pin_write(colPins[c], LOW);
	}
}

// Update the key list whenever the user presses, holds or releases a key.
bool Keypad::getKeys() {
	bool keyActivity = false;

	// Limit how often the keypad is scanned. This makes the loop() run 10 times as fast.
	if ( (millis()-startTime)>debounceTime ) {
		scanKeys();
		startTime = millis();
		keyActivity = updateList();
		
	}

	return keyActivity;
}

// Private : Hardware scan
void Keypad::scanKeys() {
	//updates the bitMap


	// bitMap stores ALL the keys that are being pressed.
	// for (byte c=0; c<cols; c++) {
	// 	//pin_mode(colPins[c],OUTPUT); I don't think this also needs to be here
	// 	pin_write(colPins[c], LOW);	// Begin column pulse output.
	// 	// if(scanTime > 0) { //add back if I see this issue coming up
	// 	// 	delay(scanTime);  // DO NOT REMOVE! Prevents problems with the Joyjoz music mat hack; https://github.com/Nullkraft/Keypad/pull/15
	// 	// }
	// 	for (byte r=0; r<rows; r++) {
	// 		bitWrite(bitMap[r], c, !pin_read(rowPins[r]));  // keypress is active low so invert to high.
	// 	}
	// 	// Set pin to high impedance input. Effectively ends column pulse.
	// 	pin_write(colPins[c],HIGH);
	// 	//pin_mode(colPins[c],INPUT); why?
	// }

	// bitMap stores ALL the keys that are being pressed.
	for (byte c = 0; c < cols; c++){
		// pin_mode(colPins[c],OUTPUT); I don't think this also needs to be here
		pin_write(colPins[c], HIGH); // Begin column pulse output.
		// if(scanTime > 0) { //add back if I see this issue coming up
		// 	delay(scanTime);  // DO NOT REMOVE!
		// }
		//delay(10);
		for (byte r = 0; r < rows; r++)
		{
			boolean bongo = pin_read(rowPins[r]);
			bitWrite(bitMap[r], c, bongo); // keypress is active high so don't invert
			if(bongo && !bitRead(bitMap2[r],c)){
				timing[r][c] = millis();
				bitWrite(bitMap2[r], c, HIGH);
			}
		}
		
		// Set pin to high impedance input. Effectively ends column pulse.
		pin_write(colPins[c], LOW);
		// pin_mode(colPins[c],INPUT); why?
	}
}

// Private
// Manage the list without rearranging the keys. Returns true if any keys on the list changed state.
bool Keypad::updateList() {
//actually updates the list


	bool anyActivity = false;

	for (byte i=0; i<LIST_MAX; i++) {
		// Delete any IDLE keys
		if (key[i].kstate==IDLE) {
			key[i].kbyte = NO_KEY;
			key[i].kcode = -1;
			key[i].stateChanged = false;
			key[i].firstButtonTime = 0;
			key[i].secondButtonTime = 0;
			key[i].first = false;
			key[i].second = false;
		}
		// Delete any ONE_BUTTON keys that have been there too long 
		if (key[i].kstate == ONE_BUTTON)
		{
			//int current = millis(); 
			if ((key[i].firstButtonTime > 0 && startTime - key[i].firstButtonTime > 250) || (key[i].secondButtonTime > 0 && startTime - key[i].secondButtonTime > 250)){
				key[i].kbyte = NO_KEY;
				key[i].kcode = -1;
				key[i].stateChanged = false;
				key[i].firstButtonTime = 0;
				key[i].secondButtonTime = 0;
				key[i].first = false;
				key[i].second = false;
			}
		}
	}

	// Add new keys to empty slots in the key list.
	for (byte r=0; r<rows/2; r++) {
		for (byte c=0; c<cols; c++) {
			boolean first = bitRead(bitMap[r*2], c);
			boolean second = bitRead(bitMap[(r*2) + 1], c);
			byte keyByte = keymap[r * cols + c];
			int keyCode = r * cols + c;
			int idx = findInList (keyCode);
			// Key is already on the list so set its next state.
			if (idx > -1)	{
				if(key[idx].kstate == ONE_BUTTON){
					if(key[idx].first && second){
						key[idx].secondButtonTime = timing[(r * 2) + 1][c];
						key[idx].second = true;
						bitWrite(bitMap2[(r * 2) + 1], c, LOW);
					}else if(key[idx].second && first){
						key[idx].firstButtonTime = timing[r * 2][c];
						key[idx].first = true;
						bitWrite(bitMap2[r * 2], c, LOW);
					}
				}
				nextKeyState(idx, first, second); //makes sure either the state is changed or the statechanged it set to false
			}
			// Key is NOT on the list so add it.
			if ((idx == -1) && (first||second)) {
				for (byte i=0; i<LIST_MAX; i++) {
					if (key[i].kbyte==NO_KEY) {		// Find an empty slot or don't add key to list.
						key[i].kbyte = keyByte;
						key[i].kcode = keyCode;
						key[i].kstate = IDLE;		// Keys NOT on the list have an initial state of IDLE.
						if(!key[i].first && first){
						// 	// Serial.print("first ");
						// 	// Serial.println(millis());}
							key[i].firstButtonTime = timing[r*2][c];
							key[i].first = true;
							bitWrite(bitMap2[r * 2], c, LOW);
						}
						if (!key[i].second && second){
							// Serial.print("second ");
							// Serial.println(millis());
							key[i].secondButtonTime = timing[(r * 2) + 1][c];
							key[i].second = true;
							bitWrite(bitMap2[(r * 2) + 1], c, LOW);
						}
						nextKeyState (i, first, second);
						break;	// Don't fill all the empty slots with the same key.
					}
				}
			}
		}
	}

	// Report if the user changed the state of any key.
	for (byte i=0; i<LIST_MAX; i++) {
		if (key[i].stateChanged) anyActivity = true;
	}

	return anyActivity;
}

// Private
// This function is a state machine but is also used for debouncing the keys.
void Keypad::nextKeyState(byte idx, boolean first, boolean second) {
	key[idx].stateChanged = false;

	switch (key[idx].kstate) {
		case IDLE: //first time in the list
			if (first&&second){
				transitionTo(idx, PRESSED);
				key[idx].calculateVelocity();
			} else if(first||second){
				transitionTo(idx,ONE_BUTTON);
			}
			break;
		case ONE_BUTTON:
			if (first && second){
				key[idx].secondButtonTime = millis();
				transitionTo(idx, PRESSED);
				key[idx].calculateVelocity();
			}
			break;
		case PRESSED:
			if (!first && !second) //wait for key to be released
				transitionTo (idx, RELEASED);
			break;
		case RELEASED:
			transitionTo (idx, IDLE);
			break;
	}
}

// Search by byte for a key in the list of active keys.
// Returns -1 if not found or the index into the list of active keys.
int Keypad::findInList (byte keyByte) {
	for (byte i=0; i<LIST_MAX; i++) {
		if (key[i].kbyte == keyByte) {
			return i;
		}
	}
	return -1;
}

// Search by code for a key in the list of active keys.
// Returns -1 if not found or the index into the list of active keys.
int Keypad::findInList (int keyCode) {
	for (byte i=0; i<LIST_MAX; i++) {
		if (key[i].kcode == keyCode) {
			return i;
		}
	}
	return -1;
}

// Minimum debounceTime is 1 mS. Any lower *will* slow down the loop().
void Keypad::setDebounceTime(uint debounce) {
	debounce<1 ? debounceTime=1 : debounceTime=debounce;
}

void Keypad::setHoldTime(uint hold) {
    holdTime = hold;
}

// Wait this many ms after setting the output pin before checking the input pins
void Keypad::setScanTime(uint scan) {
    scanTime = scan;
}

// Private
void Keypad::transitionTo(byte idx, KeyState nextState) {
	key[idx].kstate = nextState;
	key[idx].stateChanged = true;
}
