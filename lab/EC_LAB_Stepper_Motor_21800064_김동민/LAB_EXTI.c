/**
******************************************************************************
* @author  SSSLAB
* @Mod		 2022-10-19 by Dongmin Kim
* @brief   Embedded Controller:  LAB_EXTI
*					 - _________________________________
*
******************************************************************************
*/

#include "ecRCC.h"
#include "ecGPIO.h"
#include "ecEXTI.h"
#include "stm32f411xe.h"

void setup(void);
void EXTI15_10_IRQHandler(void);

int main(void) {

	// System CLOCK, GPIO Initialiization ----------------------------------------
	setup();

	while (1){}
}


void EXTI15_10_IRQHandler(void) {
	uint32_t count=0;
	while(1){
	if (is_pending_EXTI (BUTTON_PIN)) {
			if(count==4) count = 0;
			multipleLED(count);
			count++;
		 clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
			}	
		}
	}
 


// Initialiization 
void setup(void)
{
	RCC_PLL_init();                         
	// Initialize multipleLED_init() for Output
  multipleLED_init();
	EXTI_init(GPIOC, BUTTON_PIN, FALL, 0);
}