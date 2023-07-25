# VoxelHap
This repository is for getting started with VoxelHap 

In this repository you will find step by step guide on how to set up Voxelhap base cubes with unity and establish communication. 
 The voxel hap base cubes communicte based on Master - slave architecure. Master(Wemos D1 mini) is connected to Unity via serial port and slaves(VoxelHap cubes- built using Wemos D1 mini) communicate to master wirelessly using PainlessMesh.  

Installing the dependencies: 
1. Voxelhap cubes have a capcitive touch sensor MPR121. Download Adafruit_MPR121 libray from Arduino.
   https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial/wiring
   
2. Voxelhap cubes also need FastLED library to manage LEDs on board. Download FastLED library from Arduino.
   https://fastled.io/

   

Step 1: 
Download Painlessmesh library, specifically namedmesh example.
https://gitlab.com/painlessMesh/painlessMesh/-/tree/develop/examples/namedMesh?ref_type=heads

Step2 : 
