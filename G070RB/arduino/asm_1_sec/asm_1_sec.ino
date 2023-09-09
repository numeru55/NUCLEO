// Nucleo 64
// PA5 - LED - GND  H:on L:off
// PC13 - SW with on board pullup   H:open L:close

void setup() {

  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Boot NUCLEO G070");

  Serial.println("start!");

  uint32_t time0=micros();

  asm volatile(
    "LDR r0, =21333333 \r\n" // (1 + 21333333 * 3)=64,000,000 clocks.
    ".loop: \r\n"
    "SUB r0, #1 \r\n" // 1 cycle
    "BNE .loop \r\n"  // 2 cycle: if not zero, then branch
    : 
    : 
    : "r0"
  );

  uint32_t time1=micros();

  Serial.print("time0 ");
  Serial.println(time0);

  Serial.print("time1 ");
  Serial.println(time1);

  Serial.print("takes ");
  Serial.print(time1-time0);
  Serial.print("[usec] -> ");

  Serial.print((time1-time0)/1000000);
  Serial.println("[sec]");

}

void loop() {
}
