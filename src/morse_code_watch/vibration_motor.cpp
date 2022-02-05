#include "vibration_motor.h"

VibrationMotor::VibrationMotor(byte pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void VibrationMotor::setTiming(int dotDuration)
{
    this->dotDuration = dotDuration;
    this->dashDuration = dotDuration * 3;
}

void VibrationMotor::dot()
{
    vibrateForMilliseconds(dotDuration);
}

void VibrationMotor::dash()
{
    vibrateForMilliseconds(dashDuration);
}

void VibrationMotor::vibrateForMilliseconds(int milliseconds)
{
    digitalWrite(this->pin, HIGH);
    delay(milliseconds);
    digitalWrite(this->pin, LOW);
}