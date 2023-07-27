# VoxelHap
This repository is for getting started with VoxelHap 
In this repository you will find step by step guide on how to set up Voxelhap base cube with unity and establish communication. 
 
The voxel hap base cubes communicte based on Master - slave architecure. Master(Wemos D1 mini) is connected to Unity via serial port and slaves(VoxelHap cubes- built using Wemos D1 mini) communicate to master wirelessly using PainlessMesh.  

This repository covers: 
1. Establishiong bidirection connection between Master and base cube
2. EStablishing connection between Unity and Master

![Connection_overview](https://github.com/kirangani/VoxelHap/assets/17798189/2c58aeb7-d2fb-4078-8863-977716c854b9)

Firmware folder contains the arduino files, Master.ino should be uploaded onto the masetr Wemos D1 mini and Slave_VoxelHap_Cubes.ino need to be uploaded on the VoxelHap base cubes. 

Installing the dependencies: 
1. Voxelhap cubes have a capcitive touch sensor MPR121. Download Adafruit_MPR121 libray from Arduino IDE.
   https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial/wiring
   
2. Voxelhap cubes also need FastLED library to manage LEDs on board. Download FastLED library from Arduino IDE.
   https://fastled.io/

4. Voxelhap cubes also need ArduinoJson library to send JSON file to the master. SO download ArduinoJson library from Arduino IDE.
   https://arduinojson.org/
   
5. For master - slave communication between cubes and the master Wemos D1 we use painlessmesh library.
   Download Painlessmesh library from Arduino IDE, specifically namedmesh example.
   https://gitlab.com/painlessMesh/painlessMesh/-/tree/develop/examples/namedMesh?ref_type=heads

For Unity- Master communication establish Serial communication and import the unity package (with .Net4.x frame work in player settings). 
