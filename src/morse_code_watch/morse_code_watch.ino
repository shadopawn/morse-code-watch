#include "morse_clock.h"
#include "vibration_motor.h"
#include "rtc_initializer.h"
#include "attiny_sleep.h"

const int vibrationMotorPin = 4;
const int rtcPowerPin = 3;

VibrationMotor vibrationMotor(vibrationMotorPin);
LowPowerRtc lowPowerRtc(rtcPowerPin);
MorseClock morseClock(&vibrationMotor, &lowPowerRtc);

ProgrammerStatus programmerStatus;
RtcInitializer rtcInitializer(&programmerStatus, &lowPowerRtc);

AttinySleep attiny;

void setup()
{
    rtcInitializer.setTimeIfProgrammerAttached();

    morseClock.outputTime();

    attiny.sleep();
}

void loop() {}
