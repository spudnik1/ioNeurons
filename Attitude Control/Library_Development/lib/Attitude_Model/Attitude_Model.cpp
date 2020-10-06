#include <Attitude_Model.h>

float inertia[3][3] = {{1,0,0}, {0,1,0}, {0,0,1}};

// Propagating the attitude model
void propAttitude(float* theta, float* w, float dt){

    float dTheta[3] = {0, 0, 0};
    float dW[3] = {0, 0, 0};
    
    dTheta[0] = w[0];
    dTheta[1] = w[1];
    dTheta[2] = w[2];

    // wDot
    
    // c      = x(d.kWheels); % Reaction wheel rates
    // hT     = d.inertia*w + d.inertiaRWA*(c + w);
    // wDot   = d.inertia\(tTotal - d.tRWA + Cross(w,hT));
    // cDot   = d.tRWA/d.inertiaRWA - wDot;
    // xDot(d.kWheels) = cDot;
    theta[0] = 0;
    theta[1] = 0;
    theta[2] = 0;
    
    w[0] = 0;
    w[0] = 0;
    w[0] = 0;
    // needs current state, and time step

}

/* m1 and m2 are pointers to the arrays where m1Dim and m2Dim are pointers to arrays which specify 
 * the dimensions of m1 and m2. m1Dim and m2Dim should be in the format of {rows, columns} */
void cross(float* m1, float* m2, int* m1Dim, int* m2Dim){
    

}

