#include <mbed.h>

#define ADC123_IN11 PC_1 // FFC pin 15
AnalogIn potentiometer(ADC123_IN11);
DigitalOut ledB(PD_4);


int main() {
  while(1) {
    if(potentiometer.read() >= 0.5f){
      ledB.write(1);
    }
    else{
      ledB.write(0);
    }
  }
}