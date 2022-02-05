#pragma once

#include <DS3232RTC.h>

class LowPowerRtc
{
    public:
        LowPowerRtc(byte rtcPowerPin);
        void syncWithRtc();
        void setTime(time_t time);

    private:
        byte rtcPowerPin;
};
