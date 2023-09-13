#ifndef INC_MY_SSD1306_H_
#define INC_MY_SSD1306_H_

#define SSD1306_ADDRESS  0x3c << 1  // is for SSD1306 128x32.

#define OLED_HEIGHT 32
// #define OLED_HEIGHT 64

void OLED_command(uint8_t command);
void OLED_data(uint8_t data);
void OLED_Init();
void OLED_write_bit(uint8_t ch, uint8_t x, uint8_t y);
void OLED_clear();
void OLED_char6(uint8_t ch, uint8_t x, uint8_t y);
void OLED_set_cursor(uint8_t x, uint8_t y);
void OLED_put_len(uint8_t * c, uint8_t p);
void OLED_put_c(uint8_t c);

#endif /* INC_MY_SSD1306_H_ */
