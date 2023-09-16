#ifndef INC_MY_SSD1306_H_
#define INC_MY_SSD1306_H_

#define SSD1306_ADDRESS  0x3c << 1  // is for SSD1306 128x32.

#define OLED_HEIGHT 32
// #define OLED_HEIGHT 64

#define OLED_SETCONTRAST 0x81
#define OLED_DISPLAYALLON_RESUME 0xA4
#define OLED_DISPLAYALLON 0xA5
#define OLED_NORMALDISPLAY 0xA6
#define OLED_INVERTDISPLAY 0xA7
#define OLED_DISPLAYOFF 0xAE
#define OLED_DISPLAYON 0xAF
#define OLED_SETDISPLAYOFFSET 0xD3
#define OLED_SETCOMPINS 0xDA
#define OLED_SETVCOMDETECT 0xDB
#define OLED_SETDISPLAYCLOCKDIV 0xD5
#define OLED_SETPRECHARGE 0xD9
#define OLED_SETMULTIPLEX 0xA8
#define OLED_SETLOWCOLUMN 0x00
#define OLED_SETHIGHCOLUMN 0x10
#define OLED_SETSTARTLINE 0x40
#define OLED_MEMORYMODE 0x20
#define OLED_COLUMNADDR 0x21
#define OLED_PAGEADDR 0x22
#define OLED_COMSCANINC 0xC0
#define OLED_COMSCANDEC 0xC8
#define OLED_SEGREMAP 0xA0
#define OLED_CHARGEPUMP 0x8D

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
