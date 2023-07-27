// http://www.neko.ne.jp/~freewing/cpu/stm32_stm32f103c8t6_gcc_inline_assembler/
// https://blueeyes.sakura.ne.jp/2018/01/23/825/

// Nucleo 64
// PA5 - LED - GND  H:on L:off
// PC13 - SW with on board pullup   H:open L:close

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Boot NUCLEO G070");

  Serial.println(GPIOA_BASE,HEX);
  Serial.println((uint32_t)&GPIOA->BSRR, HEX);

}

void loop() {
  // put your main code here, to run repeatedly:
}


