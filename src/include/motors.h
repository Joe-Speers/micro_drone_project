#include <Arduino.h>
class Motors{
    public:
        bool Setup();
        bool NewSettings(int thrust,int k, float roll, float pitch);
};