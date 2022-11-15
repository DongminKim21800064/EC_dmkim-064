/**
******************************************************************************
* @author  SSSLAB
* @Mod		 2022-11-08 by Dongmin Kim  	
* @brief   Embedded Controller:  EC_HAL
* 
******************************************************************************
*/

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



/* Input Capture*/

// Edge Type
#define RISE 0
#define FALL 1
#define BOTH 2

//Input Capture

typedef struct{
	GPIO_TypeDef *port;
	int pin;   
	TIM_TypeDef *timer;
	int ch;  		//int Timer Channel
	int ICnum;  //int IC number
} IC_t;



void ICAP_init(IC_t *ICx, GPIO_TypeDef *port, int pin);
void ICAP_setup(IC_t *ICx, int IC_number, int edge_type);
void ICAP_counter_us(IC_t *ICx, int usec);

void ICAP_pinmap(IC_t *timer_pin);

uint32_t is_pending_TIM(TIM_TypeDef *TIMx);
void clear_pending_TIM(TIM_TypeDef *TIMx);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif







