void setup() {

  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Boot NUCLEO G070");

}

void loop() {
  uint32_t out1, out2;

  asm volatile(
    "LDR %[out1], [%[systick_val_address]] \r\n" // 1 cycle
    "NOP \r\n"                                   // 1 cycle
    "NOP \r\n"                                   // 1 cycle
    "NOP \r\n"                                   // 1 cycle
    "NOP \r\n"                                   // 1 cycle
    "NOP \r\n"                                   // 1 cycle
    "NOP \r\n"                                   // 1 cycle
    "NOP \r\n"                                   // 1 cycle
    "NOP \r\n"                                   // 1 cycle
    "LDR %[out2], [%[systick_val_address]] \r\n" // 1 cycle
    : [out1] "=r"(out1) , [out2] "=r"(out2)     
    : [systick_val_address] "r"((uint32_t)&SysTick->VAL)
    : 
  );

  Serial.print("out1 ");
  Serial.println(out1);

  Serial.print("out2 ");
  Serial.println(out2);

  Serial.print(out1-out2);
  Serial.println(" clocks.");

  delay(2000);
  while(1) {}
}
