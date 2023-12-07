#define CALTULATION_INTERVAL 2500 // millisecond delay between calculating rpm 
#define PULSE_PER_REV 2 // number of magnets on the drive-shaft
unsigned long stopWatch = 0;
volatile int count = 0;
int rpm = 0;
const int scale = 60000/CALCULATION_INTERVAL/PUSE_PER_REV;
// vehicle configuration
const int highestGearRatio = 1; //My car has direct drive on its highest gear - needs to be changed accorging to vehicle specs
const double differentialRatio = 4,3; //Has to be changed according to vehicle specs 
const int wheelCircumference=
///
int vehicleSpeed = 0;

/// stepper motor controll ///
const int stepsPerRev = 200; //Has to be changed accordingly to the motor
Stepper myStepper(stepsPerRev, 8, 9, 10, 11); //Initialization of the stepper motor
int stepCount = 0; 
///


void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), incrementCount, FALLING);
}

void loop() {
  if(millis() - stopWatch > CALCULATION_INTERVAL){
    rpm = count*scale;
    Serial.print("Driveshaft speed:");
    Serial.print(rpm);
    Serial.println("rpm");
    
    count = 0;
    stopWatch = millis();
  }

  myStepper.step(stepsPerRev / 100); //step 1% of revolution

}

void incrementCount(){
  count++;
}

