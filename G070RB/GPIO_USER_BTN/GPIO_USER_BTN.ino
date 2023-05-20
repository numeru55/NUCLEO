void setup() {
  // PA5 same as LED_BUILTIN for NUCLEO G070RB
  // HIGH = ON
  // LOW = OFF
  pinMode(PA5, OUTPUT);

  // PC13 same as USR_BTN for NUCLEO G070RB
  pinMode(PC13, INPUT);
}

#define BTN_PRESSING LOW
#define BTN_RELEASING HIGH

void loop() {
  do {
    digitalWrite(PA5, HIGH);
    delay(200);
    digitalWrite(PA5, LOW);
    delay(200);
  } while (digitalRead(PC13) == BTN_RELEASING);
  // exit loop when BTN was pressed
  
  digitalWrite(PA5, HIGH);
  delay(2000);

  do {
    delay(10);
  } while (digitalRead(PC13) == BTN_PRESSING);
  // exit loop when BTN was released
  
  digitalWrite(PA5, LOW);

}
