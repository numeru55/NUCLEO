void setup() {

  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Boot NUCLEO G070");

  Serial.print("Result: ");
  Serial.println(SystemCoreClock);
}

void loop() {
}
