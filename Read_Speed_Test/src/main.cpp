#include <mbed.h>

#define ENCODER_REVOLUTION 16 // pulse/rev

int pulseCount = 0;

DigitalOut ledB(PD_4);
InterruptIn encoder(PE_2,PullDown); // GPIO Pin FFC_1_1
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
}

float getSpeed(){
  int status = 0;
  Speed_Timer.reset();
  Speed_Timer.start();
  // Determine time for 1 revolution
    pulseCount = 0;
    while(1){
      if(pulseCount >= ENCODER_REVOLUTION){
        Speed_Timer.stop();
        status = 1;
        break;
      }
      if(Speed_Timer.read() > 1){
        break;
      }
    }
  // Calculate Speed and output
    if(status == 1){
      return((1.0f/Speed_Timer.read_us())*60000000); // rpm 
    }
    else{
      return(0);
    }
}