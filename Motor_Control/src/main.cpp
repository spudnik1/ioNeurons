#include <mbed.h>

#define ADC123_IN11 PC_1 // FFC pin 15
#define TORQUE_CONSTANT 1.81 // mNm/A
#define BEMF_CONSTANT 0.19 // mV/min^-1
#define ENCODER_PULSECOUNT 1 // pulse/rev
#define WINDING_RESISTANCE 3.14 // ohms (THIS IS PHASE-PHASE)
#define DRIVER_PWMPERIOD 13 //us

AnalogIn potentiometer(ADC123_IN11);
PwmOut pwm(PE_5); // GPIO Pin FFC_1_3




float torqueSP;
float currentSP;
float speed;
float bEMF;
float current;
float voltage;
float error;
float dError;
float output;
int P;
int I;
int D;
int Torque;


int main() {

  pwm.period_us(DRIVER_PWMPERIOD); 
  
  while(1){
    // Start Control System Timer

    // Get Torque input (mNm)
      torqueSP = potentiometer.read();

    // Convert to current input (A)
      currentSP = torqueSP/TORQUE_CONSTANT;

    // Find actual current
      // Start Speed timer
      // Wait for 1 revolution
      for(int i = 0; i < ENCODER_PULSECOUNT; i++){
        while(1){
          // Wait for encoder pulse
          break;
        }
      }
      // Stop Speed Timer
      speed = 0;  // 2*pi rad / speed timer value 
      bEMF = BEMF_CONSTANT/speed;
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