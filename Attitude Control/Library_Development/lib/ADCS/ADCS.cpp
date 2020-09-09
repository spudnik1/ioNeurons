#include <ADCS.h>

MPU9250 imu;
Motor xMotor(PE_2,PE_5);
// MPU9250 imu;
// Motor xMotor(PE_2,PE_5);
// // Motor yMotor(,);

// float r[3];
// float v[3];
// float quat[4];
// float w[3];
// float b[3];

void attInit(){
//---------------- this comes from Kris Winer's main.cpp file ---------------- //
    uint8_t whoami = imu.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);  // Read WHO_AM_I register for MPU-9250
    printf("I AM 0x%x\n\r", whoami); printf("I SHOULD BE 0x71\n\r");
  
    if (whoami == 0x71) {// WHO_AM_I should always be 0x68 
        printf("MPU9250 WHO_AM_I is 0x%x\n\r", whoami);
        printf("MPU9250 is online...\n\r");
        wait_us(1);
        
        imu.resetMPU9250(); // Reset registers to default in preparation for device calibration
        
        imu.MPU9250SelfTest(SelfTest); // Start by performing self test and reporting values
        printf("x-axis self test: acceleration trim within : %f of factory value\n\r", SelfTest[0]);  
        printf("y-axis self test: acceleration trim within : %f of factory value\n\r", SelfTest[1]);  
        printf("z-axis self test: acceleration trim within : %f of factory value\n\r", SelfTest[2]);  
        printf("x-axis self test: gyration trim within : %f of factory value\n\r", SelfTest[3]);  
        printf("y-axis self test: gyration trim within : %f of factory value\n\r", SelfTest[4]);  
        printf("z-axis self test: gyration trim within : %f of factory value\n\r", SelfTest[5]);  
        imu.calibrateMPU9250(gyroBias, accelBias); // Calibrate gyro and accelerometers, load biases in bias registers  
        printf("x gyro bias = %f\n\r", gyroBias[0]);
        printf("y gyro bias = %f\n\r", gyroBias[1]);
        printf("z gyro bias = %f\n\r", gyroBias[2]);
        printf("x accel bias = %f\n\r", accelBias[0]);
        printf("y accel bias = %f\n\r", accelBias[1]);
        printf("z accel bias = %f\n\r", accelBias[2]);
        wait_us(2000);
        imu.initMPU9250(); 
        printf("MPU9250 initialized for active data mode....\n\r"); // Initialize device for active mode read of acclerometer, gyroscope, and temperature
        
        printf("AK8963 initialized for active data mode....\n\r"); // Initialize device for active mode read of magnetometer
        printf("Accelerometer full-scale range = %f  g\n\r", 2.0f*(float)(1<<Ascale));
        printf("Gyroscope full-scale range = %f  deg/s\n\r", 250.0f*(float)(1<<Gscale));
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
// ---------------------------------------------------------------------------- //
}

// void attInit(){
// //---------------- this comes from Kris Winer's main.cpp file ---------------- //
//     uint8_t whoami = imu.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);  // Read WHO_AM_I register for MPU-9250
//     printf("I AM 0x%x\n\r", whoami); printf("I SHOULD BE 0x71\n\r");
  
//     if (whoami == 0x71) {// WHO_AM_I should always be 0x68 
//         printf("MPU9250 WHO_AM_I is 0x%x\n\r", whoami);
//         printf("MPU9250 is online...\n\r");
//         wait_us(1);
        
//         imu.resetMPU9250(); // Reset registers to default in preparation for device calibration
        
//         imu.MPU9250SelfTest(SelfTest); // Start by performing self test and reporting values
//         printf("x-axis self test: acceleration trim within : %f of factory value\n\r", SelfTest[0]);  
//         printf("y-axis self test: acceleration trim within : %f of factory value\n\r", SelfTest[1]);  
//         printf("z-axis self test: acceleration trim within : %f of factory value\n\r", SelfTest[2]);  
//         printf("x-axis self test: gyration trim within : %f of factory value\n\r", SelfTest[3]);  
//         printf("y-axis self test: gyration trim within : %f of factory value\n\r", SelfTest[4]);  
//         printf("z-axis self test: gyration trim within : %f of factory value\n\r", SelfTest[5]);  
//         imu.calibrateMPU9250(gyroBias, accelBias); // Calibrate gyro and accelerometers, load biases in bias registers  
//         printf("x gyro bias = %f\n\r", gyroBias[0]);
//         printf("y gyro bias = %f\n\r", gyroBias[1]);
//         printf("z gyro bias = %f\n\r", gyroBias[2]);
//         printf("x accel bias = %f\n\r", accelBias[0]);
//         printf("y accel bias = %f\n\r", accelBias[1]);
//         printf("z accel bias = %f\n\r", accelBias[2]);
//         wait_us(2000);
//         imu.initMPU9250(); 
//         printf("MPU9250 initialized for active data mode....\n\r"); // Initialize device for active mode read of acclerometer, gyroscope, and temperature
        
//         printf("AK8963 initialized for active data mode....\n\r"); // Initialize device for active mode read of magnetometer
//         printf("Accelerometer full-scale range = %f  g\n\r", 2.0f*(float)(1<<Ascale));
//         printf("Gyroscope full-scale range = %f  deg/s\n\r", 250.0f*(float)(1<<Gscale));
//         if(Mscale == 0) printf("Magnetometer resolution = 14  bits\n\r");
//         if(Mscale == 1) printf("Magnetometer resolution = 16  bits\n\r");
//         if(Mmode == 2) printf("Magnetometer ODR = 8 Hz\n\r");
//         if(Mmode == 6) printf("Magnetometer ODR = 100 Hz\n\r");
//         wait_us(1000);
//     }
//    else {
//         printf("Could not connect to MPU9250: \n\r");
//         printf("%#x \n",  whoami);
//         while(1); // Loop forever if communication doesn't happen
//     }
// // ---------------------------------------------------------------------------- //
// }

// void setAttitude(float roll, float pitch, float yaw){

// }

// float* getAttitude(){
//     static float attitudeData[3];

//     // Read gyroscope
//     imu.readGyroData(gyroCount);
    
//     // Apply scaling
//     // look at this again, its a signed int
//     gx = gyroCount[0]*gRes;
//     gy = gyroCount[0]*gRes;
//     gz = gyroCount[0]*gRes;

//     // Store as velocity
//     v[0] = gx;
//     v[1] = gy;
//     v[2] = gz;

//     // Get position
//     r[0] = 0*v[0];
//     r[1] = 0*v[1];
//     r[2] = 0*v[2];

//     return(attitudeData);
// }