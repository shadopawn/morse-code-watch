#pragma once

class MorseOutput {
    public:
        virtual void setTiming(int dotDuration) = 0;
        virtual void dot() = 0;
        virtual void dash() = 0;
};