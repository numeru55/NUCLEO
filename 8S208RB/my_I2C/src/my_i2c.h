#include "stm8s_conf.h"

#define I2C_READ            0x01
#define I2C_WRITE           0x00

void i2c_init();
void i2c_start();
void i2c_stop();
void i2c_write(uint8_t data);
void i2c_write_addr(uint8_t addr);
uint8_t i2c_read();
void i2c_read_arr(uint8_t *buf, int len); 