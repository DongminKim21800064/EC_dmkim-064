/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : SSS LAB
Created          : 05-03-2021
Modified         : 10-24-2022 by DongMin Kim
Language/ver     : C++ in Keil uVision

Description      : Distributed to Students for LAB_GPIO
/----------------------------------------------------------------*/


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
void LED_toggle(void);
void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
void GPIO_output(GPIO_TypeDef *Port, int pin, int type, int pupd, int speed);
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
void reverse_sevensegment_decode(uint8_t  num);
void pause_sevensegment_decode(void);
 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
