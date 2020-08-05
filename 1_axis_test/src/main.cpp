#include "mbed.h"

#define MPU_ADDRESS 0x68

#define WHO_AM_I    0x75
#define PWR_MGMT_1  0x6B

#define MPU_ID 0x71

#define BLINKING_RATE 100

void readByte(int address, char subaddress, char* data);
void writeByte(int address, char subaddress, char* data);

I2C i2c(PB_11, PB_10); // Data, Clock

DigitalOut ledB(PD_4);
DigitalOut ledG(PD_5);

//int address = 0x68;
//const char ID_reg[1] = {0x75};
char data[1];

int main() {
 // example
    // Set Clock Frequency
    i2c.frequency(400000); 

    // Should scan the I2C line for devices
    
    // Read the chip ID from the WHO_AM_I register
    readByte(MPU_ADDRESS,WHO_AM_I, data);

    if (data[0] == MPU_ID){
        for(int i = 0; i < 6; i++){
            ledB.write(!ledB.read()); 
            thread_sleep_for(BLINKING_RATE);   
        }
    }
    else{
        ledG.write(1);
    }

}
void readByte(int address, char subaddress, char* data){
    //char subaddress[1] = {reg}; // i2c.write expects a char pointer
    i2c.write(address<<1,&subaddress,1,true);
    i2c.read(address<<1,data,1,false);
    return;
}

void writeByte(int address, char subaddress, int data){
    i2c.write(address<<1,&subaddress,1,true);
    i2c.write(data);
    return;
}

void calibration(){
    
    // reset device
    writeByte(MPU_ADDRESS,PWR_MGMT_1,0x80);
    


}