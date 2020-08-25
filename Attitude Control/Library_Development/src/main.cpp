// Used to test functionality of the motor library
#include <mbed.h>
#include <RXNWheel.h>

DigitalOut led(PD_4);

Motor motor(PE_2);

void function();

int main(){
    // Set up

    // Main loop
    while(1){
        if(motor.getSpeed()>=7000){
            led.write(1);
        }
        else{
            led.write(0);
        }
    }
}




