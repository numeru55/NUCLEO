# CPU SPEC

- L452RE 80MHz 512kB Flash 160kB RAM  1 - Op-Amp 1 - DAC
- G0B1RE 64MHz 512kB Flash 144kB RAM  3 - Comparators 1- DAC
- G070RB 64MHz 128kB Flash 36kB RAM
- G031F8 64MHz 64kB Flash 8kB RAM

# タイマーの解説

難しいけど

https://www.st.com/resource/ja/application_note/an4776-generalpurpose-timer-cookbook-for-stm32-microcontrollers-stmicroelectronics.pdf

# STM32CubeIDEでcppを扱う

ほぼこの方法でいける

https://qiita.com/FlechaMaker/items/de9c663d1b394e5a2862

# 雑多メモ

```main.c
#include <stdio.h>

int my_print(unsigned char * p, unsigned char q) {
    for (int i=0; i<q; i++) {
        printf("%d\n", p[i]);
    }
}

int main(void){
    // Your code here!
    unsigned char data[]={0,1,2,3,4};
    my_print((unsigned char *)&data+2, 3);
}
```
実行結果
```
2
3
4
```
