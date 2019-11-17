#define PIN_RELAY 11
#define PIN_ROBOT 12
#define PIN_LIGHT 13
#define PIN_FSR   A0

boolean relayState = false;
uint32_t lastChange = -1;
boolean lastState = false;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_ROBOT, INPUT);
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_LIGHT, OUTPUT);
  pinMode(PIN_FSR, INPUT);
}


void loop() {
  boolean robotSignal = !digitalRead(PIN_ROBOT);

  boolean relayState  = robotSignal;

  float sensorValue = analogRead(PIN_FSR);
//  Serial.println(sensorValue);
  if (sensorValue > 512) {
    relayState = false;
  }

  if (relayState != lastState) {
    // Debounce, only allow a change every 250ms
    if (millis() - lastChange < 250) {
      relayState = lastState;
    }
    else {
      lastState = relayState;
      lastChange = millis();
    }
  }

  digitalWrite(PIN_RELAY, relayState);
  digitalWrite(PIN_LIGHT, relayState);
}
