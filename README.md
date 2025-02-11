# ShakerTable-V2
Small-scale desktop vibration analysis tool based on an Arduino Uno and run via the Arduino IDE Serial Monitor.

![image](https://github.com/user-attachments/assets/818b4593-0860-4558-b228-9afc340b0cef)

Shaker Tables are commonly used in environmental testing to prove that a complex design can withstand intense vibrations. Whether it's vibrations from an earthquake, the engine of an airplane, or someone walking around with the device in their backpack, all devices need to be able to withstand some level of vibration. While most models can be simulated with reasonable accuracy, sometimes designs are too complex or detailed to thoroughly test within software like Ansys. The only way to truly prove a design can withstand vibrations up to a certain standard, they must be tested in the real world.

This small, desktop shaker table is made to simulate these vibrations, primarily for teaching demos or small scale testing.

# Goals
The goals for this project were outlined as follows:

-Output accurate and repeatable motion

-The table should be able to reach a frequency with a +/-.5Hz error

-Keep table small and light for easy transport

-Easily adjustable amplitude and frequency

-User friendly interface

-Be able to simulate multiple types of vibration profiles:

    -High resonant frequencies (sine wave)
    
    -Saw wave
    
    -Square wave
    
    -Random 


# Hardware
To meet the goals outlined above, a NEMA 17-60mm stepper motor is used with a GT3 belt drive. This simple, cost effective design would also allow different types of vibration profiles to be ran.

The table is currently controlled by an Arduino Uno with the Accel Stepper library, though in the future it may be upgraded to use G-Code and a RPi as a head computer since there are some issues with the current setup, which are described further down in this document.

# Software
All software is written in Arduino's IDE, and uses the AccelStepper Library. The control interface is currently ran within the IDE Serial Monitor.

Pre-made motion profiles are created as functions, which take the user defined values as inputs. Currently, sine-wave resonance and square wave profiles have been made, to demonstrate the basic functionalities of the shaker table. A switch statement is used for user input to provide easy addition of motion profiles in the future. 

Resonance (Sine Wave) Control:


# Results


# Resources
AccelStepper Documentation:
https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html 

BOM For Shaker Table V-2:
https://hartford0-my.sharepoint.com/:x:/g/personal/forcier_hartford_edu/EQoHR8bn9C1Muq9yt1xqKHYBLXRtwSA_wKFjgTQhrU4cBg?e=nmwIVy 
https://hartford0-my.sharepoint.com/:x:/g/personal/forcier_hartford_edu/EWN45QMFNgpOj6hBR95E2YwBf9stVtuqGKyqXrFxbaF5FQ?e=qKB1Xl 

Development Log/Journal:
Shaker Table Independent Study.docx

CAD:
https://cad.onshape.com/documents/7bd40d5f0396d9dd7bc3818a/w/cac37c4a6c6fd51dcfd15dc9/e/18fd263725c2068835e900cc?renderMode=0&uiState=663d1e92c250c04b90a2f304 

