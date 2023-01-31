#ifndef SIMULATION
#include <Arduino.h>
#endif
class Motors{
    public:
        bool Setup();
        bool NewSettings(float thrust,float k, float roll, float pitch);
    private:
        void pwm_set(pin_size_t pin, int val,int frequency);
};