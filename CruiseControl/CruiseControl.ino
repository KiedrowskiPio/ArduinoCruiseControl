//Include mandatory libraries
#include <Stepper.h>
#include <Encoder.h>
#include <Arduino.h>
#include <HallA1302.h>

//Pin Definition
#define BRAKE_PEDAL_INPUT 4 //input from brake pedal
#define HALL_PIN_VOUT A0
#define ROTARTENCI_PIN_CLK 2
#define ROTARTENCI_PIN_D 3
#define ROTARTENCI_PIN_S1 5
#define STEPPER_PIN_STEP 7
#define STEPPER_PIN_DIR 6

//Driveshaft Speed calculation
const int PULSE_PER_REV = 2; //number of magnets on driveshaft
const int CALCULATION_INTERVAL = 2500; // millisecond delay between calculating rpm 
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
int savedSpeed = 0; //speed saved from previous cycle

//stepper motor control
StepperMotor myStepper(STEPPER_PIN_STEP, STEPPER_PIN_DIR); //Initialization of the stepper motor
int stepCount = 0; 
int motorSpeed = 720;

//cruise control setup
int setSpeed = 0; //speed desired to maintain
bool systemActive = false; //system working flag

//Object initialization
Encoder rotartEnc1(ROTARTENCI_PIN_D, ROTARTENCI_PIN_CLK);
HallA1302 hallA(HALLA_PIN_COUT);
long rotaryEncIOldPosition  = 0;

void setup() {
  rotaryEncIButton.init();
  myStepper.enable();
  combinedRatio = highestGearRatio/differentialRatio*wheelCircumference/100;
  myStepper.setSpeed(motorSpeed);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), incrementCount, FALLING);
}

void loop() {

  long rotaryEncINewPosition = rotaryEncI.read();
  if (rotaryEncINewPosition != rotaryEncIOldPosition) {
    rotaryEncIOldPosition = rotaryEncINewPosition;
    setSpeed = rotaryEncINewPosition;
    Serial.print(F("Wybrana prędkość: "));
    Serial.print(rotaryEncINewPosition);

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
        if(savedSpeed > vehicleSpeed-1){
          Serial.println("vehicle is accelerating")
        }
        else{
          myStepper.step(1, 5);
          Serial.println("vehicle velocity is too low. Speeding up...")
        }
      }
      else if(setSpeed < vehicleSpeed){
        if(savedSpeed < vehicleSpeed+3){
          Serial.println("vehicle is slowing down")
        }
        else{
          myStepper.step(0, 5);
          Serial.println("vehicle speed is too great. Slowing down...")
        }

      }
  }


delay(2000);
}

void incrementCount(){
  count++;
}

void StopCruiseControl(){
  savedSpeed = 0; //check it later
  //make stepper motor free spin
}

