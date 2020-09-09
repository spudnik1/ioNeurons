#ifndef ADCS_H
#define ADCS_H

#include <mbed.h>
#include <RXNWheel.h>
#include <MPU9250.h>

extern MPU9250 imu;
extern Motor xMotor;
// Motor yMotor;

// extern MPU9250 imu;
// extern Motor xMotor;
// extern Motor yMotor;

// extern float r[3];
// extern float v[3];
// extern float quat[4];
// extern float w[3];
// extern float b[3];

void attInit();
// void attInit();
// void setAttitude(float roll, float pitch, float yaw);
// float* getAttitude();

#endif