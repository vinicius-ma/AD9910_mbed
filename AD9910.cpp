#include "mbed.h"
#include "AD9910.h"

//  amp é dado em uma valor entre 0 e 1 (escala de amplitude)
//  phase é dado em graus
//  fout é a freq de saida
// fsysclk é a freq de referencia do sistema (typ 25 MHz)

// write single tone register from amplitude, phase and frequency
void write_single_tone_register (int address, float amp,float phase,float fout,float fsysclk){
        
        int register_value = get_single_tone_register(amp, phase, fout, fsysclk);
        
        write_register(address, register_value, 64);        
}

// returns the register to be used at the single tone profile's registers (AD9910)
    int get_single_tone_register (float amp,float phase,float fout,float fsysclk){
        
        long int reg, aux;
        double aux_float;
        
        reg = 0x00000000;
        
        // calculating ASF
        aux_float = amp*pow(2.0,14.0);
        aux = rounding_to_integer(aux_float);
        
        // concatenating ASF to final register
        reg = reg | (aux<<61);        
            
        // calculating POW    
        aux_float = phase*pow(2.0,16.0)/360;
        aux = rounding_to_integer(aux_float);
        
        // concatenating POW to final register
        reg = reg | (aux<<47);        
            
        // calculating FTW    
        aux_float = fout*pow(2.0,32.0)/fsysclk;
        aux = rounding_to_integer(aux_float);
        
        // cocnatenating FTW to final register
        reg = reg | (aux);
        
        return reg;   
    }

// function to get the integer from a float
    int rounding_to_integer(float nfloat){
        
        int nint;
        
        if(nfloat - ceil(nfloat) < nfloat - floor(nfloat))
            nint = ceil(nfloat);
        else
            nint = floor(nfloat);
        
        return nint;    
    }

// returns an array with the register's bytes separated (MSB)
    int *get_byte(long int data, int data_size){
        
        int number_of_bytes;                      
        int i = 0;
        int filter = 0xFF000000;
        
        number_of_bytes = (log10((float)data_size)/log10(2.0)) - 1;
        
        int bytes_array[number_of_bytes];
        
        while(i+1 <= number_of_bytes){
            
            bytes_array[i] = data & filter;
            
            filter = filter >> 8;
            
            i++;
        }
        
    return bytes_array;        
        
}
    
void update_profile(int p0, int p1, int p2){
    
    DigitalOut  prof0(p16);
    DigitalOut  prof1(p17);
    DigitalOut  prof2(p19);
    
    prof0 = p0;
    prof1 = p1;
    prof2 = p2;
    
}

// reset the AD9910 board
void reset_board(){
    
    DigitalOut  MASTER_RESET(p23);
    DigitalOut  EXT_PWR_DWN(p27);
    
    EXT_PWR_DWN = 0;
    MASTER_RESET = 1;
    wait(2);
    MASTER_RESET = 0;
        
    wait(1);    
}

// initialize pins
void initialize_pins(){
        
        DigitalOut  cs(p8);                 // its necessary to keep it low during data transfer
        DigitalOut  io_reset(p9);           // its necessary to keep it low during data transfer
        DigitalOut  io_update(p15);         // depends os the 23 bit of CFR2
        DigitalOut  prof0(p16);
        DigitalOut  prof1(p17);
        DigitalOut  prof2(p19);
        DigitalOut  osk(p11);               //  osk can be innoprative
        
        cs = 0;        
        io_reset = 0;
        io_update = 0;        
        prof0 = 0;
        prof1 = 0;
        prof2 = 0;        
        osk = 0;    
}

void configure_spi(int nbits, int mode, float fsysclk){
    
    SPI         spi(p5, p6, p7);        // MOSI MISO SCLK
    
    spi.format(nbits, mode);
    spi.frequency(fsysclk);    
}

void io_update_pulse(int time_us){
        
        DigitalOut  io_update(p15);         // depends os the 23 bit of CFR2
        
        io_update = 1;
        wait_us(time_us);
        io_update = 0;
}

void write_register(int address, int data, int data_size){
        
        SPI         spi(p5, p6, p7);        // MOSI MISO SCLK
        
        int i;
        int data_bytes[data_size];
        
        
        spi.write(address);    //  address
        for(i=0; i+1 <= data_size; i++){
            data_bytes[i] = *(get_byte(data, data_size)+i);
            spi.write(data_bytes[i]);
        }
        
        io_update_pulse(100);
}
