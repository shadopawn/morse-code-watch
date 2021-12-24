int vibrationMotorPin = 1;
int touchSensorPin = 3;

void setup() {
  pinMode(vibrationMotorPin, OUTPUT);
  pinMode(touchSensorPin, INPUT);
}

void loop() {

}

int lastTouchedState = 0;

void onTouched(void (*touchedAction)())
{
  int touchSensorState = digitalRead(touchSensorPin);

  if (touchSensorState != lastTouchedState)
  {
    if (touchSensorState == HIGH)
    {
      touchedAction();
    }
  }

  lastTouchedState = touchSensorState;
}
