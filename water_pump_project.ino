volatile int flow_frequency;
 float vol = 0.0, Min, sec;
unsigned char flowSensor = 2;
unsigned long currentTime;
unsigned long initialTime;
bool motorState = false;

#define RELAY 9

void flow(){
  flow_frequency++;
}

void setup() {
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
  pinMode(flowSensor, INPUT);
  digitalWrite(flowSensor, HIGH);
  digitalWrite(RELAY, HIGH);
  attachInterrupt(digitalPinToInterrupt(flowSensor), flow, RISING);
  currentTime = millis();
  initialTime = currentTime;
  Serial.println("WATER PUMP PROJECT");
}

void loop() {
  currentTime = millis();
  if ((currentTime - initialTime) >= 60000 && motorState == false){
    digitalWrite(RELAY, LOW);
    motorState = true;
    initialTime = currentTime;
  }
  if((currentTime - initialTime) >= 1000 && motorState == true){
    initialTime = currentTime;
    if (flow_frequency != 0){
      Min = (flow_frequency / 7.5);
      Serial.print("Rate: ");
      Serial.print(Min);
      Serial.print(" L/min");
      sec = Min/60;
      vol = vol + sec;
      Serial.print(" Vol: ");
      Serial.print(vol);
      Serial.println(" L");
      flow_frequency = 0;
      if (vol >= 0.45){
        digitalWrite(RELAY, HIGH);
        motorState = false;
        Serial.println("IT HAS REACHED 450ML");
        vol = 0.0;
      }
    }
    else {
      digitalWrite(RELAY, HIGH);
      motorState = false;
      Serial.println("THE TANK IS EMPTY");
    }
  }

}
