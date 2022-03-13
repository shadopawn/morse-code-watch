#include "attiny_sleep.h"

void AttinySleep::sleep()
{
    applySleepSettings();
    enterSleep();
}

void AttinySleep::applySleepSettings()
{
    disableAdc();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void AttinySleep::disableAdc()
{
    (ADCSRA &= ~(1 << ADEN));
}

void AttinySleep::enterSleep()
{
    sleep_enable();
    sleep_cpu();
}