#include <DS3232RTC.h>

void setup()
{
    RTC.set(compiledTime(__DATE__, __TIME__));
}

void loop()
{
}

time_t compiledTime(char const *date, char const *time)
{
    char s_month[5];
    int year, day;
    int hour, minute, second;
    tmElements_t timeElements;
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
    sscanf(date, "%s %d %d", s_month, &day, &year);
    //sscanf(time, "%2hhd %*c %2hhd %*c %2hhd", &t.Hour, &t.Minute, &t.Second);
    sscanf(time, "%2d %*c %2d %*c %2d", &hour, &minute, &second);
    // Find where is s_month in month_names. Deduce month value.
    timeElements.Month = (strstr(month_names, s_month) - month_names) / 3 + 1;
    timeElements.Day = day;
    // year can be given as '2010' or '10'. It is converted to years since 1970
    if (year > 99) 
        timeElements.Year = year - 1970;
    else 
        timeElements.Year = year + 50;
    timeElements.Hour = hour;
    timeElements.Minute = minute;
    timeElements.Second = second;
    return makeTime(timeElements);
}