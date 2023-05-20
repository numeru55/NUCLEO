// u8g2 log from:

// https://github.com/olikraus/u8g2/wiki/u8logreference

// connect SSD1306 unit

//      PB8 D15 10 = SCL
//      PB9 D14 9  = SDA


#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

// Create a U8g2log object
U8G2LOG u8g2log;

// assume 4x6 font, define width and height
#define U8LOG_WIDTH 16
#define U8LOG_HEIGHT 6

// allocate memory
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT];

void setup(void) {
  u8g2.begin();    
  u8g2.setFont(u8g2_font_8x13_mf);
  u8g2log.begin(u8g2, U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);	// connect to u8g2, assign buffer
  u8g2log.setLineHeightOffset(0);	// set extra space between lines in pixel, this can be negative
  u8g2log.setRedrawMode(0);		// 0: Update screen with newline, 1: Update screen for every char  

  u8g2log.print("NUCLEO-F303K8\n\n");

  pinMode(LED_BUILTIN, OUTPUT);

}

void loop(void) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(300);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
