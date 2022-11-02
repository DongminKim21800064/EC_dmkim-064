/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Dongmin Kim
Created          : 05-03-2021
Modified         : 10-10-2022 by DongMin Kim
Language/ver     : C++ in Keil uVision

Description      : Distributed to Students for LAB_GPIO
/----------------------------------------------------------------*/
#include "ecGPIO.h"
#include "ecSysTick.h"
#include "ecEXTI.h"


void EXTI_init(GPIO_TypeDef *Port, int Pin, int trig_type,int priority){

	// SYSCFG peripheral clock enable	
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;		
	
	// Connect External Line to the GPIO
	int EXTICR_port;
	if			(Port == GPIOA) EXTICR_port = 0;
	else if	(Port == GPIOB) EXTICR_port = 1;
	else if	(Port == GPIOC) EXTICR_port = 2;
	else if	(Port == GPIOD) EXTICR_port = 3;
	else 										EXTICR_port = 4;
	
	if(Port == GPIOA)
		{
		SYSCFG -> EXTICR[Pin/4] &= ~(0xF << 4*(Pin%4)); // PC13   ~(1111<<4)
		SYSCFG -> EXTICR[Pin/4] |= PAx_PIN <<4*(Pin%4) ; // 0x 0020 (0000 0000 0010 0000) choose MUX
		}
		else if(Port == GPIOB)
		{
		SYSCFG -> EXTICR[Pin/4] &= ~(0xF << 4*(Pin%4)); // PC13   ~(1111<<4)
		SYSCFG -> EXTICR[Pin/4] |= PBx_PIN <<4*(Pin%4) ; // 0x 0020 (0000 0000 0010 0000) choose MUX
		}
		else if(Port == GPIOC)
		{
		SYSCFG -> EXTICR[Pin/4] &= ~(0xF << 4*(Pin%4)); // PC13   ~(1111<<4)
		SYSCFG -> EXTICR[Pin/4] |= PCx_PIN <<4*(Pin%4) ; // 0x 0020 (0000 0000 0010 0000) choose MUX
		}
	// Configure Trigger edge
	if (trig_type == FALL) EXTI->FTSR |= 1<<Pin;   // Falling trigger enable 
	else if	(trig_type == RISE) EXTI->RTSR |= 1<<Pin;   // Rising trigger enable 
	else if	(trig_type == BOTH) {			// Both falling/rising trigger enable
		EXTI->RTSR |= 1<<Pin; 
		EXTI->FTSR |= 1<<Pin;
	} 
	
	// Configure Interrupt Mask (Interrupt enabled)
	EXTI->IMR  |= 1<<Pin;     // not masked
	
	
	// NVIC(IRQ) Setting
	int EXTI_IRQn = 0;
	
	if (Pin < 5) 	EXTI_IRQn = Pin+6;
	else if	(Pin < 10) 	EXTI_IRQn = EXTI9_5_IRQn;
	else 			EXTI_IRQn = EXTI15_10_IRQn;
								
	NVIC_SetPriority(EXTI_IRQn, priority);	// EXTI priority
	NVIC_EnableIRQ(EXTI_IRQn); 	// EXTI IRQ enable
}


void EXTI_enable(uint32_t pin) {
	EXTI->IMR |= 1<<pin;     // not masked (i.e., Interrupt enabled)
}
void EXTI_disable(uint32_t pin) {
	EXTI->IMR |= 0<<pin;     // masked (i.e., Interrupt disabled)
}

uint32_t is_pending_EXTI(uint32_t pin){
	//uint32_t EXTI_PRx = ;     	// check  EXTI pending 	
	return ((EXTI->PR & (1UL<<pin)) == (1UL<<pin));
}


void clear_pending_EXTI(uint32_t pin){
	EXTI->PR |= 1<<pin ;     // clear EXTI pending 
}
