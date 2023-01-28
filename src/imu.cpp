#include "include/imu.h"
#include "LSM6DS3.h"
#include "Wire.h"
#define RECORD_INTERVAL 1
LSM6DS3 myIMU(I2C_MODE, 0x6A);    //I2C device address 0x6A
bool is_setup=false;
int record_step=0;

bool IMU::IMUSetup(){
    is_setup=false;
    acc[0]=0;
    acc[1]=0;
    acc[2]=0;
    gyro[0]=0;
    gyro[1]=0;
    gyro[2]=0;
    myIMU.settings.gyroSampleRate = 1666;
    myIMU.settings.accelSampleRate = 1666;
    myIMU.settings.accelBandWidth = 400;
    myIMU.settings.gyroBandWidth = 400;
    myIMU.settings.fifoModeWord = 0;
    myIMU.settings.gyroFifoEnabled = 0;
    myIMU.settings.accelFifoEnabled = 0;
    if (myIMU.begin() != 0) return false;
    is_setup=true;
    return true;
}
bool IMU::ReadAcc(){
    if(!is_setup) return false;

    uint16_t errors=0;
    record_step++;
    if(record_step>=RECORD_INTERVAL){
        record_step=0;
        acc+=3;
        gyro+=3;
        if(acc>=recording_acc+RECORD_LENGTH*3)acc=recording_acc;
        if(gyro>=recording_gyro+RECORD_LENGTH*3)gyro=recording_gyro;
    }
    //Acelerometer axis X
    acc[0]=myIMU.readFloatAccelX();

    //Acelerometer axis Y
    acc[1]=myIMU.readFloatAccelY();

    //Acelerometer axis Z
    acc[2]=myIMU.readFloatAccelZ();

    //gyroscope
    gyro[0]=myIMU.readFloatGyroX();
    gyro[1]=myIMU.readFloatGyroY();
    gyro[2]=myIMU.readFloatGyroZ();
    if(errors!=0) return false;
    return true;
}
void IMU::ReadGyro(){
    if(!is_setup) return;
}