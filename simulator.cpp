#ifdef SIMULATION
#include <sys/timeb.h>
#include <cstring>
#include <iostream>
#include <iomanip>

#include "simulator.h"//must come first

#include "drone_init.ino"


float motor_output[4];
float true_gyro[3];
float true_acc[3];

#define MOTOR_FORCE 0.1
#define MOTOR_DISTANCE_FROM_CENTRE 0.05
#define MASS_MOMENT_INTERTIA 0.0004
#define dt 0.001

int main(){
    
    initialize_mock_arduino();
    setup();
    true_gyro[0]=-100;
    true_gyro[1]=0;
    true_gyro[2]=0;
    true_acc[0]=0;
    true_acc[1]=0;
    true_acc[2]=1;
    comms.controlin[0]=50;
    comms.controlin[1]=20;
    comms.controlin[2]=20;
    while(true){
        loop();
        //physics
        float x_acc=(motor_output[FRmotpin]+motor_output[BRmotpin]-motor_output[FLmotpin]-motor_output[BLmotpin])*MOTOR_FORCE*MOTOR_DISTANCE_FROM_CENTRE/MASS_MOMENT_INTERTIA;
        true_gyro[0]+=x_acc*dt;
        //mock imu
        imu.imu_record_step++;
        if(imu.imu_record_step>=RECORD_INTERVAL){
            imu.imu_record_step=0;
            imu.acc+=3;
            imu.gyro+=3;
            if(imu.acc>=imu.recording_acc+RECORD_LENGTH*3)imu.acc=imu.recording_acc;
            if(imu.gyro>=imu.recording_gyro+RECORD_LENGTH*3)imu.gyro=imu.recording_gyro;
        }
        //Acelerometer axis X
        imu.acc[0]=true_acc[0];
        //Acelerometer axis Y
        imu.acc[1]=true_acc[1];
        //Acelerometer axis Z
        imu.acc[2]=true_acc[2];
        //gyroscope
        imu.gyro[0]=true_gyro[0];
        imu.gyro[1]=true_gyro[1];
        imu.gyro[2]=true_gyro[2];
    }
    return 0;
}



timeb t_start;
unsigned long millis() {
  timeb t_now;
  ftime(&t_now);
  return (t_now.time  - t_start.time) * 1000 + (t_now.millitm - t_start.millitm);
}

void delay( unsigned long ms ) {
  unsigned long start = millis();
  while(millis() - start < ms){}
}

void initialize_mock_arduino() {
  ftime(&t_start);
}


#endif
