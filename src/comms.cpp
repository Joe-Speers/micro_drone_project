#include "include/comms.h"

bool Comms::CommsSetup(){
    Serial.begin(57600);
    return true;
}

bool Comms::Send(String msg){
    Serial.println(msg);
    return true;
}