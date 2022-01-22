#include <SoftwareSerial.h>

#define RX 3 // PB3, Pin 2
#define TX 4 // PB4, Pin 3

SoftwareSerial Serial(RX, TX);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.println(internalVoltage());
    delay(1000);
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
