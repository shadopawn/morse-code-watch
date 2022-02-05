#include "rtc_initializer.h"

RtcInitializer::RtcInitializer(ProgrammerStatus* programmerStatus, LowPowerRtc* lowPowerRtc, int uploadTime = 20)
{
    this->programmerStatus = programmerStatus;
    this->lowPowerRtc = lowPowerRtc;
    this->uploadTime = uploadTime;
}

void RtcInitializer::setTimeIfProgrammerAttached()
{
    bool programmerWasAttached = programmerStatus->isProgrammerAttached();
    while (programmerStatus->isProgrammerAttached());

    if (programmerWasAttached)
    {
        delay(1000);
        lowPowerRtc->setTime(compiledTime());
    }
}

time_t RtcInitializer::compiledTime()
{
    const char *compiledDate = __DATE__, *compiledTime = __TIME__;

    tmElements_t timeElements;
    timeElements.Month = compiledMonthNumber();
    timeElements.Day = atoi(compiledDate + 4);
    timeElements.Year = atoi(compiledDate + 7) - 1970;
    timeElements.Hour = atoi(compiledTime);
    timeElements.Minute = atoi(compiledTime + 3);
    timeElements.Second = atoi(compiledTime + 6);

    time_t time = makeTime(timeElements);
    return time + compiledTimeAdjustment();
}

int RtcInitializer::compiledMonthNumber()
{
    const char *compiledDate = __DATE__;
    const char *months = "JanFebMarAprMayJunJulAugSepOctNovDec";
    char compiledMonth[4], *month;

    strncpy(compiledMonth, compiledDate, 3);
    compiledMonth[3] = '\0';
    month = strstr(months, compiledMonth);

    return ((month - months) / 3 + 1);
}

int RtcInitializer::compiledTimeAdjustment()
{
    int currentSecondsRunning = millis() / 1000;
    return uploadTime + currentSecondsRunning;
}

