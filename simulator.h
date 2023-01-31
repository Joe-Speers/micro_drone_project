#pragma once
#include <iostream>
#include "src/include/util.h"

extern float motor_output[4];
unsigned long millis();
void delay( unsigned long ms );
void initialize_mock_arduino();

struct {
    void begin(int) {}
    template<typename T> void print(T x) { std::cout << x; }
    template<typename T> void println(T x) { std::cout << "println: " << x << std::endl; }
} Serial;

struct {
    int CommsSetup() { return 0; }
    template<typename T> void Send(T x) { std::cout << "BT Coms: " << x << std::endl; }
    uint8_t controlin[5];
    void UpdateComms() {};
} comms;

struct {
    int IMUSetup() { return 0; }
    bool ReadAcc() {return true;};
    float recording_acc[RECORD_LENGTH*3];
    float* acc=recording_acc;
    float recording_gyro[RECORD_LENGTH*3];
    float* gyro=recording_gyro;
    int imu_record_step=0;
} imu;

static void setPWM(int duffPWMobject, int motor_pin, int frequency, float duty_cycle) {
    motor_output[motor_pin]=duty_cycle;
    
};

static void pinMode(int motor_pin, int pin_type) {};

template<typename T> std::string String(T x){return std::to_string(x);};