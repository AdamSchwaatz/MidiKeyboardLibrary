
typedef unsigned char byte;
typedef enum{IDLE,PRESSED,RELEASED} KeyState;
typedef unsigned int uint;

class Key{
public:
    byte kbyte;
    int kcode;
    KeyState kstate;
    bool stateChanged;
    uint firstTime;
    uint secondTime;
    int diff;
    byte velocity;

public:
    Key();
    Key(byte userByte);
    void calculateVelocity();
};