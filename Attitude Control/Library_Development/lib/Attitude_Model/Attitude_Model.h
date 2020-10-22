#ifndef ATTMOD_H
#define ATTMOD_H


// Variables found the ADCS.h
extern float r[3];
extern float v[3];
extern float quat[4];
extern float theta[3];
extern float w[3];
extern float b[3];

// Variables found the Attitude_Model.h

void propAttitude(float* theta, float* w, float dt);

void multiply(float* m1, float* m2);


#endif

