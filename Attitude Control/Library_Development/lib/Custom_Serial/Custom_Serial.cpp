#include <Custom_Serial.h>

void printFloat(float input){
    
    int preDec = abs(int(input));
    int postDec = abs(int(input*100)) - preDec * 100;

    if (input >= 0){
        printf("%d.%d",preDec,postDec);
    }
    else{
        printf("-%d.%d",preDec,postDec);
    }
}