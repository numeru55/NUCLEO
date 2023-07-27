void setup() {

  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Boot NUCLEO G070");

  pinMode(PC13, INPUT);

  uint32_t out;

  asm volatile(
    "GPIOC_IDR = 0x50000810 \r\n" // GPIOC->IDR のアドレスになまえをつけておく
    "LDR r1, =GPIOC_IDR \r\n"     // r1 に GPIOC->IDR のアドレスを代入
    "LDR r1, [r1] \r\n"           // アドレス r1 の値を r1 にロード
    "LSR r1, #13 \r\n"            // r1 を 13ビット右シフト
    "MOV %[out], #1 \r\n"         // 0b1 と
    "AND %[out], r1 \r\n"         // AND をとって %[out] で返す
    : [out] "=r" (out) // 結果を収めるレジスタ
    : 
    : "r1"             // 使うレジスタ
    );
  
  Serial.print("Result: ");
  Serial.println(out,HEX);
}

void loop() {
}
