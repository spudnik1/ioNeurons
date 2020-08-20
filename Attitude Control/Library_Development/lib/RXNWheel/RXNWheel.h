#ifndef RXNWHEEL_H
#define RXNWHEEL_H

#include <mbed.h>

#define ENCODER_REVOLUTION 8 // pulse/rev

class Motor {
    private:    
        volatile int encoderCount;
        volatile int encoderInit;
        Timer speedTimer;
        InterruptIn* encoder;
    public:
        Motor(PinName pin);
        void Pulse_Count();
        float getSpeed();
};

#endif
