#include <ADCS.h>
#include <Attitude_Model.h>


MPU9250 imu;
Motor xMotor(PE_2,PE_5);
Timer integralTimer;

// Motor yMotor(,);

int integralCount;

float r[3];
float v[3];
float quat[4];
float theta[3] = {0,0,0};
float w[3];
float b[3];

float prevW[3];

void attitudeInit(){
//---------------- same process as Kris Winer's example code ----------------- //
    uint8_t whoami = imu.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);  // Read WHO_AM_I register for MPU-9250
    printf("I AM 0x%x\n\r", whoami); printf("I SHOULD BE 0x71\n\r");
  
    if (whoami == 0x71) {// WHO_AM_I should always be 0x68 
        printf("MPU9250 WHO_AM_I is 0x%x\n\r", whoami);
        printf("MPU9250 is online...\n\r");
        wait_us(1);
        
        imu.resetMPU9250(); // Reset registers to default in preparation for device calibration
        
        imu.MPU9250SelfTest(SelfTest); // Start by performing self test and reporting values
        printf("x-axis self test: acceleration trim within : "); printFloat(SelfTest[0]); printf(" percent of factory value\n\r");  
        printf("y-axis self test: acceleration trim within : "); printFloat(SelfTest[1]); printf(" percent of factory value\n\r");
        printf("z-axis self test: acceleration trim within : "); printFloat(SelfTest[2]); printf(" percent of factory value\n\r");
        printf("x-axis self test: gyration trim within : "); printFloat(SelfTest[3]); printf(" percent of factory value\n\r");
        printf("y-axis self test: gyration trim within : "); printFloat(SelfTest[4]); printf(" percent of factory value\n\r");
        printf("z-axis self test: gyration trim within : "); printFloat(SelfTest[5]); printf(" percent of factory value\n\r");
        imu.calibrateMPU9250(gyroBias, accelBias); // Calibrate gyro and accelerometers, load biases in bias registers  
        printf("x gyro bias = "); printFloat(gyroBias[0]); printf("\n\r");
        printf("y gyro bias = "); printFloat(gyroBias[1]); printf("\n\r");
        printf("z gyro bias = "); printFloat(gyroBias[2]); printf("\n\r");
        printf("x accel bias = "); printFloat(accelBias[0]); printf("\n\r");
        printf("y accel bias = "); printFloat(accelBias[1]); printf("\n\r");
        printf("z accel bias = "); printFloat(accelBias[2]); printf("\n\r");
        wait_us(2000);
        imu.initMPU9250(); 
        printf("MPU9250 initialized for active data mode....\n\r"); // Initialize device for active mode read of acclerometer, gyroscope, and temperature
        imu.initAK8963(magCalibration);
        printf("AK8963 initialized for active data mode....\n\r"); // Initialize device for active mode read of magnetometer
        printf("Accelerometer full-scale range = "); printFloat(2.0f*(float)(1<<Ascale)); printf(" g\n\r");
        printf("Gyroscope full-scale range = "); printFloat(250.0f*(float)(1<<Gscale)); printf(" deg/s\n\r");
        if(Mscale == 0) printf("Magnetometer resolution = 14  bits\n\r");
        if(Mscale == 1) printf("Magnetometer resolution = 16  bits\n\r");
        if(Mmode == 2) printf("Magnetometer ODR = 8 Hz\n\r");
        if(Mmode == 6) printf("Magnetometer ODR = 100 Hz\n\r");
        wait_us(1000);
    }
   else {
        printf("Could not connect to MPU9250: \n\r");
        printf("%#x \n",  whoami);
        while(1); // Loop forever if communication doesn't happen
    }
    // ------------------------------------------------------------------------ //
    imu.getGres();
    integralTimer.reset();
}

void setAttitude(float roll, float pitch, float yaw){

}

void getDrift(){

}
// 
void getAttitude(){
    
    // Get ADC values from gyro data register
    imu.readGyroData(gyroCount); 
    
    // Convert ADC values to angular speed
    w[0] = (float)gyroCount[0]*gRes - gyroBias[0];
    w[1] = (float)gyroCount[1]*gRes - gyroBias[1];
    w[2] = (float)gyroCount[2]*gRes - gyroBias[2];

    // Determine integral in the case that timer has started
    if (integralTimer.read_ms() > 0){
        
        integralTimer.stop();

        // Integrate velocity curve using midpoint rule 
        theta[0]=((w[0]+prevW[0])/2)*(integralTimer.read_ms()/1000.0f)+theta[0];
        theta[1]=((w[1]+prevW[1])/2)*(integralTimer.read_ms()/1000.0f)+theta[1];
        theta[2]=((w[2]+prevW[2])/2)*(integralTimer.read_ms()/1000.0f)+theta[2];

        integralTimer.reset();
        
    }
    
    integralTimer.start();

    // Store past angular speed
    prevW[0] = w[0];
    prevW[1] = w[1];
    prevW[2] = w[2];
}

