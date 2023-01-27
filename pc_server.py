import asyncio
import time
from bleak import BleakClient

address = "FB:5B:53:8A:0F:AE"
CONSOLE_UUID = "0000aaaa-0000-1000-8000-00805f9b34fb"
CONTROL_UUID = "0000bbbb-0000-1000-8000-00805f9b34fb"
control_settings = [0, 255, 255, 0, 0]


def console_callback(sender, data):
    print("recieved: {0}".format("".join(map(chr, data))))

async def main(address):
    async with BleakClient(address) as client:
        #await client.connect(timeout=15)
        descriptors=client.services.descriptors
        for descriptor in descriptors.values():
            print(descriptor.description)
            print(descriptor.characteristic_uuid)
        await client.start_notify(CONSOLE_UUID, console_callback)
        while True:
            await asyncio.sleep(0.5)
            control_settings[0]+=1
            if(control_settings[0]>255): control_settings[0]=0
            await client.write_gatt_char(CONTROL_UUID,bytes(control_settings),True)
        #    console=await client.read_gatt_char(CONSOLE_UUID)
            
        

asyncio.run(main(address))
while(False):
    time.sleep(1)