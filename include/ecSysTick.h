/**
******************************************************************************
* @author   DongMin Kim 21800064
* @Mod     -
******************************************************************************
*/

#ifndef __EC_SYSTICK_H
#define __EC_SYSTICK_H

#include "stm32f4xx.h"
#include "ecRCC.h"
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */


void SysTick_init(uint32_t msec);
void SysTick_Handler(void);
void SysTick_counter();
void delay_ms(uint32_t msec);
void delay_us (uint32_t uesc);
void SysTick_reset(void);
uint32_t SysTick_val(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif