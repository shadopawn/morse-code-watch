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
}
