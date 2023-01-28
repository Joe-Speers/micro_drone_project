#include <Arduino.h>
class Comms{
    public:
    
        uint8_t controlin[5];
        bool CommsSetup();
        bool Send(String msg);
        void UpdateComms();
};