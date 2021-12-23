int vibrationMotorPin = 1;
int touchSensorPin = 3;

void setup() {
  pinMode(vibrationMotorPin, OUTPUT);
  pinMode(touchSensorPin, INPUT);
}

bool canTrigger = true;

void loop() {
  int touchSensorState = digitalRead(touchSensorPin);
  
  if (touchSensorState == HIGH && canTrigger)
  {
    canTrigger = false;
    // Do actions here
  }
  else
  {
    canTrigger = true;
  }
}
