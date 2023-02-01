#ifndef SIMULATION
#include <Arduino.h>
#endif
class Comms{
    public:
    
        uint8_t controlin[5];
        bool CommsSetup();
        bool Send(String msg);
        bool UpdateComms(); //returns true if client has sent a message
};