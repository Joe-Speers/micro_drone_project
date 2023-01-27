#include "src/include/imu.h"
#include "src/include/comms.h"

IMU imu;
Comms comms;

void setup(){
    
    if(comms.CommsSetup()==0){
        Serial.println("COMMS OK");
    } else {
        Serial.println("COMMS FAILED TO INITIALISE");
    }

    if(imu.IMUSetup()==0){
        Serial.println("IMU OK");
    } else {
        Serial.println("IMU FAILED TO INITIALISE");
    }

    
}
int i=0;
void loop(){
    comms.UpdateComms();
    if(!imu.ReadAcc()){
        comms.Send("IMU read error");
    }
    //comms.Send("X:"+String(imu.acc[0]));
    //comms.Send("Y:"+String(imu.acc[1]));
    //comms.Send("Z:"+String(imu.acc[2]));
    //comms.Send("########"+String(i));
    i++;
    //delay(20);
}