#include "mbed.h"

SPI spi(p5, p6, p7); // MOSI MISO SCLK
DigitalOut cs(p8);  // its necessary to keep it low during data transfer
DigitalOut io_reset(p9); // its necessary to keep it low during data transfer
DigitalOut io_update(p15);  // depends os the 23 bit of CFR2
DigitalOut MASTER_RESET(p23);
DigitalOut EXT_PWR_DWN(p27);
DigitalOut prof0(p16);
DigitalOut prof1(p17);
DigitalOut prof2(p19);
DigitalOut osk(p11);    //  In this case, osk is inoperative
DigitalIn ctrl(p30);

int main(){
       
    //  valores iniciais de pinos
        cs = 0;
        
        io_reset = 0;
        io_update = 0;
        
        prof0 = 0;
        prof1 = 0;
        prof2 = 0;
        
        osk = 0;
    
    // reset inicial
        EXT_PWR_DWN = 0;
        MASTER_RESET = 1;
        wait(2);
        MASTER_RESET = 0;
        
        wait(1);
        
    //  spi configuration
        spi.format(8,0);
        spi.frequency(25000000);
        
    // CFR1
        spi.write(0x00);    //  address
        spi.write(0x00);    //  MSB
        spi.write(0x00);
        spi.write(0x00);
        spi.write(0x02);    //  LSB
        
    //  I/O UPDATE
        io_update = 1;
        wait_us(100);
        io_update = 0;
        
    // CFR2
        spi.write(0x01);    //  address
        spi.write(0x00);    //  MSB
        spi.write(0x40);
        spi.write(0x00);
        spi.write(0x00);    //  LSB
    
    //  I/O UPDATE
        io_update = 1;
        wait_us(100);
        io_update = 0;
        
    // CFR3
        spi.write(0x02);    //  address
        spi.write(0x17);    //  MSB
        spi.write(0x38);
        spi.write(0x40);
        spi.write(0x00);    //  LSB
    
    //  I/O UPDATE
        io_update = 1;
        wait_us(100);
        io_update = 0;
        
    //  Profile 0
        spi.write(0x0E);    //  address
        spi.write(0x3F);    //  MSB     ASF - MSB
        spi.write(0xFF);    //          ASF - LSB
        spi.write(0x00);    //          POW - MSB
        spi.write(0x00);    //          POW - LSB
        spi.write(0x33);       //          FTW - MSB
        spi.write(0x33);    //          FTW - LSB
        spi.write(0x33);   //          FTW - MSB
        spi.write(0x33);   //  LSB     FTW - LSB
            
        //  I/O UPDATE
        io_update = 1;
        wait_us(100);
        io_update = 0;
  
        //  Profile 1
        spi.write(0x0F);    //  address
        spi.write(0x3F);    //  MSB     ASF - MSB
        spi.write(0xFF);    //          ASF - LSB
        spi.write(0x00);    //          POW - MSB
        spi.write(0x00);    //          POW - LSB
        spi.write(0x19);       //          FTW - MSB
        spi.write(0x99);    //          FTW - LSB
        spi.write(0x99);   //          FTW - MSB
        spi.write(0x99);   //  LSB     FTW - LSB
            
        //  I/O UPDATE
        io_update = 1;
        wait_us(100);
        io_update = 0;
                
        //  Profile 2
        spi.write(0x10);    //  address
        spi.write(0x3F);    //  MSB     ASF - MSB
        spi.write(0xFF);    //          ASF - LSB
        spi.write(0x00);    //          POW - MSB
        spi.write(0x00);    //          POW - LSB
        spi.write(0x28);       //          FTW - MSB
        spi.write(0xF5);    //          FTW - LSB
        spi.write(0xC2);   //          FTW - MSB
        spi.write(0x8C);   //  LSB     FTW - LSB
            
        //  I/O UPDATE
        io_update = 1;
        wait_us(100);
        io_update = 0;
                
        //  Profile 3
        spi.write(0x11);    //  address
        spi.write(0x3F);    //  MSB     ASF - MSB
        spi.write(0xFF);    //          ASF - LSB
        spi.write(0x00);    //          POW - MSB
        spi.write(0x00);    //          POW - LSB
        spi.write(0x33);       //          FTW - MSB
        spi.write(0x33);    //          FTW - LSB
        spi.write(0x33);   //          FTW - MSB
        spi.write(0x33);   //  LSB     FTW - LSB
            
        //  I/O UPDATE
        io_update = 1;
        wait_us(100);
        io_update = 0;
            
        //  Profile 4
        spi.write(0x12);    //  address
        spi.write(0x3F);    //  MSB     ASF - MSB
        spi.write(0xFF);    //          ASF - LSB
        spi.write(0x00);    //          POW - MSB
        spi.write(0x00);    //          POW - LSB
        spi.write(0x3D);       //          FTW - MSB
        spi.write(0x70);    //          FTW - LSB
        spi.write(0xA3);   //          FTW - MSB
        spi.write(0xD2);   //  LSB     FTW - LSB
            
        //  I/O UPDATE
        io_update = 1;
        wait_us(100);
        io_update = 0;
                
        //  Profile 4
        spi.write(0x13);    //  address
        spi.write(0x3F);    //  MSB     ASF - MSB
        spi.write(0xFF);    //          ASF - LSB
        spi.write(0x00);    //          POW - MSB
        spi.write(0x00);    //          POW - LSB
        spi.write(0x51);       //          FTW - MSB
        spi.write(0xEB);    //          FTW - LSB
        spi.write(0x85);   //          FTW - MSB
        spi.write(0x18);   //  LSB     FTW - LSB
        
        //  I/O UPDATE
        io_update = 1;
        wait_us(100);
        io_update = 0;                
                
        //  Profile 6
        spi.write(0x14);    //  address
        spi.write(0x3F);    //  MSB     ASF - MSB
        spi.write(0xFF);    //          ASF - LSB
        spi.write(0x00);    //          POW - MSB
        spi.write(0x00);    //          POW - LSB
        spi.write(0x66);       //          FTW - MSB
        spi.write(0x66);    //          FTW - LSB
        spi.write(0x66);   //          FTW - MSB
        spi.write(0x66);   //  LSB     FTW - LSB
            
        //  I/O UPDATE
        io_update = 1;
        wait_us(100);
        io_update = 0;
                
        //  Profile 7
        spi.write(0x15);    //  address
        spi.write(0x3F);    //  MSB     ASF - MSB
        spi.write(0xFF);    //          ASF - LSB
        spi.write(0x00);    //          POW - MSB
        spi.write(0x00);    //          POW - LSB
        spi.write(0x66);       //          FTW - MSB
        spi.write(0x66);    //          FTW - LSB
        spi.write(0x66);   //          FTW - MSB
        spi.write(0x66);   //  LSB     FTW - LSB
            
        //  I/O UPDATE
        io_update = 1;
        wait_us(100);
        io_update = 0;
                
                //  PROFILE UPDATE
                while(1){                    
                    if(ctrl == 0){
                        prof2 = 0;
                        prof1 = 0;
                        prof0 = 0;     
                    }
                    else{
                        prof2 = 1;
                        prof1 = 1;
                        prof0 = 1;
                    }
                }
            
}
