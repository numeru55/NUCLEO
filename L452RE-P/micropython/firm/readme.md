
# STM32L452RET6 P CPU PIN OUT

|  | STM32L452RET6 | STM32L452RET6P |
| -- | -- | -- |
| DS11912 66ページ | 25pin PC5<br>26pin PB0 | N/A PC5<br>25pin PB0 |
| DS11912 67ページ | 27pin PB1<br>28pin PB2 | 26pin PB1<br>27pin PB2 |
| DS11912 68ページ | 29pin PB10<br>30pin PB11<br>N/A VDD12 | 28pin PB10<br>29pin PB11<br>30pin VDD12 |
| DS11912 72ページ | 54pin PD2 | N/A PD2 |
| DS11912 73ページ | 55pin PB3<br>56pin PB4<br>57pin PB5 | 54pin PB3<br>55pin PB4<br>56pin PB5 |
| DS11912 74ページ | 58pin PB6<br>59pin PB7<br>60pin PH3<br>61pin PB8<br>62pin PB9<br>N/A VDD12 | 57pin PB6<br>58pin PB7<br>59pin PH3<br>60pin PB8<br>61pin PB9<br>62pin VDD12 |


# NUCLEO CONNECTOR

```
    L452RE          L452RE-P
     CN5             CN7
D15  PB8  I2C1_SCL   PB8  I2C1_SCL
D14  PB9  I2C1_SDA   PB7  I2C1_SDA
    AVDD            AVDD
     GND             GND
D13  PA5  SPI1_SCK  PB13  SPI2_SCK
D12  PA6  SPI1_MISO PB14  SPI2_MISO
D11  PA7  SPI1_MOSI PB15  SPI2_MOSI
D10  PB6  SPI1_CS   PA11  SPIx_NSS
 D9  PC7             PA8
 D8  PA9             PB6

     CN9             CN9

 D7  PA8             PC7
 D6 PB10            PB10
 D5  PB4            PA15
 D4  PB5             PB5
 D3  PB3             PB3
 D2 PA10            PA12
 D1  PA2             PA2
 D0  PA3             PA3
```

# 参考

- https://qiita.com/grinpeaceman/items/0425ae4c1e3d891e99ca
- https://blog.boochow.com/article/mp-stm-nucleo-l432kc.html
