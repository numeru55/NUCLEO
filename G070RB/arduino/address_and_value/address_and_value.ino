// http://www.neko.ne.jp/~freewing/cpu/stm32_stm32f103c8t6_gcc_inline_assembler/
// https://blueeyes.sakura.ne.jp/2018/01/23/825/

// Nucleo 64
// PA5 - LED - GND  H:on L:off
// PC13 - SW with on board pullup   H:open L:close

void setup() {

  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Boot NUCLEO G070");

  Serial.print("SysTick Address ");
  Serial.println((uint32_t)&SysTick->VAL, HEX);
  Serial.print("SysTick CTRL ");
  Serial.println((uint32_t)SysTick->CTRL, BIN);
  Serial.print("SysTick LOAD ");
  Serial.print((uint32_t)SysTick->LOAD, BIN);
  Serial.print(" = ");
  Serial.println((uint32_t)SysTick->LOAD);
  Serial.print("SysTick VAL ");
  Serial.println((uint32_t)SysTick->VAL, BIN);

  uint32_t out;

  asm volatile(
    "SYSTICK_VAL = 0xE000E018 \r\n"  // GPIOC->IDR のアドレスになまえをつけておく
    "LDR r1, =SYSTICK_VAL \r\n"      // r1 に GPIOC->IDR のアドレスを代入
    "LDR %[out], [r1] \r\n"            // アドレス r1 の値を r1 にロード
    : [out] "=r"(out)              // 結果を収めるレジスタ
    :
    : "r1"  // 使うレジスタ
  );

  Serial.print(" memory ");
  Serial.println(out);
}

void loop() {

  delay(1);
}
