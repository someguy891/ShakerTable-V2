#include <AccelStepper.h>

//-----------------------------------SETUP----------------------------------
//driver pin setup
#define dir 9
#define stp 8

//num steps in one 360 degree revolution of stepper
const int stepsPerRev = 400;//steps
const double distPerRev = .04241;//meters
const double pulleyRadius = 0;//might not need
const double STEPLOOP = 1;
const double MAXAMP = .2;
double accel = 0;
int currentPos = 0;

AccelStepper stepper(1, stp, dir); //create stepper motor object


void setup() {
  // Change these to suit your stepper if you want
  Serial.begin(57600);
  stepper.setEnablePin(7);
}

//----------------------------SQUARE------------------------------

//This function needs to be updated to work with the TB6600 Driver

void squareControl(double maxVin, double ampIn) {
  const double stepsPmm = 5; //change to 10 bc microstepping?
  int amplitudeSteps = ampIn / distPerRev * stepsPerRev;
  Serial.println(amplitudeSteps);
  //amplitudeSteps = amplitudeSteps/2;

  double maxV = maxVin * stepsPmm;
  stepper.disableOutputs();

  stepper.setMaxSpeed(maxV);
  stepper.setSpeed(maxV);
  stepper.setAcceleration(99999999);
  stepper.moveTo(amplitudeSteps);

  Serial.println("Starting, hit any button+enter to escape.");
  delay(3000);
  
  while (halt()) {

    if (stepper.distanceToGo() == 0) {
      stepper.moveTo(-stepper.currentPosition());
    }

    stepper.run();
    stepper.runSpeed();
  }
}



//-----------------------------RESONANCE-----------------------
void resonanceControl(double freqIn, double ampIn) {

  //Things to try to stop stutter:
  //https://forum.arduino.cc/t/stepper-motor-stutter-low-rpm-drv8871/513789/6
  //1. increase amperage to 3amp
  //2. try microstepping (change steps/rev in code)

  int amplitudeSteps = ampIn / distPerRev * stepsPerRev; //calc amp in steps
  //amplitudeSteps = amplitudeSteps / 2; //shouldnt divide by 2
  Serial.println(amplitudeSteps);
  int stepVMax = freqIn * stepsPerRev; //calc max speed

  //This command calculates the max accel for the shaker table, according to
  //the max acceleration equation for sinusoidal motion. This is then used to
  //generate the motion desired with the AccelStepper library
  accel = pow((2 * PI * freqIn), 2) * amplitudeSteps; 
  Serial.print("Maximum acceleration: ");
  Serial.println(accel);

  stepper.setMaxSpeed(10000000000);
  stepper.setSpeed(stepVMax); //set velocity goal
  stepper.setAcceleration(accel); //set acceleration
  stepper.moveTo(amplitudeSteps); //move amplitude

  //give a 3 second delay for user to think about their actions
  Serial.println("Starting, hit any button+enter to escape.");
  delay(3000);

  while (halt()) {//run until user gives new input
    //Serial.println("in loop");
    stepper.disableOutputs();
    
    //Serial.print(accel);
    
    if (stepper.distanceToGo() == 0)
      //once at end of travel (amplitudeSteps), change direction, move to other end of travel
      stepper.moveTo(-stepper.currentPosition());
/*
    Serial.print("Step: ");
    Serial.print(stepper.distanceToGo());
    Serial.print(" || ");
    Serial.print(stepper.currentPosition());
    Serial.print(" || ");
    Serial.print(stepper.targetPosition());
*/
    stepper.run();//move a max of one step.
  }
}

//-----------------------------STOP MOVEMENT-------------------
boolean halt() {
  if (Serial.available() == 0) {
    return true;
    Serial.println("HALTED");
  } else {
    stepper.enableOutputs();
    return false;

    //IMPLEMNT : ramp down speed according to last speed
  }
}


//--------------------------------MENU--------------------------
void menu() {
  //------------------------UI----------------------
  int menuSelect = 0;
  Serial.println("Select wave generation mode: ");
  Serial.println("1 : resonance (sine wave)");
  Serial.println("2 : move table(TEST)");
  Serial.println("3 : bounce (TEST)");
  Serial.println("4 : Square Wave");
  while (Serial.available() == 0) {
  }
  menuSelect = Serial.parseInt();
  //IMPLEMENT : random vibration
  //IMPLEMENT : impact(accel then sudden stop)

  switch (menuSelect) {
    //--------------------RESONANCE------------------
    case 1: {
        float uFreq = 0;
        float uAmp = 0;

        Serial.println("Input frequency or 0 for back: ");
        while (Serial.available() == 0) {
        }
        uFreq = Serial.parseFloat();

        Serial.println("Input amplitude greater than 0 but less than .15 meters: ");
        while (Serial.available() == 0) {
        }
        uAmp = Serial.parseFloat();

        if (uFreq != 0) {
          if (uAmp > 0 && uAmp <= MAXAMP) {
            resonanceControl(uFreq, uAmp);
          } else {
            Serial.println("out of range");
          }
        }
        break;
      }
    //----------------MOVE----------------------
    /*
      case 2: {

        float dist = 0;
        float rpm = 0;

        Serial.println("Input speed in steps/second or 0 for back: ");
        while (Serial.available() == 0) {
        }
        rpm = Serial.parseFloat();

        Serial.println("Input distance in meters: ");
        while (Serial.available() == 0) {
        }
        dist = Serial.parseFloat();

        basicMovement(rpm, dist);
        break;
      }
    */
    case 3: {

        stepper.setEnablePin(7);

        stepper.setMaxSpeed(10000);
        stepper.setSpeed(1500);
        stepper.setAcceleration(1000);
        stepper.moveTo(100);

        while (true) {
          // If at the end of travel go to the other end
          stepper.disableOutputs();

          if (stepper.distanceToGo() == 0)
            stepper.moveTo(-stepper.currentPosition());

          Serial.print(stepper.distanceToGo());
          Serial.print(" || ");
          Serial.print(stepper.currentPosition());
          Serial.print(" || ");
          Serial.println(stepper.targetPosition());

          stepper.run();
        }
      }

    case 4: {
        float uV = 0;
        float uA = 0;
        //square wave
        Serial.println("Input max velocity in mm/s or 0 for back: ");
        while (Serial.available() == 0) {
        }
        uV = Serial.parseFloat();

        Serial.println("Input amplitude in meters or 0 for back: ");
        while (Serial.available() == 0) {
        }
        uA = Serial.parseFloat();

        squareControl(uV, uA);
      }

    default: {
        Serial.println("bad input");
        break;
      }
  }
  //----------------------------------------------
}


void loop() {
  menu();
}
