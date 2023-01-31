#ifdef _WIN32
#include <sys/timeb.h>
#include <cstring>
#include <iostream>
#include <iomanip>

#include "simulator.h"//must come first

#include "drone_init.ino"




int main(){
    initialize_mock_arduino();
    setup();
    while(true){
        loop();
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
