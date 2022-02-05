#include "low_power_rtc.h"

LowPowerRtc::LowPowerRtc(byte rtcPowerPin)
{
    this->rtcPowerPin = rtcPowerPin;
    pinMode(rtcPowerPin, OUTPUT);
}

void LowPowerRtc::syncWithRtc()
{
    digitalWrite(rtcPowerPin, HIGH);
    setSyncProvider(RTC.get);
    digitalWrite(rtcPowerPin, LOW);
}

void LowPowerRtc::setTime(time_t time)
{
    digitalWrite(rtcPowerPin, HIGH);
    RTC.set(time);
    digitalWrite(rtcPowerPin, LOW);
}
