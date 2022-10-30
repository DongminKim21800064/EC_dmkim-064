/**
******************************************************************************
* @author  Dongmin Kim 
* @Mod		 2022-10-30 by Dongmin Kim  	
* @brief   Embedded Controller:  LAB PWM Out - Servo Motor
*					 - Control a servo motor with PWM output
* 
******************************************************************************
*/


#include "stm32f411xe.h"
#include "ecGPIO.h"
#include "ecRCC.h"
#include "ecEXTI.h"
#include "ecTIM.h"
#include "ecPWM.h"

#define RCMotor_PIN	1

PWM_t pwm;
static uint32_t pwm_period = 20;
static uint32_t EXTI_flag = 0;
static uint32_t TIM_flag = 0;

uint32_t count = 0;
uint32_t state = 0;

void setup(void);
void EXTI15_10_IRQHandler(void);
void TIM3_IRQHandler(void);

int main(void) { 
	// Initialiization ---------------------------------------------------------
	setup();

	// Inifinite Loop ----------------------------------------------------------
	while(1){				
			if(EXTI_flag==1){									// If the Button Pushed -> reset
				state =0 ;
				PWM_duty(&pwm, (0.5 /pwm_period)); // Set 0 degree
				EXTI_flag = 0;
			}		
		}
	}


// Initialiization 
void setup(void){	
	RCC_PLL_init();                       // System Clock = 84MHz
	TIM_INT_init(TIM3,u_sec,100); 				// Timer Period 100usec
	
	
	// Digital In: Button Pin to use interrupt
	GPIO_init(GPIOC, BUTTON_PIN, INPUT);
	GPIO_pupd(GPIOC, BUTTON_PIN, EC_PU);
	EXTI_init(GPIOC, BUTTON_PIN, FALL, 0);

	// Digital Out: ServoMotor
	GPIO_init(GPIOA, RCMotor_PIN, AF);    // calls RCC_GPIOA_enable()
	GPIO_output (GPIOA, RCMotor_PIN, PUSH_PULL, EC_PU, FAST_SPEED);
 
	// PWM
	PWM_init(&pwm, GPIOA, RCMotor_PIN);
	PWM_period_ms(&pwm, pwm_period);
	
}

void TIM3_IRQHandler(void){					// Timer Interrupt
	if (is_UIF(TIM3) == TIM_SR_UIF) { // update interrupt flag
		
		count++;
		if(count >5000){			// delay 500ms = 100us x 5000 

		if(state >= 18) TIM_flag = 1;		// If PWM Restart flag
				
		PWM_duty(&pwm, (0.5 + ((2.5-0.5)/18)*state)/pwm_period);	// PWM operate
				
			if(TIM_flag==1){		// To prevent the state from operating at 1 to 18
				TIM_flag = 0;			// It will operate at 0 to 18
				state = 0;
			}else if(TIM_flag==0)	state++;
						
			count = 0;
		}	
	
	clear_UIF (TIM3);                       // clear by writing 0
	}
}

void EXTI15_10_IRQHandler(void) {   // EXTI Button interrupt
	if (is_pending_EXTI(BUTTON_PIN)){
		EXTI_flag = 1;  
		clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
	}
}
