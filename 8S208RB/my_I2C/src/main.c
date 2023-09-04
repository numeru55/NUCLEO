#include "stm8s.h"
#include "stm8s_it.h"

#include "my_i2c.h"

void main(void)
{

  GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);

    i2c_start();
    i2c_write_addr(0x37 + I2C_WRITE);
    i2c_write(0x20);
    i2c_stop();

  while (1)
  {
    GPIO_WriteReverse(GPIOC, GPIO_PIN_5);
    for (uint32_t c = 200000L; c > 0; c--) {}
  }

}

// from example

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{
  (void)file;
  (void)line;
  while (1)
  {
  }
}
#endif