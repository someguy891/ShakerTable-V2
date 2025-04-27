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

The code, "ShakerTableV2Final-TB6600.ino", is commented in detail, and describes most functions of the software.

# Sinusoidal (Resonance) Control
This function controls the motion of the shaker table in a sinusoidal motion. This motion can be used to estimate the natural frequencies of objects, as it attempts moves at a constant, single frequency. 

For the Shaker Table, the maximum acceleration is calculated from the given frequency and amplitude. 

    x(t) = A * sin(ω * t + θ)
    v(t) = A * ω * sin(ω * t + θ)
    a(t) = -A * ω^2 * sin(ω * t + θ)

To calculate maximum acceleration, this equation is used:

    a = (2 * π * f)^2 * A

With the maximum acceleration and velocity calculated from the user inputs, the rest of the programming is straightforward. The table is set to only to move with these values, and moves one step per time increment. The stepper library automatically does the acceleration control when commanded to move to a position, so the only thing left to do is check to see if the target has been reached. If it has, the target position is inverted, and the tables moves in the opposite direction. By controlling the shaker table by only commanding the table to reach a certain velocity with a certain acceleration over a distance, and the calculated values align with the max velocity and acceleration for a sine wave, the table is forced to move in a sine wave motion.


# Results
Overall, the table does an okay job simulating harmonic motion. Observing the capstone position data, sine waves can be clearly seen in the motion of the table, but the precision of the frequency leaves some to be desired. Using recommended amplitude values, the accuracy of the table can be within +/- .5Hz, meeting the set goal.

The test setup for the shaker table used a Pasco Ultrasonic Distance sensor, which measures the time of flight sound emitted by the sensor. Using Pasco Capstone, the sensor can live record the data onto a position graph, and built in tools allow the user to curve fit a sine wave onto the plot. With the curve fit, an estimate of the frequency and amplitude can be found. 

![image](https://github.com/user-attachments/assets/4fbc3e71-d5fd-4168-aefc-29e7e5dc6375)

    Positional graph of the table moving at 2 Hz, and .01m amplitude

The table was tested from a range of 1 Hz to 15 Hz. The Shaker table showed that it has an “ideal” operating range, where it moves smoothly without much noise, but also doesn’t try to rattle itself to pieces. At low frequencies (<5 Hz), the table tends to move with a loud grinding noise, coming from the stepper driver. However, at frequencies above 12Hz, a lot of the motion ends up going into the frame of the machine rather than the table. This could be fixed by mounting the machine directly to a lab bench, or adding more weight to the frame. The range between 5-12 Hz is a sweet spot for the table though, and is the ideal operating range for it. When using the recommended amplitudes, the table operates within +/- .5 Hz of the target frequency, with only a few outliers. 


![image](https://github.com/user-attachments/assets/b3c5650b-2771-4f5a-85d0-b2238917248b)
![image](https://github.com/user-attachments/assets/3b7dce98-699d-4e47-968e-0bbc43ad955f)


    Results from testing with recommended amplitudes

These results reach the original goals for Shaker Table V2, but there are still many improvements that could be made. It took a lot of tweaking of amplitudes to get the results within the +/- .5 Hz goal, and severely limits the use of the table. The vast majority of this issue could be resolved by using a feedback control based system, rather than blindly driving the stepper motor. Additionally, the Pasco ultrasonic sensor got a lot of external noise due to the frame of the table moving. If a mount was made for the sensor so it could be attached directly to the frame of the table, the accuracy of the data should improve.


# Resources
AccelStepper Documentation:
https://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html 

BOM For Shaker Table V-2:
https://hartford0-my.sharepoint.com/:x:/g/personal/forcier_hartford_edu/EQoHR8bn9C1Muq9yt1xqKHYBLXRtwSA_wKFjgTQhrU4cBg?e=nmwIVy 
https://hartford0-my.sharepoint.com/:x:/g/personal/forcier_hartford_edu/EWN45QMFNgpOj6hBR95E2YwBf9stVtuqGKyqXrFxbaF5FQ?e=qKB1Xl 

CAD:
https://cad.onshape.com/documents/7bd40d5f0396d9dd7bc3818a/w/cac37c4a6c6fd51dcfd15dc9/e/18fd263725c2068835e900cc?renderMode=0&uiState=663d1e92c250c04b90a2f304 

