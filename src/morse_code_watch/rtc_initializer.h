#include "programmer_status.h"
#include "low_power_rtc.h"

class RtcInitializer
{
    public:
        RtcInitializer(ProgrammerStatus* programmerStatus, LowPowerRtc* lowPowerRtc, int uploadTime = 20);
        void setTimeIfProgrammerAttached();

    private:
        ProgrammerStatus *programmerStatus;
        LowPowerRtc *lowPowerRtc;
        int uploadTime;
        time_t compiledTime();
        int compiledMonthNumber();
        int compiledTimeAdjustment();

};