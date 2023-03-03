# micro_drone_project
A personal project to build a <30g micro drone, code will be incomplete and experimental.

Based upon the Seeed Studio XIAO nRF52840 Sense, using the inbuilt IMU and bluetooth.
- Output to motors will be four PWM channels fed to four MOSFETS (homemade circuit)
- Battery is a 300mah, 3.8v LiPo
- Motors are 0615 brushed DC motors with 31mm quad props.
- Frame is 3D printed

## To run
- To run on the seeduino, open drone_init.ino in the Arduino IDE and upload
- To simulate on a PC, compile simulator.cpp using g++ with the args as in `tasks.json`. If using VSCode, just place this file into the `.vscode` folder and it will handle this for you when you click the play button!

