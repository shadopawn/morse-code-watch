#include "morse_clock.h"

MorseClock::MorseClock(MorseOutput* outputDevice, LowPowerRtc* lowPowerRtc, int dotDuration = 100)
{
    this->outputDevice = outputDevice;
    this->lowPowerRtc = lowPowerRtc;
    
    setTiming(dotDuration);
}

void MorseClock::setTiming(int dotDuration)
{
    outputDevice->setTiming(dotDuration);
    this->betweenDotDashDelay = dotDuration;
    this->betweenDigitDelay = dotDuration * 3;
}

void MorseClock::outputTime()
{
    lowPowerRtc->syncWithRtc();
    outputHour();
    outputMinutes();
}

void MorseClock::outputHour()
{
    int hour = hourFormat12();
    int tensPosition = this->tensPosition(hour);
    int onesPosition = this->onesPosition(hour);
    if (tensPosition != 0)
        outputDigitWithDelay(tensPosition);
    outputDigitWithDelay(onesPosition);
}

void MorseClock::outputMinutes()
{
    int minutes = minute();
    int tensPosition = this->tensPosition(minutes);
    int onesPosition = this->onesPosition(minutes);
    outputDigitWithDelay(tensPosition);
    outputDigitWithDelay(onesPosition);
}

int MorseClock::tensPosition(int time)
{
    return floor(time / 10);
}

int MorseClock::onesPosition(int time)
{
    return time % 10;
}

void MorseClock::outputDigitWithDelay(int digit)
{
    outputMorseDigit(digit);
    delay(betweenDigitDelay);
}

void MorseClock::outputMorseDigit(int digit)
{
    if (digit >= 10)
        return;

    for (auto dotOrDash : morseDigits[digit])
    {
        (dotOrDash == '.') ? outputDevice->dot() : outputDevice->dash();
        delay(betweenDotDashDelay);
    }
}