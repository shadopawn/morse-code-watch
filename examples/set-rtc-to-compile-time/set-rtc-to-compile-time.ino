#include <DS3232RTC.h>

void setup()
{
    Serial.begin(9600);
    Serial.println("Setting time");

    RTC.set(compiledTime());

    setSyncProvider(RTC.get);
    if (timeStatus() != timeSet)
        Serial.println("Unable to sync with the RTC");
    else
        Serial.println("RTC has set the system time");

    digitalClockDisplay();
}

void loop() {}

void digitalClockDisplay()
{
    printTime();
    printDate();
}

void printTime()
{
    Serial.print(hourFormat12());
    printDigits(minute());
    printDigits(second());
}

void printDate()
{
    Serial.print(' ');
    Serial.print(day());
    Serial.print(' ');
    Serial.print(month());
    Serial.print(' ');
    Serial.print(year());
    Serial.println();
}

void printDigits(int digits)
{
    Serial.print(':');
    if (digits < 10)
        Serial.print('0');
    Serial.print(digits);
}

time_t compiledTime()
{
    char s_month[5];
    int year, day;
    int hour, minute, second;
    tmElements_t timeElements;
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
    sscanf(__DATE__, "%s %d %d", s_month, &day, &year);
    // sscanf(time, "%2hhd %*c %2hhd %*c %2hhd", &t.Hour, &t.Minute, &t.Second);
    sscanf(__TIME__, "%2d %*c %2d %*c %2d", &hour, &minute, &second);
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