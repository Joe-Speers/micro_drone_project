#include <Arduino.h>
class Comms{
    public:
        bool CommsSetup();
        bool Send(String msg);
        void UpdateComms();
};