#include <mbed.h>
#include <motorlibrary.h>

DigitalOut led(PD_5);

int main(){
  test_function();
  if (test_variable == 1){
    led.write(1);
  }
}

