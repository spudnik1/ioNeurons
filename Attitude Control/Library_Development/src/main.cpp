// Used to test functionality of the motor library
#include <mbed.h>
#include <RXNWheel.h>
// #include <Custom_Serial.h>
#include <MPU9250.h>



DigitalOut led(PD_4);

Motor motor(PE_2,PE_5);

MPU9250 imu;

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
//         motor.setVoltage(input);
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
int16_t gyroData[3];
float testReport[6];

float num;
char str[10];


int main(void)
{  
    printf("Started!\n");
    // motor.setVoltage(0.65);
    imu.MPU9250SelfTest(testReport);
    // imu.initMPU9250();
    // imu.calibrateMPU9250(gyroBias,accelBias); 
    
    for(int i = 0; i < 6; i++){
        printf("%d\n", (int)(testReport[i]*10000));
    }
    
    while(1){
        
        // imu.readGyroData(gyroData);
        // printf("%d, %d, %d\n", gyroData[0], gyroData[1], gyroData[2]);
        // thread_sleep_for(500);
        
    }
}
