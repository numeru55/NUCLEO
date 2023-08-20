# 完成したので Qiita に投稿した

https://qiita.com/numeru55/items/9a0105cfea85fe6df646

# 参考

https://blog.handen.net/archives/19087339.html

# ピン接続

```

2 GND
...
12 A0 PA0 -- DATA
13  (AVDD)
14 3.3V

```

# 計画

0packet T0H 400 +/-150 nsec -->> 4 clock
0packet T0L 850 +/-150 nsec -->> 7 clock

1packet T1H 800 +/-150 nsec -->> 7 clock
1packet T1L 450 +/-150 nsec -->> 4 clock


8MHz動作の場合，1クロックは125nsec 

## Hを出すとき

```main.c
	  const uint32_t bsrr = (uint32_t)&GPIOB->BSRR;

	  asm volatile(
	    "MOV r1, #(1 << 3) \r\n"
	    "STR r1, [%[bsrr]] \r\n"
	    :
	    : [bsrr] "r"(bsrr)
	    : "r1"
	    );
```

## L を出すとき

```main.c
	  asm volatile(
	    "MOV r1, #(1 << (3+16)) \r\n"
	    "STR r1, [%[bsrr]] \r\n"
	    :
	    : [bsrr] "r"(bsrr)
	    : "r1"
	    );
```