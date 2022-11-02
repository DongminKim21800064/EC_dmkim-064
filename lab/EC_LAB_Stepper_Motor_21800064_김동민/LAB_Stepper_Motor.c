/**
******************************************************************************
* @author							DongMin Kim  
* @Modified         : 11-02-2022 by DongMin Kim   	
* @brief	Embedded Controller:  Stepper Motor 
*					 
******************************************************************************
*/

#include "stm32f411xe.h"
#include "ecGPIO.h"
#include "ecRCC.h"
#include "ecEXTI.h"
#include "ecSysTick.h"
#include "ecStepper.h"					



void setup(void);
volatile uint32_t rev = 10;
volatile uint32_t rpm = 20;
volatile uint32_t mode = HALF;
int main (void){
	// Initialization------------------------------------------------
	setup();
	
	Stepper_step(2048*rev, 0, mode); // (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)

	// Infinite Loop -------------------------------------------------
	while(1){;}
}

// Initialization
void setup(void){
	RCC_PLL_init();																				// System Clock = 84Mz 																		
	SysTick_init(1);																		// Systick init
		
	EXTI_init(GPIOC, BUTTON_PIN, FALL, 0);								// External Interrupt Setting
	GPIO_init(GPIOC, BUTTON_PIN, INPUT);									// GPIOC pin 13 Initialization
	
	Stepper_init(GPIOB, 10, GPIOB, 4 , GPIOB,5, GPIOB,3); // Stepper GPIO pin Initializaion // No pull-up Pull-down , Push-Pull, Fast	
	Stepper_setSpeed(rpm,mode);																	// set stepper motor speed
}

void EXTI15_10_IRQHandler(void){
	if(is_pending_EXTI(BUTTON_PIN)){
		Stepper_stop();
		clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
	}
}