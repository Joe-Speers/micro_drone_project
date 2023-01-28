/*Todo 
- add yaw feedback loop
- add integral control
*/
#include "src/include/imu.h"
#include "src/include/comms.h"
#include "src/include/motors.h"
#include "src/include/util.h"
#include<cmath>
IMU imu;
Comms comms;
Motors motors;


void setup(){
    motors.Setup();
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
    if(!imu.ReadAcc()){
            //comms.Send("IMU read error");
    }
    if(i%10==0){
        comms.UpdateComms();
        
    }
    motors.NewSettings(comms.controlin[0],comms.controlin[1],-imu.gyro[1]/100,imu.gyro[0]/100);
    if(pow(imu.acc[0],2)+pow(imu.acc[1],2)+pow(imu.acc[2],2)>pow(3,2)){
        motors.NewSettings(0,0,0,0);
        
        comms.Send("ACCELEROMETER X:"+String(imu.acc[0])+", Y:"+String(imu.acc[1])+", Z:"+String(imu.acc[2]));
        comms.Send("GYRO X:"+String(imu.gyro[0])+", Y:"+String(imu.gyro[1])+", Z:"+String(imu.gyro[2]));
        comms.Send("DOWNLOAD");
        for(int j=0; j<RECORD_LENGTH; j++){
            imu.acc+=3;
            imu.gyro+=3;
            delay(1);
            comms.Send("A:"+String(j)+":"+String(imu.acc[0])+":"+String(imu.acc[1])+":"+String(imu.acc[2]));
            delay(1);
            comms.Send("G:"+String(j)+":"+String(imu.gyro[0])+":"+String(imu.gyro[1])+":"+String(imu.gyro[2]));
            if(imu.acc>=imu.recording_acc+RECORD_LENGTH*3) imu.acc=imu.recording_acc;
            if(imu.gyro>=imu.recording_gyro+RECORD_LENGTH*3) imu.gyro=imu.recording_gyro;
        }
        delay(10);
        comms.Send("DOWNLOAD_COMPLETE");
        comms.Send("DOWNLOAD_COMPLETE");
        comms.Send("DOWNLOAD_COMPLETE");
        for(int j=0; j<2000; j++){
            j=0;//lock in loop
            delay(10);
            comms.UpdateComms();
            imu.ReadAcc();
        }
        
    }
    //comms.Send("X:"+String(imu.acc[0]));
    //comms.Send("Y:"+String(imu.acc[1]));
    //comms.Send("Z:"+String(imu.acc[2]));
    //comms.Send("########"+String(i));
    i++;
    if(i>10000000) i=0;
    delay(1);
}