Firmware code for connecting cubes: Based on master slave architecture. All the cubes send data to the master server.

Mesh_demo_server is the master server here. 

We have to assign the physical id of each cube in the masetr server as Cube1, Cube2 ..... 

Every time a cube connected to the server, server sends connected message back to the cube and cube can start sending
sensor info to the server. 

Every tim there is a connection between two cubes, server sends messages to the respective cubes to change the color/to 
turn off the LEDs on the side. 
  


