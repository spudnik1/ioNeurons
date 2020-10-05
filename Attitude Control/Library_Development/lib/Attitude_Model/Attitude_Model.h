#ifndef ATTMOD_H
#define ATTMOD_H

extern float r[3];
extern float v[3];
extern float quat[4];
extern float theta[3];
extern float w[3];
extern float b[3];

void propAttitude(float* theta, float* w, float dt);

#endif