To use the shaker table, you must have the Arduino IDE installed, since the table is controlled via serial monitor. You can download it here https://www.arduino.cc/en/software/ 

Quick Video Demo
https://youtu.be/CGTB2_CrCpI

1. Connect the Arduino UNO via USB to your laptop

![20250507_115115](https://github.com/user-attachments/assets/3b5f4d24-c6dc-471a-9b7d-f7e1b5d895d0)


2. Launch the Arduino IDE

3. In tools, configure your COM port (will be different per device) and Arduino model (Arduino UNO)

![image](https://github.com/user-attachments/assets/120ecc5c-50ba-45e4-8c71-a77b4e635a69)


4. In tools, select Serial Monitor

![image](https://github.com/user-attachments/assets/98e00161-314a-4763-9051-0c1ad5198e81)


6. In the Serial Monitor, change the settings in the bottom to the following:

![image](https://github.com/user-attachments/assets/2f43dd06-98dc-4236-ad2f-08a1f0f7fd8d)


6. If everything was done correctly, you should see a menu to select the motion profile. Follow the guidelines below for Resonance control for best results

![main menu](https://github.com/user-attachments/assets/0ac00f01-8672-4730-9708-f146222325a5)


Simulation Parameters for Resonance: 

6hz or lower should have an amplitude of .01

7hz to 10hz should have an amplitude no larger than .008

Up to 15hz, .005 should be used, but the motion can get very violent. 

Not recommended to run above 15Hz, unless with very small amplitudes
