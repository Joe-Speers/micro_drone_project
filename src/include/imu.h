
#include <stdint.h>
class IMU{
    public:
        float acc[3];
        float gyro[3];
        bool IMUSetup();
        bool ReadAcc();
        void ReadGyro();
};