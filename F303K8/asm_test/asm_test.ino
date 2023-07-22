// http://www.neko.ne.jp/~freewing/cpu/stm32_stm32f103c8t6_gcc_inline_assembler/


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Boot NUCLEO");

  int a=1, b=2, c=3; 

  Serial.print("a = ");
  Serial.print(a);
  Serial.print(" b = ");
  Serial.print(b);
  Serial.print(" c = ");
  Serial.println(c);

  // res = i + j;
  asm volatile (
     "ADD %[result], %[input_i], %[input_j]"
     : [result] "=r" (a)
     : [input_i] "r" (b), [input_j] "r" (c)
     );

  Serial.print("a = ");
  Serial.print(a);
  Serial.print(" b = ");
  Serial.print(b);
  Serial.print(" c = ");
  Serial.println(c);
}

void loop() {
  // put your main code here, to run repeatedly:
}


