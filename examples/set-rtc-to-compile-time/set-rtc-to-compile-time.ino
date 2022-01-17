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
    const time_t FUDGE(10); // fudge factor to allow for upload time, etc. (seconds, YMMV)
    const char *compiledDate = __DATE__, *compiledTime = __TIME__, *months = "JanFebMarAprMayJunJulAugSepOctNovDec";
    char compiledMonth[4], *month;

    strncpy(compiledMonth, compiledDate, 3);
    compiledMonth[3] = '\0';
    month = strstr(months, compiledMonth);

    tmElements_t tm;
    tm.Month = ((month - months) / 3 + 1);
    tm.Day = atoi(compiledDate + 4);
    tm.Year = atoi(compiledDate + 7) - 1970;
    tm.Hour = atoi(compiledTime);
    tm.Minute = atoi(compiledTime + 3);
    tm.Second = atoi(compiledTime + 6);

    time_t t = makeTime(tm);
    return t + FUDGE;
}