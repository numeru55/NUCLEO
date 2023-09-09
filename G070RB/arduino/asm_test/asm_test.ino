// http://www.neko.ne.jp/~freewing/cpu/stm32_stm32f103c8t6_gcc_inline_assembler/
// https://blueeyes.sakura.ne.jp/2018/01/23/825/

// Nucleo 64
// PA5 - LED - GND  H:on L:off
// PC13 - SW with on board pullup   H:open L:close

void setup() {
  pinMode(PA5, OUTPUT);

  // Set PA5 (to H)

  const uint64_t bsrr = GPIOA_BASE + 0x18UL;

  asm volatile(
    ".equ GPIOA_BSRR, 0x50000018 \r\n"
    "mov r0, #(GPIOA_BSRR) \r\n"
    "mov r1, #(1 << 5) \r\n"
    "str r1, [r0] \r\n"
    : 
    :
    : "r0", "r1"
    );

}

void loop() {


}
