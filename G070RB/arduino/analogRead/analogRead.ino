// arduino-cli compile --fqbn STMicroelectronics:stm32:GenG0 hello
// arduino-cli upload -p /dev/cu.usbmodem14103 --fqbn STMicroelectronics:stm32:GenG0 hello
// arduino-cli monitor -p /dev/cu.usbmodem14103


/*
                 PB8 D15 10
                  PB9 D14 9
                  AVD AVD 8
                  GND GND 7
1 NC              PA5 D13 6
2 IOREF           PA6 D12 5
3 NRST            PA7 D11 4
4 3V3             PB0 D10 3
5 5V               PC7 D9 2
6 GND              PA9 D8 1
7 GND
8 VIN              PA8 D7 8
                  PB14 D6 7
1 A0 PA0           PB4 D5 6
2 A1 PA1           PB5 D4 5
3 A2 PA4           PB3 D3 4
4 A3 PB1          PA10 D2 3
5 A4 PB9           PC4 D1 2
6 A5 PB8           PC5 D0 1

*/

#include <SoftwareSerial.h>
SoftwareSerial mySerial(PA3, PA2); // RX, TX

void setup()
{
  mySerial.begin(9600);
  analogReadResolution(12);
}

#define A0 PA0
#define A1 PA1
#define A2 PA4
#define A3 PB1
//#define A4 PB11 // not work
//#define A5 PB12 // not work

void loop()
{
  mySerial.print(analogRead(A0));
  mySerial.print(',');
  mySerial.print(analogRead(A1));
  mySerial.print(',');
  mySerial.print(analogRead(A2));
  mySerial.print(',');
  mySerial.print(analogRead(A3));
  mySerial.print(',');
  mySerial.print(analogRead(PB_11));
  mySerial.print(',');
  mySerial.println(analogRead(PB_12));
  delay(1000);
}
