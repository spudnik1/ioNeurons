#include <mbed.h>

#define ENCODER_REVOLUTION 8 // pulse/rev

volatile int pulseCount = 0;
volatile int encoderInit = 0;

DigitalOut testpin(PE_5);
DigitalOut ledG(PD_5);
DigitalOut ledB(PD_4);
InterruptIn encoder(PE_2); // GPIO Pin FFC_1_1

Timer Speed_Timer;

void encoder_count();
float getSpeed();

int main() {

  encoder.rise(&encoder_count);
  while(1) {
    if(getSpeed()>=7000){
      ledB.write(1);
    }
    else{
      ledB.write(0);
    }
  }
}

void encoder_count(){
  pulseCount++;
  encoderInit = 1;
}

float getSpeed(){
  // Initialization
  int timeout_flag = 0;
  encoderInit = 0;
  Speed_Timer.reset();
  
  // Wait for the beginning of a pulse
  while(!encoderInit);
  
  // Start the timer and initialize count
  Speed_Timer.start();
  pulseCount = 0;
  
  // Wait until one revolution has passed
  while(pulseCount < ENCODER_REVOLUTION){
    // Timeout if the motor is going less than 1 rps
    if(Speed_Timer.read() > 1){
      timeout_flag = 1;
      break;
    }
  }
  
  // Stop timer
  Speed_Timer.stop();
  
  // Return 0 if timed out
  if(timeout_flag == 1){
    return(0);
  }
  
  // Determine and return speed (rpm)
  else{
    return((1.0f/Speed_Timer.read_us())*60000000);
  }
}