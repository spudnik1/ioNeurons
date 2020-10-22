#include <Attitude_Model.h>
#include <mbed.h>

float Is[3][3] = {{1,0,0}, {0,1,0}, {0,0,1}};
float Iw[3][3] = {{1,0,0}, {0,1,0}, {0,0,1}};

// Propagating the attitude model
void propAttitude(float* theta, float* w, float* wW, float dt){

    float thetaDot[3] = {0, 0, 0};
    float wDot[3] = {0, 0, 0};
    float hW[3];
    float hS[3];
    float hT[3];
    
    thetaDot[0] = w[0];
    thetaDot[1] = w[1];
    thetaDot[2] = w[2];

    // Satellite angular momentum
    hS[0] = Is[0][0]*w[0] + Is[1][0]*w[1] + Is[2][0]*w[2];
    hS[1] = Is[0][1]*w[0] + Is[1][1]*w[1] + Is[2][1]*w[2];
    hS[2] = Is[0][2]*w[0] + Is[1][2]*w[1] + Is[2][2]*w[2];

    // Wheel angular momentum
    hW[0] = Iw[0][0]*(w[0]+wW[0]) + Iw[1][0]*(w[1]+wW[1]) + Iw[2][0]*(w[2]+wW[2]);
    hW[1] = Iw[0][1]*(w[0]+wW[0]) + Iw[1][1]*(w[1]+wW[1]) + Iw[2][1]*(w[2]+wW[2]);
    hW[2] = Iw[0][2]*(w[0]+wW[0]) + Iw[1][2]*(w[1]+wW[1]) + Iw[2][2]*(w[2]+wW[2]);

    // Total angular momentum
    hT[0] = hS[0] + hW[0];
    hT[1] = hS[1] + hW[1];
    hT[2] = hS[2] + hW[2];

    // wDot[0] =  w[0];
    // wDot[1]
    // wDot[2]



    // c      = x(d.kWheels); % Reaction wheel rates
    // hT     = d.inertia*w + d.inertiaRWA*(c + w);
    // wDot   = d.inertia\(tTotal - d.tRWA + Cross(w,hT));
    // cDot   = d.tRWA/d.inertiaRWA - wDot;
    // xDot(d.kWheels) = cDot;

    // wDot[0] = ;
    wDot[1] = 0;
    wDot[2] = 0;

}

/* */
void multiply(float* m1, float* m2){
    int rows = sizeof(m1)/sizeof(m1[0]);

    int cols = sizeof(m2[0])/sizeof(float);
    printf("%d row %d col", rows, cols);
}

void divide(){

}

void vCross(float** m1, float** m2){
    

}

