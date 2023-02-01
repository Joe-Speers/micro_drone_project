
#include "util.h"
#include <stdint.h>
class IMU{
    public:
        float recording_acc[RECORD_LENGTH*3];
        float* acc=recording_acc;
        float recording_gyro[RECORD_LENGTH*3];
        float* gyro=recording_gyro;
        bool IMUSetup();
        bool ReadAcc();
    private:
        void readSensorRegisters();
};