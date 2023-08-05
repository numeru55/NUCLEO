/*
Nucleo の 右下 0 と 1 のピンをショート
送受信のテスト
"a" を送り "a" を受けて表示
*/

HardwareSerial Serial1(0, 1); // RX=D0=PC5 TX=D1=PC4

void setup() {
  Serial.begin(9600);
  while(!Serial) {}

  Serial1.begin(9600);
  while(!Serial1) {}

  Serial.println("Boot");

  Serial1.write("a");

}

void loop() {

  if (Serial1.available()>0) {
    Serial.print("Received ");
    char c=Serial1.read();
    Serial.println(String(c));
  }

}
