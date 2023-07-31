// Nucleo 64
// PA5 - LED - GND  H:on L:off
// PC13 - SW with on board pullup   H:open L:close

void setup() {

  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Boot NUCLEO G070");

}

void loop() {
  uint32_t out1, out2;

  asm volatile(
    // value 1 -> 4 cycles
    // value 2 -> 7 cycles
    // value 3 -> 10 cycles
    "MOV r0, #3 \r\n" // 1 -> 
    "LDR %[out1], [%[systick_val_address]] \r\n" // 1 cycle
    ".loop: \r\n"
    "SUB r0, #1 \r\n"  // 1 cycle
    "BNE .loop \r\n"  // 2 cycle if not zero, then branch
    "LDR %[out2], [%[systick_val_address]] \r\n" // 1 cycle
    : [out1] "=r"(out1) , [out2] "=r"(out2)     
    : [systick_val_address] "r"((uint32_t)&SysTick->VAL)
    : "r0"
  );

  Serial.print("out1 ");
  Serial.println(out1);

  Serial.print("out2 ");
  Serial.println(out2);

  Serial.print("takes ");
  Serial.print(out1-out2);
  Serial.println(" cycle(s)");

  delay(2000);

  while(1) {}
}
