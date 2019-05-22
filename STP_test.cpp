#include "AD9910.h"

DigitalOut  myled0(LED1);
DigitalOut  myled1(LED2);
DigitalOut  myled2(LED3);
DigitalOut  myled3(LED4);

int main(){
    
    // defining fsysclks
    float fsysclk = 25.0e+6;
       
    initialize_pins();
    reset_board();
    
    // configuring CFR's
    write_register(CFR1, 0x00000002, 32);
    write_register(CFR2, 0x00400800, 32);
    write_register(CFR3, 0x1738C000, 32);
    
    STP_write(Prof4, 1.0, 00.0, 10.0E+6, fsysclk);
    update_profile(0,1,0);
   
    while(1){
        wait(0.5);
        myled0  =   1;
        myled1  =   1;
        myled2  =   1;
        myled3  =   1;
        wait(0.5);
        myled0  =   0;
        myled1  =   0;
        myled2  =   0;
        myled3  =   0;
    }
            
}
