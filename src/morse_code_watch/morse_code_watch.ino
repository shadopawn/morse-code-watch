#include "morse_clock.h"
#include "vibration_motor.h"
#include "rtc_initializer.h"
#include "attiny_sleep.h"

const int rtcPowerPin = 3;
const int vibrationMotorPin = 4;

ProgrammerStatus programmerStatus;
LowPowerRtc lowPowerRtc(rtcPowerPin);
RtcInitializer rtcInitializer(&programmerStatus, &lowPowerRtc);

VibrationMotor vibrationMotor(vibrationMotorPin);
MorseClock morseClock(&vibrationMotor, &lowPowerRtc);

ATtinySleep attiny;

void setup()
{
    rtcInitializer.setTimeIfProgrammerAttached();

    morseClock.outputTime();

    attiny.sleep();
}

void loop() {}
