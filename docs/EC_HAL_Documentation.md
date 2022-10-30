# EC_dmkim-064

---
description: EC_HAL API
---


# Embedded Controller - STM32f411 HAL API

Documentation for HAL functions

Written by:   김동민

Course:  임베디드컨트롤러

Program: C/C++

IDE/Compiler: Keil uVision 5

OS: WIn10

MCU:  STM32F411RE (Nucleo-64)



---

[TOC]

  * [GPIO Digital In/Out](#gpio-digital-inout)
    + [Header File](#header-file)
    + [GPIO_init\(\)](#gpio_init)
    + [GPIO_mode\(\)](#gpio_mode)
    + [GPIO_write\(\)](#gpio_write)
    + [GPIO_read\(\)](#gpio_read)
    + [GPIO_ospeed\(\)](#gpio_ospeed)
    + [GPIO_otype\(\)](#gpio_otype)
    + [GPIO_pupd\(\)](#gpio_pupd)

  * [Interrupt EXTI](#interrupt-EXTI)
    + [Header File](#header-file)
    + [EXTI_init\(\)](#exti_init)
    + [EXTI_enable\(\)](#exti_enable)
    + [EXTI_disable\(\)](#exti_disable)
    + [is_pending_EXTI\(\)](#is_pending_exti)
    + [clear_pending_EXTI\(\)](#clear_pending_exti)

  * [Interrupt SysTick](#interrupt-SysTick)
    + [Header File](#header-file)
    + [SysTick_init\(\)](#systick_init)
    + [SysTick_Handler\(\)](#systick_handler)
    + [SysTick_counter\(\)](#systick_counter)
    + [delay_ms\(\)](#delay_ms)
    + [SysTick_reset\(\)](#systick_reset)
    + [SysTick_val\(\)](#systick_val)
---

## GPIO Digital InOut 

### Header File

 `#include "ecGPIO.h"`


```c++
#include "stm32f411xe.h"
#include "ecRCC.h"

#ifndef __ECGPIO_H
#define __ECGPIO_H

// PIN
#define LED_PIN 				5
#define BUTTON_PIN 		 13

#define      PA5        5
#define      PA6        6
#define      PA7        7
#define      PB6        6
#define      PC7        7
#define      PA9        9
#define      PA8        8
#define      PB10      10


// MODER
#define 		 INPUT  		0x00
#define 		 OUTPUT 		0x01
#define 		 AF     		0x02
#define      ANALOG 		0x03

// IDR & ODR
#define 		 HIGH 			1
#define 		 LOW  			0

// PUDR
#define 		 NONE  			0x00	// No pull-up, pull-down
#define 		 EC_PU 			0x01	// Pull-up
#define 		 EC_PD 			0x02	// Pull-down 
#define 		 RESERVED 	0x03 	// Reserved

// OTYPER
#define 		 PUSH_PULL 			0	// Push-pull
#define 		 OPEN_DRAIN 		1 // Open-Drain

// Output speed Setting
#define      LOW_SPEED          0
#define      MEDIUM_SPEED       1 
#define      FAST_SPEED         2 
#define      HIGH_SPEED         3 





#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

void bit_toggle(GPIO_TypeDef* Port, int pin);
void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
void GPIO_write(GPIO_TypeDef *Port, int pin, int Output);
int  GPIO_read(GPIO_TypeDef *Port, int pin);
void GPIO_mode(GPIO_TypeDef* Port, int pin, int mode);
void GPIO_ospeed(GPIO_TypeDef* Port, int pin, int speed);
void GPIO_otype(GPIO_TypeDef* Port, int pin, int type);
void GPIO_pupd(GPIO_TypeDef* Port, int pin, int pupd);
void multipleLED_init(void);
void multipleLED(uint32_t  num);
void sevensegment_init(void); 
void sevensegment_decode(uint8_t  num);

 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
```



### bit_toggle\(\)

Toggling the LED or other pins.

```c++
void bit_toggle(GPIO_TypeDef* Port, int pin);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH

* **pin**:  pin number (int) 0~15

  


**Example code**

```c++
bit_toggle(GPIOA, LED_PIN); // LED_PIN = 5
```






### GPIO_init\(\)

Initializes GPIO pins with default setting and Enables GPIO Clock. Mode: In/Out/AF/Analog

```c++
void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH

* **pin**:  pin number (int) 0~15

* **mode**:   INPUT(0), OUTPUT(1),  AF(02), ANALOG (03)

  

**Example code**

```c++
GPIO_init(GPIOA, 5, OUTPUT);
GPIO_init(GPIOC, 13, INPUT); //GPIO_init(GPIOC, 13, 0);
```



### GPIO_mode\(\)

Configures  GPIO pin modes: In/Out/AF/Analog

```c++
void GPIO_mode(GPIO_TypeDef *Port, int pin, int mode);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH

* **pin**:  pin number (int) 0~15

* **mode**:   INPUT (0), OUTPUT (1),  AF(02), ANALOG (03)

  

**Example code**

```c++
GPIO_mode(GPIOA, 5, OUTPUT);
```



### GPIO_write\(\)

Write the data to GPIO pin: High, Low

```c++
void GPIO_write(GPIO_TypeDef *Port, int pin, int output);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH
* **pin**:  pin number (int) 0~15
* **output**:   LOW(0), HIGH(1)



**Example code**

```c++
GPIO_write(GPIOA, 5, 1);  // 1: High
```



### GPIO_read\(\)

Read the data from GPIO pin

```c++
int  GPIO_read(GPIO_TypeDef *Port, int pin);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH
* **pin**:  pin number (int) 0~15



**Example code**

```c++
GPIO_read(GPIOC, 13);
```



### GPIO_ospeed\(\)

Configures  output speed of GPIO pin : Low, Mid, Fast, High

```c++
void GPIO_ospeed(GPIO_TypeDef* Port, int pin, int speed);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH
* **pin**:  pin number (int) 0~15
* **speed**:   LOW_SPEED(0), MID_SPEED(1), FAST_SPEED(2) , HIGH_SPEED(3)



**Example code**

```c++
GPIO_ospeed(GPIOA, 5, 2);  // 2: FAST_SPEED
```



### GPIO_otype\(\)

Configures  output type of GPIO pin: Push-Pull / Open-Drain

```c++
void GPIO_otype(GPIO_TypeDef* Port, int pin, int type);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH
* **pin**:  pin number (int) 0~15
* **type**:   PUSH_PULL(0), OPEN_DRAIN(1)



**Example code**

```c++
GPIO_otype(GPIOA, 5, 0);  // 0: Push-Pull
```



### GPIO_pupdr\(\)

Configures  Pull-up/Pull-down mode of GPIO pin: No Pull-up, Pull-down/ Pull-up/ Pull-down/ Reserved

```c++
void GPIO_pupd(GPIO_TypeDef* Port, int pin, int pupd);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH
* **pin**:  pin number (int) 0~15
* **pupd**:   NO_PUPD(0), PULL_UP(1), PULL_DOWN(2), RESERVED(3)



**Example code**

```c++
GPIO_pupd(GPIOA, 5, 0);  // 0: No Pull-up, Pull-down
```



### multipleLED_init\(\)

Initializes multiple LED pins with default setting.

```c++
void multipleLED_init(void);
```

**Parameters**

* void

**Example code**

```c++
multipleLED_init();
```



### multipleLED()

Turned on and off with 4 LED_pins (PA5, PA6, PA7 and PB6)

```c++
void multipleLED(uint32_t  num);
```

**Parameters**

* **num:**  Select  the column of the structure which is composed with LED on and off.

**Example code**

```c++
multipleLED(i);  // when the 'i' is uint32_t type
```


------



### sevensegment_init\(\)

Initializes seven-segment  pins with default setting.

```c++
void sevensegment_init(void); 
```

**Parameters**

* void

**Example code**

```c++
sevensegment_init();
```



### sevensegment_decode()

Turned on and off the common anode type 7-segment.

```c++
void sevensegment_decode(uint8_t  num);
```

**Parameters**

* **num:**  Select  the column of the structure which is composed with 7-segment on and off.

**Example code**

```c++
sevensegment_decode(cnt % 10);  // when the 'cnt' is unsigned int type
```


------



## Interrupt EXTI

### Header File

 `#include "ecEXTI.h"`

```c
#include "stm32f4xx.h"

#ifndef __ECEXTI_H
#define __ECEXTI_H

#define FALL 0
#define RISE 1
#define BOTH 2

#define PA_pin 0x0
#define PB_pin 0x1
#define PC_pin 0x2
#define PD_pin 0x3
#define PE_pin 0x4

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
	 
void EXTI_init (GPIO_TypeDef *Port, uint32_t pin, int edge , int prior);
void EXTI_enable(uint32_t pin);
void EXTI_disnable(uint32_t pin);
uint32_t is_pending_EXTI(uint32_t pin);
void clear_pending_EXTI(uint32_t pin);
void EXTI15_10_IRQHandler(void);
void LED_toggle(GPIO_TypeDef *Port, uint32_t pin);
	 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
```





### EXTI_init()

Initialize EXIT

```c
void EXTI_init (GPIO_TypeDef *Port, uint32_t pin, int edge , int prior);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH
* **pin:**  pin number (int) 0~15
* **edge:** Trigger type, Fall and Rising
* **prior:** Priority

**Example code**

```c
EXTI_init(GPIOC, BUTTON_PIN, FALL, 0);
```



### EXTI_enable()

Enable the EXIT

```c
void EXTI_enable(uint32_t pin);
```

**Parameters**

* **pin:**  pin number (int) 0~15

**Example code**

```c
EXTI_enable(BUTTON_PIN);
```



### EXTI_disable()

Enable the EXIT

```c
void EXTI_disable(uint32_t pin);
```

**Parameters**

* **pin:**  pin number (int) 0~15

**Example code**

```c
EXTI_disable(BUTTON_PIN);
```



### is_pending_EXTI()

Check EXTI pending

```c
uint32_t is_pending_EXTI(uint32_t pin);
```

**Parameters**

* **pin:**  pin number (int) 0~15

**Example code**

```c
is_pending_EXTI (BUTTON_PIN);
```



### clear_pending_EXTI()

Clear the EXTI pending

```c
void clear_pending_EXTI(uint32_t pin);
```

**Parameters**

* **pin:**  pin number (int) 0~15

**Example code**

```c
clear_pending_EXTI(BUTTON_PIN);
```



## Interrupt SysTick

### Header File

 `#include "ecSystick.h"`

```c
#ifndef __EC_SYSTICK_H
#define __EC_SYSTICK_H

#include "stm32f4xx.h"
#include "ecRCC.h"
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

void SysTick_init(uint32_t Ticks);
void SysTick_Handler(void);
void SysTick_counter();
void delay_ms(uint32_t msec);
void SysTick_reset(void);
uint32_t SysTick_val(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
```





### SysTick_init()

Initailize Systick Clock.

```c
void SysTick_init(uint32_t Ticks);
```

**Parameters**

* Ticks : To control the period.

**Example code**

```c
SysTick_init();
```



### SysTick_Handler()

If Systick interrupt is ON, Implement this function

```c
void SysTick_Handler(void);
```

**Parameters**

* void

**Example code**

```c
SysTick_Handler(); // Called by interrupt
```



### SysTick_counter()

Count the clock by ms unit.

```c
void SysTick_counter();
```

**Parameters**

* void

**Example code**

```c
SysTick_counter(); 
```



### delay_ms()

Delay by the input time

```c
void delay_ms(uint32_t msec);
```

**Parameters**

* **msec :** Time of ms unit

**Example code**

```c
delay_ms(1000); // Give 1s delay
```



### SysTick_reset()

Reset the systick val

```c
void SysTick_reset(void);
```

**Parameters**

* void

**Example code**

```c
SysTick_reset(); //reset the val value
```



### SysTick_val()

Return the current Systick reload

```c
uint32_t SysTick_val(void);
```

**Parameters**

* void

**Example code**

```c
SysTick_val(void); // return current reload value
```



## Timer Interrupt

### Header File

 `#include "ecTIM.h"`

```c
#ifndef __EC_TIM_H 
#define __EC_TIM_H
#include "stm32f411xe.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
#define m_sec  0
#define u_sec  1

/* Timer Configuration */
void TIM_init(TIM_TypeDef* timerx, uint32_t unit, uint32_t time);  
void TIM_period_us(TIM_TypeDef* timx, uint32_t usec);  
void TIM_period_ms(TIM_TypeDef* timx, uint32_t msec);

void TIM_INT_init(TIM_TypeDef *timerx, uint32_t unit ,uint32_t time); 
void TIM_INT_enable(TIM_TypeDef* timx);
void TIM_INT_disable(TIM_TypeDef* timx);

uint32_t is_UIF(TIM_TypeDef *TIMx);
void clear_UIF(TIM_TypeDef *TIMx);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
```

### TIM_init()

Initialize TIM CLOCK, CNT period, CNT Direction, Enable Timer Counter.

```c
void TIM_init(TIM_TypeDef* timerx, uint32_t unit, uint32_t time);
```

**Parameters**

* **timerx :** Select TIM(x), x = 1,2, ..
* **unit :** Select unit of the time. m_sec = 0, u_sec = 1
* **time :** Declare timer period

**Example code**

```c
TIM_INT_init(TIM3,u_sec,100);
```



### TIM_period_us()

Initialize Timer period micro unit sec.

```c
TIM_period_us(TIM_TypeDef* timx, uint32_t usec);
```

**Parameters**

* **timerx :** Select TIM(x), x = 1,2, ..
* **usec :** Declare micro sec timer period

**Example code**

```c
TIM_period_us(TIM3, 100);
```



### TIM_period_ms()

Initialize Timer period milli unit sec.

```c
TIM_period_ms(TIM_TypeDef* timx, uint32_t msec);
```

**Parameters**

* **timerx :** Select TIM(x), x = 1,2, ..
* **msec :** Declare milli sec timer period

**Example code**

```c
TIM_period_ms(TIM3, 1);
```



### TIM_INT_init()

Initialize TIM interrupt.

```c
void TIM_INT_init(TIM_TypeDef* timerx, uint32_t unit, uint32_t time);
```

**Parameters**

* **timerx :** Select TIM(x), x = 1,2, ..
* **unit :** Select unit of the time. m_sec = 0, u_sec = 1
* **time :** Declare timer period

**Example code**

```c
TIM_INT_init(TIM3, u_sec, 100);
```



### TIM_INT_enable()

Initialize TIM enable.

```c
void TIM_INT_enable(TIM_TypeDef* timx);
```

**Parameters**

* **timerx :** Select TIM(x), x = 1,2, ..

**Example code**

```c
TIM_INT_enable(TIM3);
```



### TIM_INT_disable()

Initialize TIM disable.

```c
void TIM_INT_disable(TIM_TypeDef* timx);
```

**Parameters**

* **timerx :** Select TIM(x), x = 1,2, ..

**Example code**

```c
TIM_INT_disable(TIM3);
```



### is_UIF()

update interrupt flag

```c
uint32_t is_UIF(TIM_TypeDef *TIMx);
```

**Parameters**

* **timerx :** Select TIM(x), x = 1,2, ..

**Example code**

```c
is_UIF(TIM3);
```



### clear_UIF()

clear by writing 0

```c
void clear_UIF(TIM_TypeDef *TIMx);
```

**Parameters**

* **timerx :** Select TIM(x), x = 1,2, ..

**Example code**

```c
clear_UIF(TIM3);
```



## PWM

### Header File

 `#include "ecPWM.h"`

```c
#include "stm32f411xe.h"
#include "ecGPIO.h"
#include "ecTIM.h"  			// change to ecTIM.h

#ifndef __EC_PWM_H
#define __EC_PWM_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

typedef struct{
   GPIO_TypeDef *port;
   int pin;
   TIM_TypeDef *timer;
   int ch;
} PWM_t;


/* PWM Configuration */
void PWM_init(PWM_t *pwm, GPIO_TypeDef *port, int pin);  
void PWM_period_ms(PWM_t *pwm,  uint32_t msec);		
void PWM_period_us(PWM_t *pwm, uint32_t usec);  


void PWM_pulsewidth_ms(PWM_t *pwm, float pulse_width_ms);
void PWM_duty(PWM_t *pwm, float duty);
void PWM_pinmap(PWM_t *PWM_pin);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
```

### PWM_init()

Initialize PWM's GPIO port, configure GPIO AFR, initialize timer, configure timer output mode as PWM, enable timer counter.

```c
void PWM_init(PWM_t *pwm, GPIO_TypeDef *port, int pin);  
```

**Parameters**

* **pwm** 
* **port :** Port Number,  GPIOA~GPIOH
* **pin :** pin number (int) 0~15

**Example code**

```c
PWM_init(&pwm, GPIOA, RCMotor_PIN);
```



### PWM_period_ms()

Initialize PWM period in milli sec unit.

```c
void PWM_period_ms(PWM_t *pwm,  uint32_t msec);	
```

**Parameters**

* **pwm** 
* **msec :** Declare milli sec timer period

**Example code**

```c
PWM_period_ms(&pwm, pwm_period);
```



### PWM_period_us()

Initialize PWM period in micro sec unit.

```c
void PWM_period_us(PWM_t *pwm,  uint32_t usec);	
```

**Parameters**

* **pwm** 
* **usec :** Declare micro sec timer period

**Example code**

```c
PWM_period_us(&pwm, pwm_period);
```



### PWM_pulsewidth_ms()

Initialize PWM pulse width in msec unit.

```c
void PWM_pulsewidth_ms(PWM_t *pwm, float pulse_width_ms);
```

**Parameters**

* **pwm** 
* **pulse_width_ms :** Declare msec PWM pulse width

**Example code**

```c
PWM_pulsewidth_ms(&pwm, pulse_width_ms);
```



### PWM_duty()

Initialize PWM duty ratio.

```c
void PWM_duty(PWM_t *pwm, float duty);
```

**Parameters**

* **pwm** 
* **duty :** Declare duty ratio of PWM

**Example code**

```c
PWM_duty(&pwm, (0.5 + ((2.5-0.5)/18)*state)/pwm_period);
```



### PWM_pinmap()

Initialize pinmap of PWM.

```c
void PWM_pinmap(PWM_t *PWM_pin);
```

**Parameters**

* **pin :** pin number (int) 0~15

**Example code**

```c
PWM_pinmap(PWM_pin);
```

