#include <DS3232RTC.h>

#include <SoftwareSerial.h>

#define RX 3 // PB3, Physical Pin 2
#define TX 4 // PB4, Physical Pin 3

SoftwareSerial Serial(RX, TX);

void setup()
{
    Serial.begin(9600);

    bool programmerWasAttached = programmerAttached();
    while (programmerAttached());
    
    if (programmerWasAttached){

        Serial.println("Programmer Removed");
        Serial.print("Programmer was attached for ");
        Serial.print(millis());
        Serial.println("ms");

        delay(1000);
        setAndPrintTime();
    }
    else
    {
        Serial.println("Programmer was not attached");
    }
}

void loop()
{
    digitalClockDisplay();
    delay(1000);
}

bool programmerAttached()
{
    return internalVoltage() > 4000;
}

void printVoltage()
{
    Serial.print("Internal voltage ");
    Serial.print(internalVoltage());
    Serial.println("mV");
}

int internalVoltage()
{
    // reads internal 1V1 reference against VCC
    ADMUX = _BV(MUX3) | _BV(MUX2);
    delay(2);            // Wait for Vref to settle
    ADCSRA |= _BV(ADSC); // Convert
    while (bit_is_set(ADCSRA, ADSC));
    uint8_t low = ADCL;
    unsigned int val = (ADCH << 8) | low;
    // discard previous result
    ADCSRA |= _BV(ADSC); // Convert
    while (bit_is_set(ADCSRA, ADSC));
    low = ADCL;
    val = (ADCH << 8) | low;
    // returns voltage in mV
    return ((long)1024 * 1100) / val;
}

void setAndPrintTime()
{
    Serial.println("Setting time");

    RTC.set(compiledTime());

    setSyncProvider(RTC.get);
    if (timeStatus() != timeSet)
        Serial.println("Unable to sync with the RTC");
    else
        Serial.println("RTC has set the system time");

    digitalClockDisplay();
}

time_t compiledTime()
{
    const char *compiledDate = __DATE__, *compiledTime = __TIME__;

    tmElements_t tm;
    tm.Month = compiledMonthNumber();
    tm.Day = atoi(compiledDate + 4);
    tm.Year = atoi(compiledDate + 7) - 1970;
    tm.Hour = atoi(compiledTime);
    tm.Minute = atoi(compiledTime + 3);
    tm.Second = atoi(compiledTime + 6);

    time_t time = makeTime(tm);
    return time + compiledTimeAdjustment();
}

int compiledMonthNumber()
{
    const char *compiledDate = __DATE__;
    const char *months = "JanFebMarAprMayJunJulAugSepOctNovDec";
    char compiledMonth[4], *month;

    strncpy(compiledMonth, compiledDate, 3);
    compiledMonth[3] = '\0';
    month = strstr(months, compiledMonth);

    return ((month - months) / 3 + 1);
}

int compiledTimeAdjustment()
{
    const time_t FUDGE(20); // fudge factor to allow for upload time, etc. (seconds, YMMV)
    int currentRunningTime = millis()/1000;
    return FUDGE + currentRunningTime;
}

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
