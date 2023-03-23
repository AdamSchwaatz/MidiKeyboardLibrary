#include "Keyboard.h"
// #include "Wire.h"
// #include "Adafruit_MCP23X17.h"

// Keyboard::Keyboard(byte *userKeymap, byte *row, byte *col, byte numRows, byte numCols){
//     rowPins = row;
//     colPins = col;
//     rows = numRows;
//     cols = numCols;
//     row = 0;

//     debounceTime = 20;
//     //begin(userKeymap);
    
//     currentTime = 0;

//     //set up the inputs and outputs
// 	// for (byte r = 0; r < rows*2; r++){
//     //     pin_mode(rowPins[r], INPUT);
// 	// }
// 	// for (byte c = 0; c < cols; c++){
// 	// 	pin_mode(colPins[c], OUTPUT);
// 	// 	pin_write(colPins[c], LOW);
// 	// }

    
    
// }

// void Keyboard::begin(byte *userKeymap){
//     Wire.begin();
//     keymap = userKeymap;
//     //loop through the columns
//     for(byte c = 0;c<cols;c++){
//         //loop through the rows
//         for(byte r = 0;r<rows;r++){
//             keys[r][c].kbyte = keymap[r * cols + c];
//             keys[r][c].kcode = r * cols + c;
//         }
//     }

//     Wire.beginTransmission(0x20);
//     Wire.write(0x00);
//     Wire.write(0x00);
//     Wire.endTransmission();
//     Wire.beginTransmission(0x20);
//     Wire.write(0x01);
//     Wire.write(0b11111100);
//     Wire.endTransmission();
// }
// //bitRead takes 4 microseconds
// //bitWrite takes 4 microseconds
// //pinread takes 492 microseconds
// //pinwrite takes 860 microseconds
// //current key loop takes 492
// //read gpioB takes 484 microseconds

// void Keyboard::updateKeys(){
   
//     //loop through the columns
//     for(byte c = 0;c<cols;c++){
//         //int testTime = millis();
//         //loop through the rows
//         //pin_write(colPins[c],HIGH);
//         pin_write(c,HIGH);
//         //row = mcp.readGPIOB();
//         Wire.beginTransmission(0x20);
//         Wire.write(0x13);
//         Wire.endTransmission();
//         Wire.requestFrom(0x20,1);;
//         byte rowInput=Wire.read();
    
//         Serial.println(rowInput);
//         for(byte r = 0;r<rows;r++){
//             currentTime = millis();
//             //check if the key has been pressed
//             if(!bitRead(pressed[r],c)){
//                 //If the key has not been pressed check first button
//                 //if the first button for a key is not pressed
//                 if(!bitRead(first[r],c)){
//                 //then check if it has been pressed
                    
//                     if(bitRead(row,(r*2)+1+2)){
//                     //if(pin_read(rowPins[(r*2)+1])){
//                         //update the timing and change the boolean
//                         keys[r][c].firstTime = currentTime;
//                         bitWrite(first[r],c,true);
//                     }
//                 }else{
//                     //this is if the first button has been pressed
//                     //if somehow the first button was pressed and never the second
//                     //then remove the first button press
//                     if((currentTime - keys[r][c].firstTime)>500){
//                         bitWrite(first[r],c,false);
//                     }

//                     //now we check the second button
//                     //if(bitRead(row,(r*2)+2)){
//                     if(pin_read(rowPins[r*2])){
//                         keys[r][c].secondTime = currentTime;
//                         bitWrite(second[r],c,true);

//                         //calculate velocity of the key press
//                         keys[r][c].calculateVelocity();
//                         //this is where we are going to send the midi
//                         //debugging print statements 
//                         Serial.print("First: ");
//                         Serial.print(keys[r][c].firstTime);
//                         Serial.print(" Second: ");
//                         Serial.print( keys[r][c].secondTime);
//                         Serial.print(" Difference: ");
//                         Serial.print( keys[r][c].diff);
//                         // Serial.print("Key: ");
//                         // Serial.print( keys[r][c].kbyte);
//                         // Serial.print(" Code: :");
//                         // Serial.print( keys[r][c].kcode);
//                         Serial.print(" Velocity: ");
//                         Serial.println( keys[r][c].velocity);

//                         //reset the values
//                         bitWrite(first[r],c,false);
//                         bitWrite(second[r],c,false);
//                         bitWrite(pressed[r],c,true);
//                     }
//                 }
//             }else{
//                 //check the debounce time
//                 if((currentTime-keys[r][c].firstTime) > debounceTime){
//                     //if the debounce time has passed
//                     //check if the key has been released
//                     //if(bitRead(row,(r*2)+1+2)){
//                     if(!pin_read(rowPins[(r*2)+1])){
//                         //this is when the key has been released
//                         //write the MIDI release here ACTION
//                         bitWrite(pressed[r],c,false);
//                     }
//                 }
//             }
//         }
//         //pin_write(colPins[c],LOW);
//         //Serial.println(millis() - testTime);
//     }
    
// }