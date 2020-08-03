#include "mbed.h"

void readRegister(int address, const char* reg, char* data);

I2C i2c(PB_11, PB_10); // Data, Clock

DigitalOut led1(PD_4);
DigitalOut led2(PD_5);

int address = 0x68;
const char ID_reg[1] = {0x75};
char data[1];

int main() {

    // Set Clock Frequency
    i2c.frequency(400000); 

    readByte(address, ID_reg, data);

    if (data[0] == 0x71){
        led1.write(true); // blue
    }
    else{
        led2.write(true); // green
    }
}
void readByte(int address, const char* reg, char* data){
    i2c.write(address<<1,reg,1,true);
    i2c.read(address<<1,data,1,false);
    return;
}

void writeByte(int address, const char* reg, char data){
    i2c.write(address<<1,reg,1,false);
    i2c.write(data);
    return;
}