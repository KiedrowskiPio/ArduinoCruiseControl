#include <Stepper.h> //Stepper motor control library
const int stepsPerRev = 200; //Has to be changed accordingly to the motor
Stepper myStepper(stepsPerRev, 8, 9, 10, 11); //Initialization of the stepper motor
int stepCount = 0; 

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  int neededPower

  
  myStepper.step(stepsPerRev / 100); //step 1% of revolution

}
