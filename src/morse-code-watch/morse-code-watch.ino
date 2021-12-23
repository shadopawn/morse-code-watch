int vibrationMotorPin = 1;
int touchSensorPin = 3;

void setup() {
  pinMode(vibrationMotorPin, OUTPUT);
  pinMode(touchSensorPin, INPUT);
}

int lastTouchedState = 0;

void loop() {
  int touchSensorState = digitalRead(touchSensorPin);

  if (touchSensorState != lastTouchedState)
  {
    if (touchSensorState == HIGH)
    {
      // Do actions here
    }
  }

  lastTouchedState = touchSensorState;
}
