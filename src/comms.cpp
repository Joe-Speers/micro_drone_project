#ifndef SIMULATION
#include "include/comms.h"
#include <ArduinoBLE.h>
BLEService droneService("180F");
byte consoleOutBuf[512];
BLECharacteristic consoleOut("AAAA", BLERead | BLENotify, 512,false);
BLECharacteristic controlIn("BBBB", BLEWrite | BLENotify, 512,false);
bool isBTConnected=false;


bool Comms::CommsSetup(){
    Serial.begin(115200);
    if (!BLE.begin()) return false;
    // set advertised local name and service UUID:
    BLE.setLocalName("joe_drone");
    BLE.setAdvertisedService(droneService);
    
    // add the characteristic to the service
    droneService.addCharacteristic(consoleOut);
    droneService.addCharacteristic(controlIn);
    // add service
    BLE.addService(droneService);
    controlin[0]=0;
    controlin[1]=0;
    // start advertising
    BLE.advertise();
    return true;
}

void Comms::UpdateComms(){
    BLEDevice central = BLE.central();
 
    // if a central is connected to peripheral:
    if (central.connected() && !isBTConnected) {
        isBTConnected=true;
        Comms::Send("BT Connected to: "+central.address());
    } else if(!central.connected()&& isBTConnected){
        isBTConnected=false;
         Comms::Send("BT disconnected");
    }
    if(central.connected()){
        if (controlIn.written()) {
            Serial.println("here");
            controlIn.readValue(controlin,5);
            Serial.println("recieved:"+String(controlin[2]));
        }
    }
}
bool Comms::Send(String msg){
    Serial.println(msg);
    msg.getBytes(consoleOutBuf, msg.length()+1);
    consoleOut.writeValue(consoleOutBuf,msg.length()+1);
    return true;
}
#endif