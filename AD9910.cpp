#include "AD9910.h"

DigitalOut  cs(p10);        // its necessary to keep it low during data transfer
DigitalOut  io_reset(p9);   // its necessary to keep it low during data transfer
DigitalOut  osk(p11);
DigitalOut  io_update(p17); // depends os the 23 bit of CFR2
DigitalOut  p_0(p18);
DigitalOut  p_1(p19);
DigitalOut  p_2(p20);
DigitalOut  MASTER_RESET(p15);
DigitalOut  EXT_PWR_DWN(p14);
DigitalIn   ctrl(p30);
DigitalOut  myled(LED1);
DigitalOut  myled2(LED2);

//  amp is normalized (between 0 and 1) - amplitude scale
//  phase is in degree

// write single tone register from amplitude, phase and frequency
void STP_write (int address, float amp,float phase,float fout,float fsysclk){
        
        uint64_t register_value = STP_get_reg(amp, phase, fout, fsysclk);
        write_register(address, register_value, 64);
}

// returns the register to be used at the single tone profile's registers (AD9910)
    uint64_t STP_get_reg(float amp,float phase,float fout,float fsysclk){
        
        uint64_t reg, aux;
        long double aux_float;
        
        reg = 0x00;
        
        // calculating ASF
        aux_float = amp*pow(2.0,14.0);
        aux = fround(aux_float);
        
        // concatenating ASF to final register
        aux<<=48;
        reg = reg|aux;
        
        // calculating POW    
        aux_float = phase*pow(2.0,16.0)/360;
        aux = fround(aux_float);
        
        // concatenating POW to final register
        aux<<=32;
        reg = reg|aux;
            
        // calculating FTW    
        aux_float = ((double) fout/fsysclk)*(pow(2.0,32.0));
        aux = fround(aux_float);
        
        // concatenating FTW to final register
        reg = reg|aux;
        
        return reg;   
    }

// returns number's nearest integer
    uint64_t fround(double nfloat){
        
        uint64_t nint;

        if( -(nfloat - (double)ceil(nfloat)) < (nfloat - (double)floor(nfloat))){
            nint = (uint64_t) ceil(nfloat);
        }
        else{
            nint = (uint64_t) floor(nfloat);
        }
        
        return nint;    
    }

// returns an array with the register's bytes separated (MSB)
    uint64_t *get_byte(uint64_t data, int data_size){
        
        int number_of_bytes;                      
        int i = 0;
        
        number_of_bytes = (int)fround(data_size/8);
        uint64_t filter = 0xFF*pow(2.0,8.0*(number_of_bytes-1));
        
        uint64_t *bytes_array = (uint64_t*)malloc(sizeof(uint64_t)*number_of_bytes);
        
        while(i < number_of_bytes){
            
            bytes_array[i] = (data & filter)>>((number_of_bytes-i-1)*8);            
            filter>>= 8;            
            i++;
        }
        
    return bytes_array;        
        
}
    
void update_profile(int p0, int p1, int p2){
  
    p_0 = p0;
    p_1 = p1;
    p_2 = p2;
    
    io_update_pulse(100);
    
}

// reset the AD9910 board
void reset_board(){
    
    EXT_PWR_DWN = 0;
    MASTER_RESET = 1;
    wait(1);
    MASTER_RESET = 0;
    wait(0.5);
 
}

// initialize pins
void initialize_pins(){
        
        cs = 1;        
        io_reset = 0;
        io_update = 0;        
        p_0 = 0;
        p_1 = 0;
        p_2 = 0;        
        osk = 0;
   
}

void io_update_pulse(float time_us){
        
        io_update = 1;
        wait_us(time_us);
        io_update = 0;
        
}

void write_register(int address, uint64_t data, int data_size){
        
        int i;
        uint64_t *data_bytes = get_byte(data, data_size);
        
        // SPI configuration
            SPI spi(p5, p6, p7);            // SPI: MOSI MISO SCLK
            spi.format(spi_bits, spi_mode);
            spi.frequency(spi_freq);
            
        cs = 0;
        
        spi.write(address);    //  address
        
        for(i=0; i+1 <= data_size/8; i++){
            spi.write(data_bytes[i]);
        }
        
        free(data_bytes);
        
        cs = 1;
        
        io_update_pulse(100);
}