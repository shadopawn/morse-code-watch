#include <Arduino.h>
#include <avr/sleep.h>

class AttinySleep
{
    public:
        void sleep();

    private:
        void applySleepSettings();
        void disableAdc();
        void enterSleep();
    
};
