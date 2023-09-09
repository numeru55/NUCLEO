// arduino-cli compile --fqbn STMicroelectronics:stm32:GenG0 hello
// arduino-cli upload -p /dev/cu.usbmodem14103 --fqbn STMicroelectronics:stm32:GenG0 hello
// arduino-cli monitor -p /dev/cu.usbmodem14103

#include <SoftwareSerial.h>
SoftwareSerial mySerial(PA3, PA2); // RX, TX

void setup()
{
  mySerial.begin(9600);
}


void loop()
{
  mySerial.println("Hello, World");
  delay(1000);
}
