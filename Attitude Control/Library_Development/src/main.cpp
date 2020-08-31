// Used to test functionality of the motor library
#include <mbed.h>
#include <RXNWheel.h>
#include <Custom_Serial.h>
#include <MPU9250.h>

DigitalOut led(PD_4);

Motor motor(PE_2,PE_5);


// 

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

int main(void)
{
    // print to the console using the `serial_port` object.
    while(1){
        printf("Mbed OS version");
    }
}





