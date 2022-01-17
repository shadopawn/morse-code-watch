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
    const char *compDate = __DATE__, *compTime = __TIME__, *months = "JanFebMarAprMayJunJulAugSepOctNovDec";
    char compMon[4], *m;

    strncpy(compMon, compDate, 3);
    compMon[3] = '\0';
    m = strstr(months, compMon);

    tmElements_t tm;
    tm.Month = ((m - months) / 3 + 1);
    tm.Day = atoi(compDate + 4);
    tm.Year = atoi(compDate + 7) - 1970;
    tm.Hour = atoi(compTime);
    tm.Minute = atoi(compTime + 3);
    tm.Second = atoi(compTime + 6);

    time_t t = makeTime(tm);
    return t + FUDGE;
}