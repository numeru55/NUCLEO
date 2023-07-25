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

uint64_t odr = GPIOA_BASE+0x14UL;
uint64_t data;

// asm volatile("LDR R0, [%[address]]" : : [address] "r" (address));

asm volatile(
        //"eor [%[odr1]], [%[odr2]], #32"
        "ldr %[data], [%[odr]]\r\n"
        //"eor %[data], #0x20\r\n"
        "movw %[data], #0x20\r\n"
        "str %[data], [%[odr]]\r\n"
        : [data] "=r" (data)
        : [odr] "r" (odr)
);



}

void loop() {
  // put your main code here, to run repeatedly:
}


