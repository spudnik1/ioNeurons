#include "mbed.h"
I2C i2c(PB_11, PB_10); // Data, Clock

DigitalOut led1(PD_4);
DigitalOut led2(PD_5);

int address = 0x68<<1;
char ID_reg[1]= {0x75};
char data[1];

int test = 1;

int main() {

    i2c.frequency(400000); 

    test = i2c.write(address, ID_reg, 1,true);
    i2c.read(address,data,1,false);
    
    if (data[0] == 0x71){
        led1.write(true); // blue
    }
    else{
        led2.write(true); // green
        }

}
