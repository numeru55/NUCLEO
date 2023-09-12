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
