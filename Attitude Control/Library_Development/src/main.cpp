// Used to test functionality of the motor library
#include <mbed.h>
// #include <RXNWheel.h>
// #include <Custom_Serial.h>
// #include <MPU9250.h>
#include <ADCS.h>

DigitalOut led(PD_4);

// ----- Want to implement this into Custom_Serial library, but not working. ------

    // Specify different pins to test printing on UART other than the console UART.
    #define TARGET_TX_PIN                                                     PA_9
    #define TARGET_RX_PIN                                                     PA_10
    
    // Create a BufferedSerial object to be used by the system I/O retarget code.
    static BufferedSerial serial_port(TARGET_TX_PIN, TARGET_RX_PIN, 9600);

    FileHandle *mbed::mbed_override_console(int fd)
    {
        return &serial_port;
    }


// --------------------------------------------------------------------------------


//---------------//
// MOTOR TESTING //
//---------------//

// Sets the motor voltage to 0 V (DC = 50%), then prompts for new setpoint over serial

// float input = 0.5;
// int main(void){
//     printf("started!\n");
//     while(1){
//         xMotor.setVoltage(input);
//         printf("set!\n");
//         scanf("%f",&input);
//     }
// }


//---------------//
//  IMU TESTING  //
//---------------//

// Reads the WHO_AM_I and prints to serial. 

// char test; 
// int main(void)
// {  
//     printf("Started!\n", test);
//     test = imu.readByte(MPU9250_ADDRESS,WHO_AM_I_MPU9250);
//     printf("%d\n", test);
// }

// Reads the gyroscope data





void attInit();
// void setAttitude(float roll, float pitch, float yaw);
// float* getAttitude();

int main(void)
{  
 attInit();
}
