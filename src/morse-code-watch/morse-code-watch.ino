#include <DS3232RTC.h>

const int vibrationMotorPin = 4;

void setup()
{
    pinMode(vibrationMotorPin, OUTPUT);

    setTimeIfProgrammerAttached();

    syncAndVibrateTime();
}

void setTimeIfProgrammerAttached()
{
    bool programmerWasAttached = programmerAttached();
    while (programmerAttached());

    if (programmerWasAttached)
    {
        delay(1000);
        RTC.set(compiledTime());
    }
}

bool programmerAttached()
{
    return internalVoltage() > 4000;
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

time_t compiledTime()
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

void loop() {}

const int dotDuration = 100;
const int dashDuration = dotDuration * 3;
const int betweenDotDashDelay = dotDuration;
const int intraDigitDelay = dotDuration * 3;

const char morseDigits[10][5] = {
    "-----",
    ".----",
    "..---",
    "...--",
    "....-",
    ".....",
    "-....",
    "--...",
    "---..",
    "----."};

void syncAndVibrateTime()
{
    setSyncProvider(RTC.get);
    vibrateTime();
}

void vibrateTime()
{
    vibrateHour(hourFormat12());
    vibrateMinutes(minute());
}

void vibrateHour(int hour)
{
    int tensPosition = getTensPosition(hour);
    int onesPosition = getOnesPosition(hour);
    if (tensPosition != 0)
        vibrateDigitWithDelay(tensPosition);
    vibrateDigitWithDelay(onesPosition);
}

void vibrateMinutes(int minutes)
{
    int tensPosition = getTensPosition(minutes);
    int onesPosition = getOnesPosition(minutes);
    vibrateDigitWithDelay(tensPosition);
    vibrateDigitWithDelay(onesPosition);
}

int getTensPosition(int time)
{
    return floor(time / 10);
}

int getOnesPosition(int time)
{
    return time % 10;
}

void vibrateDigitWithDelay(int digit)
{
    vibrateMorseDigit(digit);
    delay(intraDigitDelay);
}

void vibrateMorseDigit(int digit)
{
    if (digit >= 10)
        return;

    for (auto dotOrDash : morseDigits[digit])
    {
        (dotOrDash == '-') ? dash() : dot();
        delay(betweenDotDashDelay);
    }
}

void dot()
{
    vibrateForMilliseconds(dotDuration);
}

void dash()
{
    vibrateForMilliseconds(dashDuration);
}

void vibrateForMilliseconds(int milliseconds)
{
    digitalWrite(vibrationMotorPin, HIGH);
    delay(milliseconds);
    digitalWrite(vibrationMotorPin, LOW);
}
