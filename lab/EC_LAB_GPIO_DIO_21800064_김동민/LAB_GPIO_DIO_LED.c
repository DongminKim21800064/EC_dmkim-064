/**
******************************************************************************
* @author   DongMin Kim
* @Mod      2022-10-01 by DongMin Kim
* @brief   Embedded Controller:  LAB Digital In/Out
*                - Toggle LED LD2 by Button B1  pressing
* 
******************************************************************************
*/

#include "stm32f4xx.h"
#include "ecRCC.h"
#include "ecGPIO.h"
#include "ecSysTick.h"

#define LED_PIN 	5
#define BUTTON_PIN 13

void setup(void);
	
int main(void) { 

	// Initialiization --------------------------------------------------------
	setup();
	
	 //Inifinite Loop ----------------------------------------------------------
	while(1){
		// When the button pressed
		if(GPIO_read(GPIOC, BUTTON_PIN) == 0){
			bit_toggle(GPIOA, LED_PIN);
		}	
		// For debouncing
		delay_ms(50);
		SysTick_reset();
	}
}

// Initialiization 
void setup(void)
{
	RCC_HSI_init();	
	SysTick_init();
	GPIO_init(GPIOC, BUTTON_PIN, INPUT);  		// calls RCC_GPIOC_enable()
	GPIO_pupd(GPIOC, BUTTON_PIN, EC_PU); 			// PULL-UP  
	
	GPIO_init(GPIOA, LED_PIN, OUTPUT);    		// calls RCC_GPIOA_enable()
	GPIO_pupd(GPIOA, LED_PIN, EC_PU);					// PULL-UP
	GPIO_otype(GPIOA, LED_PIN, OPEN_DRAIN); 	// OPEN-DRAIN
	GPIO_ospeed(GPIOA, LED_PIN,MEDIUM_SPEED); // MEDIUM-SPEED
}