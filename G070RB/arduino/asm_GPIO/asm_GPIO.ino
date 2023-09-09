// http://www.neko.ne.jp/~freewing/cpu/stm32_stm32f103c8t6_gcc_inline_assembler/
// https://blueeyes.sakura.ne.jp/2018/01/23/825/

// Nucleo 64
// PA5 - LED - GND  H:on L:off
// PC13 - SW with on board pullup   H:open L:close

void setup() {

  // Serial.begin(9600);
  // while (!Serial) {}
  // Serial.println("Boot NUCLEO G070");

  pinMode(PA5, OUTPUT);

}

void loop() {

  // Set PA5 (to H)

  const uint64_t bsrr = GPIOA_BASE + 0x18UL;

  asm volatile(
    "mov r1, #(1 << 5) \r\n"
    "str r1, [%[bsrr]] \r\n"
    : 
    : [bsrr] "r"(bsrr)
    : "r1"
    );


  delay(1000);

  // Reset PA5 (to L)

  const uint64_t brr = GPIOA_BASE + 0x28UL;

  asm volatile(
    "mov r1, #(1 << 5) \r\n"
    "str r1, [%[brr]] \r\n"
    : 
    : [brr] "r"(brr)
    : "r1"
    );

  delay(200);

}
