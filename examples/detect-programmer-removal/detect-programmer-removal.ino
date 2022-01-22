#include <SoftwareSerial.h>

#define RX 3 // PB3, Physical Pin 2
#define TX 4 // PB4, Physical Pin 3

SoftwareSerial Serial(RX, TX);

void setup()
{
    Serial.begin(9600);

    Serial.println("Begin detecting if programmer is attached");

    bool programmerWasAttached = programmerAttached();
    while (programmerAttached());
    
    if (programmerWasAttached){
        Serial.println("Programmer Removed");
        Serial.print("Time programmer was attached ");
        Serial.println(millis());
    }
}

void loop()
{
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
