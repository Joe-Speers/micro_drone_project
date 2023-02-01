#ifndef SIMULATION
#include "include/imu.h"
#include "LSM6DS3.h"
#include "Wire.h"
#include "include/util.h"
#include <nrf.h>
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
    myIMU.settings.gyroSampleRate = 416;//416 is perfect for 300hz
    myIMU.settings.accelSampleRate = 208;//208 is perfecr for removing noise
    myIMU.settings.accelBandWidth = 50;//50 is best
    myIMU.settings.gyroBandWidth = 400;//does nothing
    myIMU.settings.fifoModeWord = 0;
    myIMU.settings.gyroFifoEnabled = 0;
    myIMU.settings.accelFifoEnabled = 0;
    
    if (myIMU.begin() != 0) return false;
    
    //NRF_TWIM0->FREQUENCY = TWIM_FREQUENCY_FREQUENCY_K400;
    //NRF_TWIM0->ENABLE = (TWIM_ENABLE_ENABLE_Enabled << TWIM_ENABLE_ENABLE_Pos);
    Wire.setClock(400000);
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
    readSensorRegisters();
    //Acelerometer axis X
    //acc[0]=myIMU.readFloatAccelX();

    //Acelerometer axis Y
    //acc[1]=myIMU.readFloatAccelY();

    //Acelerometer axis Z
    //acc[2]=myIMU.readFloatAccelZ();

    //gyroscope
    //gyro[0]=myIMU.readFloatGyroX();
    //gyro[1]=myIMU.readFloatGyroY();
    //gyro[2]=myIMU.readFloatGyroZ();
    if(errors!=0) return false;
    return true;
}

void IMU::readSensorRegisters() {
    uint8_t myBuffer[12];
    status_t returnError = myIMU.readRegisterRegion(myBuffer, LSM6DS3_ACC_GYRO_OUTX_L_G, 12);  //Does memory transfer
    int16_t sensor_data[6];
    for(int i=0;i<6;i++){
        sensor_data[i]=(int16_t)myBuffer[i*2] | int16_t(myBuffer[(i*2)+1] << 8);
    }
    gyro[0]=myIMU.calcGyro(sensor_data[0]);
    gyro[1]=myIMU.calcGyro(sensor_data[1]);
    gyro[2]=myIMU.calcGyro(sensor_data[2]);
    acc[0]=myIMU.calcAccel(sensor_data[3]);
    acc[1]=myIMU.calcAccel(sensor_data[4]);
    acc[2]=myIMU.calcAccel(sensor_data[5]);
}
#endif