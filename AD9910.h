#define spi_bits 8
#define spi_mode 0
#define spi_freq 12.5e+6

#define CFR1        0x00
#define CFR2        0x01
#define CFR3        0x02
#define AuxDAC_Ctrl 0x03
#define IOUp_Rate   0x04
#define FTW         0x07
#define POW         0x08
#define ASF         0x09
#define MultiSync   0x0A
#define DRampLimit  0x00B
#define DRampStep   0x0C
#define DRampRate   0x0D
#define Prof0       0x0E
#define Prof1       0x0F
#define Prof2       0x10
#define Prof3       0x11
#define Prof4       0x12
#define Prof5       0x13
#define Prof6       0x14
#define Prof7       0x15
#define RAM         0x16

#include "mbed.h"

//  amp is between 0 and 1 (amplitude scale)
//  phase given in degrees
//  fout given in Hz
//  fsysclk reference of the system (typ 25 MHz)

void STP_write (int address, float amp,float phase,float fout,float fsysclk);
uint64_t STP_get_reg (float amp,float phase,float fout,float fsysclk);
uint64_t fround(double nfloat);
uint64_t *get_byte(uint64_t data, int data_size);
void reset_board();
void initialize_pins();
void io_update_pulse(float time_us);
void write_register(int address, uint64_t data, int data_size);
void update_profile(int p0, int p1, int p2);
