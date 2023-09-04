#include "my_i2c.h"

void i2c_init() {
    I2C->FREQR = (1 << 1); // 1MHz
    I2C->CCRL = 0x0A; // 100kHz
    I2C->OARH = I2C_OARH_ADDMODE; // 7-bit addressing
    //I2C_OARH = (1 << I2C_OARH_ADDMODE); // 7-bit addressing
    //I2C_CR1 = (1 << I2C_CR1_PE);
    I2C->CR1 = I2C_CR1_PE; // peripheral enable

}

void i2c_start() {
    //I2C_CR2 |= (1 << I2C_CR2_START);
    I2C->CR2 |= I2C_CR2_START;
    //while (!(I2C_SR1 & (1 << I2C_SR1_SB)));
    while(!(I2C->SR1 & I2C_SR1_SB));
}

void i2c_stop() {
    //I2C_CR2 |= (1 << I2C_CR2_STOP);
    //while (I2C_SR3 & (1 << I2C_SR3_MSL));
    I2C->CR2 |= I2C_CR2_STOP;
    while (!(I2C->SR3 & I2C_SR3_MSL));
}

void i2c_write(uint8_t data) {
    //I2C_DR = data;
    //while (!(I2C_SR1 & (1 << I2C_SR1_TXE)));
    I2C->DR = data;
    while (!(I2C->SR1 & I2C_SR1_TXE));
}

void i2c_write_addr(uint8_t addr) {
    /*
    I2C_DR = addr;
    while (!(I2C_SR1 & (1 << I2C_SR1_ADDR)));
    (void) I2C_SR3; // check BUS_BUSY
    I2C_CR2 |= (1 << I2C_CR2_ACK);
    */
    I2C->DR = addr;
    while (!(I2C->SR1 & I2C_SR1_ADDR)) ;
    while (!(I2C->SR3 & I2C_SR3_BUSY)) ;
    I2C->CR2 |= I2C_CR2_ACK;
}

uint8_t i2c_read() {
    /*
    I2C_CR2 &= ~(1 << I2C_CR2_ACK);
    i2c_stop();
    while (!(I2C_SR1 & (1 << I2C_SR1_RXNE)));
    return I2C_DR;
    */
    I2C->CR2 &= ~(I2C_CR2_ACK);
    i2c_stop();
    while (!(I2C->SR1 & I2C_SR1_RXNE));
    return I2C->DR;
}

void i2c_read_arr(uint8_t *buf, int len) {
    /*
    while (len-- > 1) {
        I2C_CR2 |= (1 << I2C_CR2_ACK);
        while (!(I2C_SR1 & (1 << I2C_SR1_RXNE)));
        *(buf++) = I2C_DR;
    }
    *buf = i2c_read();
    */

    while (len-- > 1) {
        I2C->CR2 |= I2C_CR2_ACK;
        while (!(I2C->SR1 & I2C_SR1_RXNE));
        *(buf++) = I2C->DR;
    }
    *buf = i2c_read();
}