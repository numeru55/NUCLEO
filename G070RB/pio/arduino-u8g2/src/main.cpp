#include <Arduino.h>
#include <U8x8lib.h>

U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(/* reset=*/U8X8_PIN_NONE); // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED

void setup(void)
{
  u8x8.begin();
}

void loop(void)
{
  u8x8.setCursor(0, 0);
  // u8x8.println("Hello World!");
  u8x8.setFont(u8x8_font_8x13_1x2_f);
  u8x8.println("Hello World!");

  delay(1000);
  u8x8.println("newline?");

  delay(1000);
  u8x8.setCursor(0, 0);
  u8x8.println("   append.");

  delay(1000);
  u8x8.println("Add line.");

  delay(1000);
  u8x8.setCursor(0, 0);
  u8x8.println("2");
  delay(1000);
  u8x8.println("3");
  delay(1000);
  u8x8.setCursor(0, 0);
  u8x8.println("4");

  delay(2000);
  u8x8.clear();

  u8x8.println("Speed test");
  delay(1000);
  for (int i = 0; i < 100; i++)
  {
    if ((i & 1) == 0)
    {
      u8x8.clear();
    }
    char str[128];
    snprintf(str, sizeof(str), "Count %d", 99 - i);
    u8x8.println(str);
    // delay(100);
  }
  delay(2000);
  u8x8.clear();
}
