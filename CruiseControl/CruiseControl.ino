#include <Stepper.h> //Stepper motor controling library
#define CALTULATION_INTERVAL 2500 // millisecond delay between calculating rpm 
#define PULSE_PER_REV 2 // number of magnets on the drive-shaft
#define BRAKE_PEDAL_INPUT 3 //input from brake pedal

//Driveshaft Speed calculation
unsigned long stopWatch = 0;
volatile int count = 0;
int rpm = 0;
const int scale = 60000/CALCULATION_INTERVAL/PUSE_PER_REV;

//vehicle configuration
const int highestGearRatio = 1; //My car has direct drive on its highest gear - needs to be changed accorging to vehicle specs
const double differentialRatio = 4,3; //Has to be changed according to vehicle specs 
const int wheelCircumference = 182; //wheel circumference in centymeters
double combinedRatio; //distance traveled through 1 driveshaft revolution
int vehicleSpeed = 0; //calculated vehicle speed in km/h

//stepper motor control
const int stepsPerRev = 200; //Has to be changed accordingly to the motor
Stepper myStepper(stepsPerRev, 8, 9, 10, 11); //Initialization of the stepper motor
int stepCount = 0; 
int motorSpeed = 720;

//cruise control setup
int setSpeed = 0; //speed desired to maintain
bool systemActive = false; //system working flag

void setup() {
  combinedRatio = highestGearRatio/differentialRatio*wheelCircumference/100;
  myStepper.setSpeed(motorSpeed);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), incrementCount, FALLING);
}

void loop() {
  if(millis() - stopWatch > CALCULATION_INTERVAL){
    rpm = count*scale;
    Serial.print("Driveshaft speed: ");
    Serial.print(rpm);
    Serial.println("rpm");
    vehicleSpeed = rpm*combinedRatio*60;
    Serial.print("Vehicle speed: ");
    Serial.print(vehicleSpeed);
    Serial.println("");
    
    count = 0;
    stopWatch = millis();
  }
  if(systemActive = true){
      if (setSpeed < vehicleSpeed-4 || setSpeed > vehicleSpeed+4)
      {
        Serial.println("vehicle speed is close to desired")
      }
      else if(setSpeed > vehicleSpeed){
        myStepper.step(stepsPerRev / 50); //step 2% of revolution
        Serial.println("vehicle speed is too slow. Speeding up...")
      }
      else if(setSpeed < vehicleSpeed){
        myStepper.step(-stepsPerRev / 25); //step 4% of revolution back
        Serial.println("vehicle speed i too great. Slowing down...")
      }
  }

delay(2000);
}

void incrementCount(){
  count++;
}

