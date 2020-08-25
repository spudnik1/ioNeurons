#include <RXNWheel.h>

// Class constructor 
Motor::Motor(PinName encoder_pin, PinName pwm_pin) : encoder{encoder_pin}, pwm(pwm_pin){
    encoder.rise(callback(this, &Motor::Pulse_Count));
    pwm.period_us(DRIVER_PWMPERIOD); 
}

// Interrupt function
void Motor::Pulse_Count(){
    encoderCount++;
    encoderInit = 1;
}

// Get the speed of the motor (rpm)
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

// Get the current draw of the motor 
// float Motor::getCurrent(){
//     // Find back EMF
//     float bEMF = BEMF_CONSTANT*(getSpeed()*2*PI);

//     return((V-2*bEMF)/(2*WINDING_RESISTANCE))
    
