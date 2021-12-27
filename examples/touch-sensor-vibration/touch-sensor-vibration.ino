int vibrationMotorPin = 1;
int touchSensorPin = 3;

void setup() {
  pinMode(vibrationMotorPin, OUTPUT);
  pinMode(touchSensorPin, INPUT);
}

void loop() {
  int state = digitalRead(touchSensorPin);
  digitalWrite(vibrationMotorPin, state);
}
