#include "attiny_sleep.h"

void ATtinySleep::sleep()
{
    applySleepSettings();
    enterSleep();
}

void ATtinySleep::applySleepSettings()
{
    disableAdc();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void ATtinySleep::disableAdc()
{
    (ADCSRA &= ~(1 << ADEN));
}

void ATtinySleep::enterSleep()
{
    sleep_enable();
    sleep_cpu();
}