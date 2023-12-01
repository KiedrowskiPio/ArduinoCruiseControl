#define CALTULATION_INTERVAL 2500 // millisecond delay between calculating rpm 
#define PULSE_PER_REV 2 // number of magnets on the drive-shaft
unsigned long stopWatch = 0;
volatile int count = 0;
int rpm = 0;
const int scale = 60000/CALCULATION_INTERVAL/PUSE_PER_REV;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), incrementCount, FALLING);
}

void loop() {
  if(millis() - stopWatch > CALCULATION_INTERVAL){
    rpm = count*scale;
    Serial.println(rpm);
    count = 0;
    stopWatch = millis();
  }

}

void incrementCount(){
  count++;
}

