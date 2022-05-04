#include <Arduino.h>
#include <avr/sleep.h>

class ATtinySleep
{
    public:
        void sleep();

    private:
        void applySleepSettings();
        void disableAdc();
        void enterSleep();
    
};
