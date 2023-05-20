void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // LED_BUILTIN = PA5 for NUCLEO G070RB
  for(int i=0; i<10; i++) {
    digitalWrite(LED_BUILTIN, HIGH); // on
    delay(200);
    digitalWrite(LED_BUILTIN, LOW); // off
    delay(200);
  }

  // alternative define
  pinMode(PA5, OUTPUT);
}

void loop() {
  digitalWrite(PA5, HIGH); // on
  delay(500);
  digitalWrite(PA5, LOW); // off
  delay(500);
}
