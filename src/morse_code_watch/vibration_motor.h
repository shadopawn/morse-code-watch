#include <Arduino.h>

#include "morse_output.h"

class VibrationMotor: public MorseOutput {
    public:
        VibrationMotor(byte pin);
        void setTiming(int dotDuration);
        void dot();
        void dash();

    private:
        byte pin;
        int dotDuration = 100;
        int dashDuration = dotDuration * 3;
        void vibrateForMilliseconds(int milliseconds);      
};