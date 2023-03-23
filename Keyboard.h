 #include "Key.h"
// #include "Adafruit_MCP23X17.h"

// #define LIST_MAX 20		// Max number of keys on the active list.
// #define MAPSIZE 3		// MAPSIZE is the number of rows (times 16 columns)
// #define makeKeymap(x) ((byte*)x)

// class Keyboard{
// public:

//     Keyboard(byte *userKeymap,byte *row, byte *col, byte numRows, byte numCols);
//     Adafruit_MCP23X17 mcp;
//     virtual void pin_mode(byte pinNum, byte mode) { mcp.pinMode(pinNum, mode); }
// 	virtual void pin_write(byte pinNum, boolean level) { 
//         byte num = 1;
//         if(pinNum<8){
//             num << pinNum;
//             Wire.beginTransmission(0x20);
//             Wire.write(0x12);
//             Wire.write(num);
//             Wire.endTransmission();
//         }else if(pinNum<16){
//             num << (pinNum - 8);
//             Wire.beginTransmission(0x20);
//             Wire.write(0x13);
//             Wire.write(num);
//             Wire.endTransmission();
//         }
//         //mcp.digitalWrite(pinNum, level);
//     }
// 	virtual int  pin_read(byte pinNum) { return mcp.digitalRead(pinNum); }

// private:
//     uint first[MAPSIZE];	// 10 row x 16 column array of bits.
// 	uint second[MAPSIZE];
//     uint pressed[MAPSIZE];
//     uint currentTime;
//     uint debounceTime;
//     Key keys[MAPSIZE][10];
//     byte row;

// public:
//     Key key[LIST_MAX];
// 	void updateKeys();
// 	void begin(byte *userKeymap);
// 	byte rows;
// 	byte cols;

//     byte *keymap;
//     byte *rowPins;
//     byte *colPins;
// };