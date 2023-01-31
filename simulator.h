#pragma once
#define SIMULATION
#include <iostream>

unsigned long millis();
void delay( unsigned long ms );
void initialize_mock_arduino();

struct {
    void begin(int) {}
    template<typename T> void print(T x) { cout << x; }
    template<typename T> void println(T x) { cout << x << endl; }
} Serial;
