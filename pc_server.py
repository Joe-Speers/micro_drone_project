import asyncio
import time
from bleak import BleakClient
import matplotlib.pyplot as plt
import numpy as np

address = "FB:5B:53:8A:0F:AE"
CONSOLE_UUID = "0000aaaa-0000-1000-8000-00805f9b34fb"
CONTROL_UUID = "0000bbbb-0000-1000-8000-00805f9b34fb"
control_settings = [0, 255, 255, 0, 0]
control_settings[0]=5    #thrust
control_settings[1]=20   #k val
control_settings[2]=40   #kp percentage

running=True
downloadmode=False
downloadgyro=[]
downloadacc=[]
data_index=0
def console_callback(sender, data):
    global running
    global downloadmode
    global data_index
    
    msg=str(format("".join(map(chr, data[0:-1])))).strip()
    if(msg=="DOWNLOAD"): 
        print("Downloading data")
        downloadmode=True
        data_index=0
        return
    if(msg=="DOWNLOAD_COMPLETE" and downloadmode): 
        print("Download Complete")
        downloadmode=False
        running=False
        data_index=0

        x=[item[0] for item in downloadgyro]
        gyro_x = [item[1][0] for item in downloadgyro]
        gyro_y = [item[1][1] for item in downloadgyro]
        gyro_z = [item[1][2] for item in downloadgyro]
        plt.plot(x,gyro_x,label = "X")
        plt.plot(x,gyro_y,label = "Y")
        plt.plot(x,gyro_z,label = "Z")
        plt.legend()
        plt.ylabel('gyroscope')
        plt.show()

        x=[item[0] for item in downloadacc]
        acc_x = [item[1][0] for item in downloadacc]
        acc_y = [item[1][1] for item in downloadacc]
        acc_z = [item[1][2] for item in downloadacc]
        plt.plot(x,acc_x,label = "X")
        plt.plot(x,acc_y,label = "Y")
        plt.plot(x,acc_z,label = "Z")
        plt.legend()
        plt.ylabel('accelerometer')
        plt.show()

        
        return
    if(downloadmode):
        items=msg.split(":")
        if(items[0]=="A"):
            downloadacc.append((float(items[1]),(float(items[2]),float(items[3]),float(items[4]))))
        if(items[0]=="G"):
            downloadgyro.append((float(items[1]),(float(items[2]),float(items[3]),float(items[4]))))
            data_index+=1
        print("downloading: "+str(data_index/10.0)+"%")
        return
    print("recieved: '"+msg+"'")

async def main(address):
    async with BleakClient(address) as client:
        #await client.connect(timeout=15)
        descriptors=client.services.descriptors
        for descriptor in descriptors.values():
            print(descriptor.description)
            print(descriptor.characteristic_uuid)
        await client.start_notify(CONSOLE_UUID, console_callback)
        
        await client.write_gatt_char(CONTROL_UUID,bytes(control_settings),True)
        while running:
            await asyncio.sleep(0.1)
            #await client.write_gatt_char(CONTROL_UUID,bytes(control_settings),True)
            #console=await client.read_gatt_char(CONSOLE_UUID)
            
        

asyncio.run(main(address))
while(False):
    time.sleep(1)