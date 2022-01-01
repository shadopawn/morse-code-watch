int vibrationMotorPin = 4;
int touchSensorPin = 3;

void setup()
{
  pinMode(vibrationMotorPin, OUTPUT);
  pinMode(touchSensorPin, INPUT);
}

void loop()
{
  onTouch(vibrateForOneSecond);
}

int lastTouchedState = 0;

void onTouch(void (*touchedAction)())
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
