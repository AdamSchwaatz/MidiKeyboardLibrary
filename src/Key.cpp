#include "Key.h"
#include "Arduino.h"

// default constructor
Key::Key() {
	kbyte = NO_KEY;
	kstate = IDLE;
	stateChanged = false;
	firstButtonTime = 0;
	secondButtonTime = 0;
	first = false;
	second = false;
	velocity = 0;
}

// constructor
Key::Key(byte userByte) {
	kbyte = userByte;
	kcode = UNASSIGNED;
	kstate = IDLE;
	stateChanged = false;
	firstButtonTime = 0;
	secondButtonTime = 0;
	first = false;
	second = false;
	velocity = 0;
}

void Key::calculateVelocity(){
	//velocity = pow(M_E,((abs(firstButtonTime - secondButtonTime)/50)*97)+30);
	velocity = map(abs(firstButtonTime - secondButtonTime),0,100,127,0); 
	//If above doesn't work try this
}


