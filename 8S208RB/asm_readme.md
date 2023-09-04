# 以下にテキストのマニュアルがある

http://svn.code.sf.net/p/sdcc/code/trunk/sdcc/sdas/doc/asmlnk.txt


# 3.11.3 Naked Functions

```main.c
volatile data unsigned char counter;
void nakedInterrupt(void) __interrupt (2) __naked
 {
    __asm
    inc _counter ; does not change flags, no need to save psw
    reti ; MUST explicitly include ret or reti in _naked function.
__endasm; }
```

- `__naked`  を添えて関数を定義すると，`_counter` で変数が参照できる。
- この場合 `reti` が必ず必要

# 3.11.4 Use of Labels within Inline Assembler

```main.s
__asm
mov b,#10
    00001$:
        djnz    b,00001$
__endasm ;
```