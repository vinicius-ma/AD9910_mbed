#define IO_Update_Rate 0x04
#define FTW 0x07
#define POW 0x08
#define ASF 0x09
#define Multichip_Sync 0x0A
#define Dig_Ramp_Limit_Reg 0x00B
#define Dig_Ramp_Step_Size 0x0C

#define Single_Tone_Prof_0 0x0E
#define Single_Tone_Prof_1 0x0F

int main(){
    
    float fsysclk = 25000000;
    
    SPI         spi(p5, p6, p7);        // MOSI MISO SCLK
    
    DigitalOut  cs(p8);                 // its necessary to keep it low during data transfer
    DigitalOut  io_reset(p9);           // its necessary to keep it low during data transfer
    DigitalOut  io_update(p15);         // depends os the 23 bit of CFR2
    DigitalOut  MASTER_RESET(p23);
    DigitalOut  EXT_PWR_DWN(p27);
    DigitalOut  osk(p11);               //  In this case, osk can be innoperative
    DigitalIn   ctrl(p30);
    DigitalOut  prof0(p16);
    DigitalOut  prof1(p17);
    DigitalOut  prof2(p19);
    
    configure_spi(8, 0, fsysclk);    
    initialize_pins();
    reset_board();
    
    write_register(CFR1, 0x00000002, 32);
    write_register(CFR2, 0x00400000, 32);
    write_register(CFR3, 0x17384000, 32);
    
    write_single_tone_register(Single_Tone_Prof_0, 1.0, 0.0, 500000001.0, fsysclk);
    write_single_tone_register(Single_Tone_Prof_1, 1.0, 0.0, 1000000001.0, fsysclk);
    
    while(1){                    
        if(ctrl == 0)
            update_profile(0, 0, 0);
                    
        else
            update_profile(0, 0, 1);
    }
            
}
