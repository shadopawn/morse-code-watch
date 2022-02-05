#include "programmer_status.h"

ProgrammerStatus::ProgrammerStatus(int voltageThreshold = 4000)
{
    this->voltageThreshold = voltageThreshold;
}

bool ProgrammerStatus::isProgrammerAttached()
{
    return internalVoltage() > voltageThreshold;
}

int ProgrammerStatus::internalVoltage()
{
    // reads internal 1V1 reference against VCC
    ADMUX = _BV(MUX3) | _BV(MUX2);
    delay(2); // Wait for Vref to settle
    unscaledVoltageReading();
    // discard previous result
    unsigned int val = unscaledVoltageReading();
    // returns voltage in mV
    return ((long)1024 * 1100) / val;
}

unsigned int ProgrammerStatus::unscaledVoltageReading()
{
    ADCSRA |= _BV(ADSC); // Convert
    while (bit_is_set(ADCSRA, ADSC));
    uint8_t low = ADCL;
    return (ADCH << 8) | low;
} 
