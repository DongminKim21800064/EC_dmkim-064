/**
******************************************************************************
* @author  SSSLAB
* @Mod		 2021-8-30 by YKKIM  	
* @brief   Embedded Controller:  LAB Systick&EXTI with API
*					 - 7 segment
* 
******************************************************************************
*/

#include "stm32f411xe.h"
#include "ecGPIO.h"
#include "ecRCC.h"
#include "ecEXTI.h"
#include "ecSysTick.h"

static volatile uint32_t count = 0;
static volatile uint32_t flag = 0;


void setup(void);
void EXTI15_10_IRQHandler(void);	

int main(void) { 
	// Initialiization --------------------------------------------------------
		setup();
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){

		
		if(flag==0){
			sevensegment_decode(count);
			delay_ms(1000);
			count++;
		if (count >9) count =0;
		
	}
		else if(flag==1){
			count = 0;
			sevensegment_decode(count);
			flag = 0;
		}
		SysTick_reset();
	}
}

void EXTI15_10_IRQHandler(void) {
	if (is_pending_EXTI (BUTTON_PIN)) {
			flag= 1;
			clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
			}	
		}
	
// Initialiization 
void setup(void)
{
	RCC_PLL_init();
	SysTick_init(1000); //systic period : 1000=1ms , 2000=0.5ms, 500=2ms
	sevensegment_init();
	EXTI_init(GPIOC, BUTTON_PIN, FALL, 0);
}