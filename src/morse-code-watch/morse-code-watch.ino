int vibrationMotorPin = 1;
int touchSensorPin = 3;

void setup()
{
  pinMode(vibrationMotorPin, OUTPUT);
  pinMode(touchSensorPin, INPUT);
}

void loop()
{
}

int lastTouchedState = 0;

void onTouched(void (*touchedAction)())
{
  int touchSensorState = digitalRead(touchSensorPin);

  if (touchSensorState != lastTouchedState && touchSensorState == HIGH)
    touchedAction();

  lastTouchedState = touchSensorState;
}

int dotDuration = 250;
int dashDuration = dotDuration*3;
int betweenDotDashDelay = dotDuration;
int intraDigitDelay = dotDuration*3;

char morseDigits[10][5] = {
  "-----",
  ".----",
  "..---",
  "...--",
  "....-",
  ".....",
  "-....",
  "--...",
  "---..",
  "----." 
};

void vibrateMorseDigit(int digit)
{
  if (digit >= 10) return;

  char dotsAndDashes[5] = { morseDigits[digit] };

  for (auto dotOrDash : dotsAndDashes)
  {
    (dotOrDash == ".") ? dot() : dash();
    delay(betweenDotDashDelay);
  }
}

void dot() 
{
  vibrateForMilliseconds(dotDuration);
}

void dash()
{
  vibrateForMilliseconds(dashDuration);
}

void vibrateForMilliseconds(int milliseconds)
{
  digitalWrite(vibrationMotorPin, HIGH);
  delay(milliseconds);
  digitalWrite(vibrationMotorPin, LOW);
}
