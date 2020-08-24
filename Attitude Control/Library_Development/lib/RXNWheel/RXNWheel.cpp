#include <mbed.h>
#include <RXNWheel.h>

// Class constructor and encoder initialization 
Motor::Motor(PinName pin) : encoder{pin}{
    encoder.rise(&Pulse_Count_Wrapper);
}

void Motor::Pulse_Count(){
  encoderCount++;
  encoderInit = 1;
}

float Motor::getSpeed(){
    
    // Initialization
    timeout_flag = 0;
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
     // Stop timer
    speedTimer.stop();
  
    // Return 0 if timed out
    if(timeout_flag == 1){
        return(0);
    }
  
    // Determine and return speed (rpm)
    else{
        return((1.0f/speedTimer.read_us())*60000000);
    }
}

Motor * myMotor;

void Pulse_Count_Wrapper()
{
  myMotor->Pulse_Count();
}

