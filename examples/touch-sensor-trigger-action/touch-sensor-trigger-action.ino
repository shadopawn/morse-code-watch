int vibrationMotorPin = 1;
int touchSensorPin = 3;

void setup()
{
  pinMode(vibrationMotorPin, OUTPUT);
  pinMode(touchSensorPin, INPUT);
}

void loop()
{
  onTouched(vibrateForOneSecond);
}

int lastTouchedState = 0;

void onTouched(void (*touchedAction)())
{
  int touchSensorState = digitalRead(touchSensorPin);

  if (touchSensorState != lastTouchedState && touchSensorState == HIGH)
    touchedAction();

  lastTouchedState = touchSensorState;
}

void vibrateForOneSecond(){
  digitalWrite(vibrationMotorPin, HIGH);
  delay(1000);
  digitalWrite(vibrationMotorPin, LOW);
}
