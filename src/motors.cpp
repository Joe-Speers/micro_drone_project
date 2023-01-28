#include "include/motors.h"
#define BLmotpin 3
#define BRmotpin 2
#define FLmotpin 0
#define FRmotpin 1

int BLmot=0;
int BRmot=0;
int FLmot=0;
int FRmot=0;

bool Motors::Setup(){
    return true;
    pinMode(BLmotpin, OUTPUT);
    pinMode(BRmotpin, OUTPUT);
    pinMode(FLmotpin, OUTPUT);
    pinMode(FRmotpin, OUTPUT);
}

bool Motors::NewSettings(int thrust,int k,float roll, float pitch){
    
    BLmot=thrust-pitch*k-roll*k;
    BRmot=thrust-pitch*k+roll*k;
    FLmot=thrust+pitch*k-roll*k;
    FRmot=thrust+pitch*k+roll*k;
    if(thrust==0){
        BLmot=0;
        BRmot=0;
        FLmot=0;
        FRmot=0;
    }
    if(BLmot>255)BLmot=255;
    if(BRmot>255)BRmot=255;
    if(FLmot>255)FLmot=255;
    if(FRmot>255)FRmot=255;
    if(BLmot<0)BLmot=0;
    if(BRmot<0)BRmot=0;
    if(FLmot<0)FLmot=0;
    if(FRmot<0)FRmot=0;
    analogWrite(BLmotpin, BLmot);
    analogWrite(BRmotpin, BRmot);
    analogWrite(FLmotpin, FLmot);
    analogWrite(FRmotpin, FRmot);
    return true;
}