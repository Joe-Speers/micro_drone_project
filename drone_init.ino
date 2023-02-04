/*Todo 
- add yaw feedback loop
- add integral control
*/

#ifdef SIMULATION
//simulation mode
#include "simulator.h"
#else
#include "src/include/comms.h"
#include "src/include/imu.h"
//normal mode
#endif
#include "src/include/motors.h"
#include "src/include/util.h"
#include<cmath>

Motors motors;
#ifndef SIMULATION
IMU imu;
Comms comms;
#endif


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
bool step=false;
float x_integral=0;
float y_integral=0;
float BLmot=0;
float BRmot=0;
float FLmot=0;
float FRmot=0;
float dt=0;
void loop(){
    dt=0.003;
    if(!imu.ReadAcc()){
            //comms.Send("IMU read error");
    }
    if(i%10==0){
        if(comms.UpdateComms()){
            x_integral=0;
            y_integral=0;
        }
        
    }
    if(i%100==0){
        Serial.println(i);
    }
    if(i%100==0 && false){
        comms.Send("A");
        comms.Send("AX:"+String(imu.acc[0]));
        comms.Send("AY:"+String(imu.acc[1]));
        comms.Send("AZ:"+String(imu.acc[2]));
        comms.Send("G");
        comms.Send("GX:"+String(imu.gyro[0]));
        comms.Send("GY:"+String(imu.gyro[1]));
        comms.Send("GZ:"+String(imu.gyro[2]));
    }
    float thrust=comms.controlin[0];
    float ks=float(comms.controlin[1])/10.0;
    
    float kp=comms.controlin[2];
    float ki=float(comms.controlin[3])/10.0;
    float roll=kp*(-imu.acc[1]*10)+ks*(-imu.gyro[0]/100)+ki*(-x_integral/10);
    float pitch=kp*(imu.acc[0]*10)+ks*(-imu.gyro[1]/100)+ki*(-y_integral/10);
    x_integral+=imu.gyro[0]*dt;
    y_integral+=imu.gyro[1]*dt;
    float yaw=(-imu.gyro[2]/100)*float(comms.controlin[4])/10;
    BLmot=thrust+yaw-pitch-roll;
    BRmot=thrust-yaw-pitch+roll;
    FLmot=thrust-yaw+pitch-roll;
    FRmot=thrust+yaw+pitch+roll;
    if(thrust==0){
        BLmot=0;
        BRmot=0;
        FLmot=0;
        FRmot=0;
    }
    motors.NewSettings(BLmot,BRmot,FLmot,FRmot);
    //if(imu.gyro[0]<-500){
    //    step=true;
    //}
    //if(!step){
    //    motors.NewSettings(comms.controlin[0],50,0,0);
    //} else{
    //    motors.NewSettings(comms.controlin[0],50,0,-500);
    //}
    
    //if(pow(imu.acc[0],2)+pow(imu.acc[1],2)+pow(imu.acc[2],2)>pow(4,2)){
    if(imu.acc[2]<-0.3){
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
        while(true){//loop until new startup command recieved
            delay(10);
            if(comms.UpdateComms()){
                x_integral=0;
                y_integral=0;
                break;
            }
            imu.ReadAcc();
        }
        
    }
    
    //comms.Send("########"+String(i));
    i++;
    if(i>10000000) i=0;
    //delay(1);
}