#  LAB: GPIO Digital InOut 7-segment

###  Exercise

|    Port/Pin    | Descripstion                 | Register setting           |
| :------------: | ---------------------------- | -------------------------- |
|  Port A pin 5  | Clear Pin5 mode              | GPIOA->MODER &=~(3<<(5*2)) |
|  Port A pin 5  | Set Pin5 mode = Output       | GPIOA->MODER \|=(1<<(5*2)) |
|  Port A pin 6  | Clear Pin6 mode              | GPIOA->MODER &=~(3<<(6*2)) |
|  Port A pin 6  | Set Pin6 mode = Output       | GPIOA->MODER \|=(1<<(6*2)) |
|  Port A pin Y  | Clear PinY mode              | GPIOA->MODER &=~(3<<(Y*2)) |
|  Port A pin Y  | Set PinY mode = Output       | GPIOA->MODER \|=(1<<(Y*2)) |
| Port A pin 5~9 | Clear Pin5~9 mode            | GPIOA->MODER &=~           |
|                | Set Pin5~9 mode = Output     | GPIOA->MODER \|=           |
|  Port X pin Y  | Clear Pin Y mode             | GPIOX->MODER &=~           |
|                | Set Pin Y mode = Output      | GPIOX->MODER \|=           |
|  Port A pin 5  | Set Pin5 otype=push-pull     | GPIOA->OTYPER =            |
|  Port A pin Y  | Set PinY otype=push-pull     | GPIOA-> OTYPER =           |
|  Port A pin 5  | Set Pin5 ospeed=Fast         | GPIOA->OSPEEDR =           |
|  Port A pin Y  | Set PinY ospeed=Fast         | GPIOA-> OSPEEDR =          |
|  Port A pin 5  | Set Pin5 PUPD=no pullup/down | GPIOA->OTYPER =            |
|  Port A pin Y  | Set PinY PUPD=no pullup/down | GPIOA-> OTYPER =           |

