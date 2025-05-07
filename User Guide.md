To use the shaker table, you must have the Arduino IDE installed, since the table is controlled via serial monitor. You can download it here https://www.arduino.cc/en/software/ 

Quick Video Demo
https://youtu.be/CGTB2_CrCpI

1. Connect the Arduino UNO via USB to your laptop

2. Launch the Arduino IDE

3. In tools, configure your COM port (will be different per device) and Arduino model (Arduino UNO)

4. In tools, select Serial Monitor

5. In the Serial Monitor, change the settings in the bottom to the following:

6. If everything was done correctly, you should see a menu to select the motion profile. Follow the guidelines below for Resonance control for best results


Simulation Parameters for Resonance: 

6hz or lower should have an amplitude of .01

7hz to 10hz should have an amplitude no larger than .008

Up to 15hz, .005 should be used, but the motion can get very violent. 

Not recommended to run above 15Hz, unless with very small amplitudes
