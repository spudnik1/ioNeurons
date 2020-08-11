#include <mbed.h>
#include <math.h>

#define ADC123_IN11 PC_1 // FFC pin 15
#define TORQUE_CONSTANT 1.81 // mNm/A
#define BEMF_CONSTANT 0.19 // mV/min^-1
#define ENCODER_REVOLUTION 1 // pulse/rev
#define WINDING_RESISTANCE 3.14 // ohms (THIS IS PHASE-PHASE)
#define DRIVER_PWMPERIOD 13 //us
#define PI 3.1415926535897
AnalogIn potentiometer(ADC123_IN11);
PwmOut pwm(PE_5); // GPIO Pin FFC_1_3
InterruptIn encoder(PE_2,PullDown); // GPIO Pin FFC_1_1
Timer Speed_Timer;
Timer Control_Timer;

float torqueSP;
float currentSP;
float speed;
float bEMF=0;
float current;
float voltage=0;
float error;
float dError;
float output;
int P;
int I;
int D;
int Torque;
int pulseCount = 0;

void encoder_count();

int main() {

  // Setup
    pwm.period_us(DRIVER_PWMPERIOD); 
    encoder.rise(&encoder_count);


  // Initial Output

  

  while(1){
    
    // Start Control System Timer
    
    // Get Torque Setpoint (mNm)
      torqueSP = potentiometer.read();
    
    // Convert to current SetPoint (A)
      currentSP = torqueSP/TORQUE_CONSTANT;

    // Get current
      speed = getSpeed();
      bEMF = (BEMF_CONSTANT/speed)/1000;
      current = (voltage-bEMF)/WINDING_RESISTANCE;

    // Get Error
      dError = (currentSP-current)-error;
      error = error+dError;

    // Controller
      // Stop Control System Timer
      output = P*error + D*0; //replace 0 with dError / control system timer value

    // Send controller output to drive
    pwm.write(output);
  }
}

void encoder_count(){
  pulseCount++;
}

float getSpeed(){
  float speed;
  Speed_Timer.reset();
  Speed_Timer.start();
  // Determine time for 1 revolution
    pulseCount = 0;
    while(1){
      if(pulseCount >= ENCODER_REVOLUTION){
        Speed_Timer.stop();
        speed = (1.0f/Speed_Timer.read_us())*60000000;  // rpm 
        break;
      }
      if(Speed_Timer.read() > 1){
        Speed_Timer.stop();
        Speed_Timer.reset();
        speed = 0;
        break;
      }
    }
  // Calculate Speed and output
    if(Speed_Timer.read_us() > 0){
      speed = (1.0f/Speed_Timer.read_us())*60000000;
    }
    else{
      speed = 0;
    }
    return(speed);
}