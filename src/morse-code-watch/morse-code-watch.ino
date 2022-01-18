#include <DS3232RTC.h>

int vibrationMotorPin = 4;
int touchSensorPin = 3;

void setup()
{
    pinMode(vibrationMotorPin, OUTPUT);
    pinMode(touchSensorPin, INPUT);
}

void loop()
{
    onTouch(vibrateTime);
}

int lastTouchedState = 0;

void onTouch(void (*touchedAction)())
{
    int touchSensorState = digitalRead(touchSensorPin);

    if (touchSensorState != lastTouchedState && touchSensorState == HIGH)
        touchedAction();

    lastTouchedState = touchSensorState;
}

int dotDuration = 100;
int dashDuration = dotDuration * 3;
int betweenDotDashDelay = dotDuration;
int intraDigitDelay = dotDuration * 3;

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
    "----."};

void syncAndVibrateTime()
{
    setSyncProvider(RTC.get);
    vibrateTime();
}

void vibrateTime()
{
    vibrateHour(hourFormat12());
    vibrateMinutes(minute());
}

void vibrateHour(int hour)
{
    int tensPosition = getTensPosition(hour);
    int onesPosition = getOnesPosition(hour);
    if (tensPosition != 0)
        vibrateDigitWithDelay(tensPosition);
    vibrateDigitWithDelay(onesPosition);
}

void vibrateMinutes(int minutes)
{
    int tensPosition = getTensPosition(minutes);
    int onesPosition = getOnesPosition(minutes);
    vibrateDigitWithDelay(tensPosition);
    vibrateDigitWithDelay(onesPosition);
}

int getTensPosition(int time)
{
    return floor(time / 10);
}

int getOnesPosition(int time)
{
    return time % 10;
}

void vibrateDigitWithDelay(int digit)
{
    vibrateMorseDigit(digit);
    delay(intraDigitDelay);
}

void vibrateMorseDigit(int digit)
{
    if (digit >= 10)
        return;

    for (auto dotOrDash : morseDigits[digit])
    {
        (dotOrDash == '-') ? dash() : dot();
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
