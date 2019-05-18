#include "AD9910.h"

int main(){
    
    // defining fsysclks
    float fsysclk = 25.0e+6;
       
    initialize_pins();
    reset_board();
    
    // configuring CFR's
    write_register(CFR1, 0x00000002, 32);
    write_register(CFR2, 0x00400000, 32);
    write_register(CFR3, 0x17384000, 32);
    
    STP_write(Prof0, 1.0, 00.0, 10000000.0, fsysclk);
   
    return 0;
            
}