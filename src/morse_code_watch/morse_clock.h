#include <Arduino.h>

#include "morse_output.h"
#include "low_power_rtc.h"

class MorseClock
{
    public:
        MorseClock(MorseOutput* outputDevice, LowPowerRtc* lowPowerRtc, int dotDuration = 100);
        void outputTime();

    private:
        MorseOutput *outputDevice;
        LowPowerRtc *lowPowerRtc;
        int betweenDotDashDelay;
        int betweenDigitDelay;
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
        void setTiming(int dotDuration);
        void outputHour();
        void outputMinutes();
        int tensPosition(int time);
        int onesPosition(int time);
        void outputDigitWithDelay(int digit);
        void outputMorseDigit(int digit);
};