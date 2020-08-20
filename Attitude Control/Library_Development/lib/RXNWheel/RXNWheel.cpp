#include <mbed.h>
#include <RXNWheel.h>

Motor::Motor(PinName pin){
    encoder = new InterruptIn(pin);
}
void Motor::Pulse_Count(){
  encoderCount++;
  encoderInit = 1;
}

float Motor::getSpeed(){
    
    // Initialization
    int timeout_flag = 0;
    encoderInit = 0;
    speedTimer.reset();
    
    // Wait for the beginning of a pulse
    while(!encoderInit);
    
    // Start the timer and initialize count
    speedTimer.start();
    encoderCount = 0;
    
    // Wait until one revolution has passed
    while(encoderCount < ENCODER_REVOLUTION){
        // Timeout if the motor is going less than 1 rps
        if(speedTimer.read() > 1){
        timeout_flag = 1;
        break;
        }
    }
}