#include "mbed.h"

//  amp is between 0 and 1 (amplitude scale)
//  phase given in degrees
//  fout given in Hz
// fsysclk reference of the system (typ 25 MHz)

void write_single_tone_register (int address, float amp,float phase,float fout,float fsysclk);
int get_single_tone_register (float amp,float phase,float fout,float fsysclk);
int rounding_to_integer(float nfloat);
int get_byte(long int reg, double potential);
int * get_byte(long int data, int data_size);
void reset_board();
void initialize_pins();
void configure_spi(int nbits, int mode, float fsysclk);
void io_update_pulse(float time_us);
void write_register(int address, int data, int data_size);
void update_profile(int p0, int p1, int p2);
