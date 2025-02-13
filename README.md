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
To meet the goals outlined above, a NEMA 17-60mm stepper motor is used with a GT3 belt drive. This simple, cost effective design would also allow different types of vibration profiles to be run.

The table is currently controlled by an Arduino Uno R3 with the Accel Stepper library. 

A TB6600, a common stepper motor driver, is used to control the NEMA-17. This industrial grade stepper motor driver is commonly used for CNC machines and other automated industrial machines, and is inexpensive while also having features like selectable current and easy microstepping. 

A dedicated 24V, 15A power supply is used to power the stepper motor driver, to provide a larger working range for the stepper motor, without worry of brownout. Orignally, a smaller 12V, 5A power supply was used with a 3D printer stepper driver, but this caused many issues. At lower speeds, the motor failed to move at all, while at higher speeds the motor would shudder and move unpredicatably. This was due to a lack of amperage, and the lower voltage limited the max speed of the motor, as seen below. 

![Screenshot 2025-02-11 164128](https://github.com/user-attachments/assets/93bf9890-6eea-4ea7-b9e4-4a03056dfb68)


# Software
All software is written in Arduino's IDE, and uses the AccelStepper Library. The control interface is currently ran within the IDE Serial Monitor.

Pre-made motion profiles are created as functions, which take the user defined values as inputs. Currently, sine-wave resonance and square wave profiles have been made, to demonstrate the basic functionalities of the shaker table. A switch statement is used for user input to provide easy addition of motion profiles in the future. 

# Sinusoidal (Resonance) Control
This function controls the motion of the shaker table in a sinusoidal motion. This motion can be used to estimate the natural frequencies of objects, as it moves at a constant, single frequency. 

For the Shaker Table, the maximum acceleration is calculated from the given frequency and amplitude. 

    x(t) = A * sin(ω * t + θ)
    v(t) = A * ω * sin(ω * t + θ)
    a(t) = -A * ω^2 * sin(ω * t + θ)

To calculate maximum acceleration, this equation is used:

    a = (2 * π * f)^2 * A



# Results

Coming soon, as the table is still going under testing. 

# Resources
AccelStepper Documentation:
https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html 

BOM For Shaker Table V-2:
https://hartford0-my.sharepoint.com/:x:/g/personal/forcier_hartford_edu/EQoHR8bn9C1Muq9yt1xqKHYBLXRtwSA_wKFjgTQhrU4cBg?e=nmwIVy 
https://hartford0-my.sharepoint.com/:x:/g/personal/forcier_hartford_edu/EWN45QMFNgpOj6hBR95E2YwBf9stVtuqGKyqXrFxbaF5FQ?e=qKB1Xl 

CAD:
https://cad.onshape.com/documents/7bd40d5f0396d9dd7bc3818a/w/cac37c4a6c6fd51dcfd15dc9/e/18fd263725c2068835e900cc?renderMode=0&uiState=663d1e92c250c04b90a2f304 

