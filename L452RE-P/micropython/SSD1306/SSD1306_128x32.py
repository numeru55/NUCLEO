import machine
i2c = machine.I2C(sda=machine.Pin('B7'), scl=machine.Pin('B8'))
print(i2c.scan())

from ssd1306 import SSD1306_I2C
oled = SSD1306_I2C(128, 32, i2c)

oled.text('Hello', 0, 0)
oled.text('World', 0, 10)
oled.show()