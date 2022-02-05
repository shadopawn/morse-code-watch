#include <Arduino.h>

class ProgrammerStatus
{
    public:
        ProgrammerStatus(int voltageThreshold = 4000);
        bool isProgrammerAttached();

    private:
        int voltageThreshold;
        int internalVoltage();
        unsigned int unscaledVoltageReading();
};
