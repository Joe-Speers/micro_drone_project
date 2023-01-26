#include "src/include/imu.h"
#include "src/include/comms.h"

IMU imu;
Comms comms;

void setup(){
    
    if(comms.CommsSetup()==0){
        Serial.println("COMMS OK");
    } else {
        Serial.println("COMMS FAILED TO INITILISE");
    }

    if(imu.IMUSetup()==0){
        Serial.println("IMU OK");
    } else {
        Serial.println("IMU FAILED TO INITILISE");
    }

    
}

void loop(){
    if(!imu.ReadAcc()){
        comms.Send("IMU read error");
    } else {
        comms.Send("X:"+String(imu.acc[0]));
        comms.Send("Y:"+String(imu.acc[1]));
        comms.Send("Z:"+String(imu.acc[2]));
    }
    delay(16);
}