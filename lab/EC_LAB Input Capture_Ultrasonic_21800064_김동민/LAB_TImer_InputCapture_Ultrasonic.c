/**
******************************************************************************
* @author  SSSLAB
* @Mod		 2022-11-09 by Dongmin Kim  	
* @brief   Embedded Controller:  Inputcap_UltraSonic
*					 - Detect the distance through the UltraSonic sensor 
* 
******************************************************************************
*/


#include "stm32f411xe.h"
#include "math.h"
#include "ecGPIO.h"
#include "ecRCC.h"
#include "ecTIM.h"
#include "ecPWM.h"
#include "ecUART.h"
#include "ecSystick.h"

void TIM2_IRQHandler(void);

uint32_t ovf_cnt = 0;
double distance = 0;
double timeInterval = 0;
double time1 = 0;
double time2= 0;
static volatile int flag = 0;

void setup(void);

int main(void){
	
	setup();
	
	
	while(1){
	  
	if(flag>=5){ 				// For ignore Initial sensor malfunction
			distance = ( timeInterval*340/(2*1000000) ) * 100; // ( timeInterval[us]*340[m/s]/(2*1000000) ) * 100 ==> distance[cm]
		if(distance>=(2-0.3) && distance<=(400+0.3)){ // Measurement : 2cm to 400cm, Ranging Accuracy : +-3mm
			printf("%f [cm]\r\n", distance);
			delay_ms(500);
			flag = 5;
			}
		}
	}
}
void TIM2_IRQHandler(void){
	if(is_UIF(TIM2)){                   // Update interrupt
		ovf_cnt++;												// overflow count
		clear_UIF(TIM2);  						    // clear update interrupt flag
	}
	if(is_CCIF(TIM2, 3)){ 							// TIM2_Ch3 (IC3) Capture Flag. Rising Edge Detect
		time1 = TIM2->CCR3;								// Capture TimeStart from CC3

		clear_CCIF(TIM2, 3);              // clear capture/compare interrupt flag 
	}								                      
	else if(is_CCIF(TIM2, 4)){ 					// TIM2_Ch3 (IC4) Capture Flag. Falling Edge Detect
		flag++;
		time2 = TIM2->CCR4;								// Capture TimeEnd from CC4

		timeInterval = ( (time2 - time1) + ( (TIM2->ARR) + 1 )*ovf_cnt ) * 10; 		// Total time of echo pulse
		
		ovf_cnt = 0;                      // overflow reset
		clear_CCIF(TIM2, 4);							// clear capture/compare interrupt flag 
	}
}

void setup(){

	RCC_PLL_init(); 
	SysTick_init(1);
	UART2_init();
  
// PWM configuration ---------------------------------------------------------------------	
	PWM_t trig;											// PWM1 for trig
	
	PWM_init(&trig,GPIOA,PA6);			 // PWM init as PA_6: Ultrasonic trig puls
	PWM_period_us(&trig,50000);    	// PWM of 50ms period. Use period_us()
	PWM_pulsewidth_us(&trig,10);   	// PWM pulse width of 10us

// Input Capture configuration -----------------------------------------------------------------------	
	IC_t echo;											// Input Capture for echo
	ICAP_init(&echo,GPIOB,PB10);    // ICAP init as PB10 as input caputre
	ICAP_counter_us(&echo, 10);   	// ICAP counter step time as 10us
	ICAP_setup(&echo, 3, RISE);   	// TIM2_CH3 as IC3 , rising edge detect
	ICAP_setup(&echo, 4, FALL);			// TIM2_CH3 as IC4 , falling edge detect

// Enable TIMx interrupt			-----------------------------------------------------------------------	

	TIM_INT_enable(TIM2);  					// TIM2 Interrupt Enable

}

