#include <DS3232RTC.h>

const int vibrationMotorPin = 4;

void setup()
{
    pinMode(vibrationMotorPin, OUTPUT);

    syncAndVibrateTime();
}

void loop() {}

const int dotDuration = 100;
const int dashDuration = dotDuration * 3;
const int betweenDotDashDelay = dotDuration;
const int intraDigitDelay = dotDuration * 3;

const char morseDigits[10][5] = {
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
