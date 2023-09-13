#include "main.h"
#include "my_SSD1306.h"
#include "my_font.h"

// my function for OLED SSD1306 unit 128*64 or 128*32

// global var

I2C_HandleTypeDef *i2c;

volatile uint8_t OLED_cursor_x = 0;  // 0 to 127
volatile uint8_t OLED_cursor_y = 0;  // 0, 1, 2, 3

uint8_t I2C_DATA[12];

///////////////////////////////////////////////////////////////////////////////

void OLED_command(uint8_t command) {
	I2C_DATA[0] = 0;
	I2C_DATA[1] = command;
	HAL_I2C_Master_Transmit(i2c, SSD1306_ADDRESS,  (uint8_t *)&I2C_DATA, 2, 300);
}

void OLED_data(uint8_t data) {
	I2C_DATA[0] = 0x40;
	I2C_DATA[1] = data;
	HAL_I2C_Master_Transmit(i2c, SSD1306_ADDRESS, (uint8_t *)&I2C_DATA, 2, 300);
}

void OLED_Init(I2C_HandleTypeDef *my_i2c) {
	i2c=my_i2c;

	OLED_command(OLED_DISPLAYOFF);         // 0xAE
	OLED_command(OLED_SETDISPLAYCLOCKDIV); // 0xD5
	OLED_command(0x80);                    // the suggested ratio 0x80
	OLED_command(OLED_SETMULTIPLEX);       // 0xA8

#if OLED_HEIGHT == 32
	OLED_command(0x1F);
#elif OLED_HEIGHT == 64
	OLED_command(0x7F);
	#endif

	OLED_command(OLED_SETDISPLAYOFFSET);   // 0xD3
	OLED_command(0x0);                     // no offset
	OLED_command(OLED_SETSTARTLINE | 0x0); // line #0
	OLED_command(OLED_CHARGEPUMP);         // 0x8D
	OLED_command(0xAF);
	OLED_command(OLED_MEMORYMODE); // 0x20
	OLED_command(0x00);            // 0x0 act like ks0108
	OLED_command(OLED_SEGREMAP | 0x1);
	OLED_command(OLED_COMSCANDEC);
	OLED_command(OLED_SETCOMPINS); // 0xDA

#if OLED_HEIGHT == 32
	OLED_command(0x02);
#elif OLED_HEIGHT == 64
OLED_command(0x12);
#endif

	OLED_command(OLED_SETCONTRAST); // 0x81

#if OLED_HEIGHT == 32
	OLED_command(0x8F);
#elif OLED_HEIGHT == 64
	OLED_command(0x9F);
#endif

	OLED_command(OLED_SETPRECHARGE); // 0xd9
	OLED_command(0xF1);
	OLED_command(OLED_SETVCOMDETECT); // 0xDB
	OLED_command(0x40);
	OLED_command(OLED_DISPLAYALLON_RESUME); // 0xA4
	OLED_command(OLED_NORMALDISPLAY);       // 0xA6
	OLED_command(OLED_DISPLAYON);           //--turn on oled panel

}

void OLED_write_bit(uint8_t ch, uint8_t x, uint8_t y) {
	/*
	OLED_command(0x20);            //
	OLED_command(0x02);            // Page addressing mode
	OLED_command(y + 0xB0);        // Set page start addres
	OLED_command(x & 0x0F);        // Set lower column start address
	OLED_command(0x10 + (x >> 4)); // Set higher column start address
	 */

	I2C_DATA[0]=0x00;            // Control Byte Co=0 D/C#=0
	I2C_DATA[1]=0x20;            // addressing mode
	I2C_DATA[2]=0x02;            // Page addressing mode
	I2C_DATA[3]=y + 0xB0;        // Set page start addres
	I2C_DATA[4]=x & 0x0F;        // Set lower column start address
	I2C_DATA[5]=0x10 + (x >> 4); // Set higher column start address

	HAL_I2C_Master_Transmit(i2c, SSD1306_ADDRESS, (uint8_t *)&I2C_DATA, 6, 300);

	//OLED_data(ch);

	I2C_DATA[0] = 0x40;
	I2C_DATA[1] = ch;
	HAL_I2C_Master_Transmit(i2c, SSD1306_ADDRESS, (uint8_t *)&I2C_DATA, 2, 300);

	// 続けてデータを送る場合，0x40 から始めて送ればいいみたい

}

void OLED_clear() {

	/* try

	uint8_t x = 0;
	uint8_t y = 0;
	for (x = 0; x < 128; x++) {
		for (y = 0; y < OLED_HEIGHT / 8; y++) {
			OLED_write_bit(0, x, y);
		}
	}

	クリアアイデア
	横幅128ドット
	9ドット幅の空白で埋め尽くす。
	128/9=14.2222
	*/

	OLED_cursor_x = 0;

	for (OLED_cursor_y = 0; OLED_cursor_y < 4; OLED_cursor_y++) {
		for (uint8_t c=0; c<15; c++) { // 15 = int(128/9)
			OLED_put_c(' ');
		}
	}

	OLED_cursor_x = 0;
	OLED_cursor_y = 0;
}

void OLED_set_cursor(uint8_t x, uint8_t y) {
	OLED_cursor_x=x;
	OLED_cursor_y=y;
}

/*
 * put p bytes to current x, y
 * from c[]
 *
 * example:
 * OLED_put_len( (uint8_t *)&data, 3);   // put data[0], data[1], data[2]
 * OLED_put_len( (uint8_t *)&data+1, 3); // put data[1], data[2], data[3]
 *
 */

void OLED_put_len(uint8_t * c, uint8_t p) {
	I2C_DATA[0]=0x00;            // Control Byte Co=0 D/C#=0
	I2C_DATA[1]=0x20;            // addressing mode
	I2C_DATA[2]=0x02;            // Page addressing mode
	I2C_DATA[3]=OLED_cursor_y + 0xB0;        // Set page start addres
	I2C_DATA[4]=OLED_cursor_x & 0x0F;        // Set lower column start address
	I2C_DATA[5]=0x10 + (OLED_cursor_x >> 4); // Set higher column start address

	HAL_I2C_Master_Transmit(i2c, SSD1306_ADDRESS, (uint8_t *)&I2C_DATA, 6, 300);

	HAL_I2C_Mem_Write(i2c, SSD1306_ADDRESS, 0x40, I2C_MEMADD_SIZE_8BIT, c, p, 300);
}



// x: 0 to 127
// y: 0 to 3 or 7

void OLED_char9(uint8_t ch, uint8_t x, uint8_t y) {

	int table_offset = (ch - ' ') * 18;

	/*
	for (int i = 0; i < 9; i++) {
		OLED_write_bit(OLED_characters[i + table_offset], x + i, y);
		OLED_write_bit(OLED_characters[i + table_offset+9], x + i, y+1);
	}
	 */
	OLED_put_len((uint8_t *)&OLED_characters + table_offset, 9);
	OLED_cursor_y++;
	OLED_put_len((uint8_t *)&OLED_characters + table_offset+9, 9);
	OLED_cursor_y--;

}

void OLED_put_c(uint8_t c) {
	if (c == '\n') {
		OLED_cursor_x = 0;
		OLED_cursor_y = ( OLED_cursor_y + 2 ) & ((OLED_HEIGHT>>3) - 1); // truncate 1 or 3
	} else {
		OLED_char9(c, OLED_cursor_x, OLED_cursor_y);
		OLED_cursor_x = (OLED_cursor_x + 9) & 127;
	}
}


