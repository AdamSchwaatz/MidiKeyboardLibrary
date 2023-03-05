#include "Key.h"
#include "Arduino.h"

Key::Key(){
    kbyte = 0;
	kstate = IDLE;
	stateChanged = false;
	firstTime = 0;
	secondTime = 0;
	velocity = 0;
    diff = 0;
}

//constructor given byte
Key::Key(byte userByte) {
	kbyte = userByte;
	kcode = -1;
	kstate = IDLE;
	stateChanged = false;
	firstTime = 0;
	secondTime = 0;
	velocity = 0;
    diff = 0;
}

void Key::calculateVelocity(){
    //calculate time difference
    if(secondTime < firstTime){
        diff = (65535 - firstTime) + secondTime;
    }else{
        diff = secondTime - firstTime;
    }
    
    //calculate Velocity
    if(diff > 65){
        velocity = 5;
    }else{
        velocity = map(diff,3,65,127,5);
        if(velocity > 127) velocity = 127;
    }
}