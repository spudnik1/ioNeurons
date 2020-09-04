#ifndef RXNWHEEL_H
#define RXNWHEEL_H

#include <mbed.h>

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

#define BEMF_CONSTANT 0.19 // mV/(rev/min)
#define ENCODER_REVOLUTION 8 // pulse/rev
#define TORQUE_CONSTANT 1.81 // mNm/A
#define WINDING_RESISTANCE 3.14 // ohms (THIS IS PHASE-PHASE)
#define DRIVER_PWMPERIOD 13 // us
#define INPUT_VOLTAGE 15.00 // V

#ifndef PI
#define PI 3.14159265359
#endif

class Motor {
    private:    
        volatile int encoderCount;
        volatile int encoderInit;
        volatile int timeout_flag;
        Timer speedTimer;
        InterruptIn encoder;
        PwmOut pwm; // GPIO Pin FFC_1_3
    public:
        Motor(PinName encoder_pin, PinName pwm_pin);
        void Pulse_Count();
        float getSpeed();
        void setVoltage(float);
        float getCurrent();
        
};

#endif
