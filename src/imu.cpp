#include "include/imu.h"
#include "LSM6DS3.h"
#include "Wire.h"
LSM6DS3 myIMU(I2C_MODE, 0x6A);    //I2C device address 0x6A
bool is_setup=false;
bool IMU::IMUSetup(){
    is_setup=false;
    acc[0]=0;
    acc[1]=0;
    acc[2]=0;
    myIMU.settings.gyroSampleRate = 1666;
    if (myIMU.begin() != 0) return false;
    is_setup=true;
    return true;
}
bool IMU::ReadAcc(){
    if(!is_setup) return false;

    uint16_t errors=0;
    //Acelerometer axis X
    acc[0]=myIMU.readFloatAccelX();

    //Acelerometer axis Y
    acc[1]=myIMU.readFloatAccelY();

    //Acelerometer axis Z
    acc[2]=myIMU.readFloatAccelZ();
    if(errors!=0) return false;
    return true;
}
void IMU::ReadGyro(){
    if(!is_setup) return;
}