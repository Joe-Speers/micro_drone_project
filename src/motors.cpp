#include "include/motors.h"
#include "include/util.h"
#ifndef SIMULATION
#include "nRF52_MBED_PWM.h"
mbed::PwmOut* BLpwm   = NULL;
mbed::PwmOut* BRpwm   = NULL;
mbed::PwmOut* FLpwm   = NULL;
mbed::PwmOut* FRpwm   = NULL;
#else
#include "../simulator.h"
int BLpwm   = 0;
int BRpwm   = 0;
int FLpwm   = 0;
int FRpwm   = 0;
#define OUTPUT 0
#endif

static int write_resolution = 8;
static int read_resolution = 10;



#define PWM_FREQUENCY 4000





bool Motors::Setup(){
    return true;
    pinMode(BLmotpin, OUTPUT);
    pinMode(BRmotpin, OUTPUT);
    pinMode(FLmotpin, OUTPUT);
    pinMode(FRmotpin, OUTPUT);
}

bool Motors::NewSettings(float BLmot,float BRmot,float FLmot,float FRmot){
    BLmot*=1.0;//adjust for different prop
    if(BLmot>100)BLmot=100;
    if(BRmot>100)BRmot=100;
    if(FLmot>100)FLmot=100;
    if(FRmot>100)FRmot=100;
    if(BLmot<0)BLmot=0;
    if(BRmot<0)BRmot=0;
    if(FLmot<0)FLmot=0;
    if(FRmot<0)FRmot=0;
    setPWM(BLpwm, BLmotpin, PWM_FREQUENCY, BLmot);
    setPWM(BRpwm, BRmotpin, PWM_FREQUENCY, BRmot);
    setPWM(FLpwm, FLmotpin, PWM_FREQUENCY, FLmot);
    setPWM(FRpwm, FRmotpin, PWM_FREQUENCY, FRmot);
    return true;
}