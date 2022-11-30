/**
******************************************************************************
* @author  SSSLAB
* @Mod		 2022-11-09 by Dongmin Kim  	
* @brief   Embedded Controller:  EC_HAL
* 
******************************************************************************
*/


#include "ecPWM.h"

/* PWM Configuration */

void PWM_init(PWM_t *pwm, GPIO_TypeDef *port, int pin){
// 0. Match Output Port and Pin for TIMx 	
		pwm->port = port;
		pwm->pin  = pin;
		PWM_pinmap(pwm);
		TIM_TypeDef *TIMx = pwm->timer;
		int CHn = pwm->ch;	

// 1. Initialize GPIO port and pin as AF
		GPIO_init(port, pin, AF);  // AF=2
		GPIO_ospeed(port, pin,(uint32_t)0x11);  // speed VHIGH=3 
		
		GPIO_otype(port, pin, (uint32_t)0x00);
		GPIO_pupd(port, pin, (uint32_t)0x00);

	
// 2. Configure GPIO AFR by Pin num.
		/*int val = 0;
	
		if (pin >=0 && pin < 8){
			if (TIMx == TIM1 || TIMx == TIM2){
				val = 1UL; // AF1
			}
			else if (TIMx == TIM3 || TIMx == TIM4 || TIMx == TIM5 ){
				val = 2UL; // AF2
			}
			else if (TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11 ){
				val = 3UL; // AF3
			}
			port->AFR[0] |= val << (4 * pin);
		}


		else if (pin > 7 && pin < 16){
			if (TIMx == TIM1 || TIMx == TIM2){
				val = 1UL; // AF1
			}
			else if (TIMx == TIM3 || TIMx == TIM4 || TIMx == TIM5 ){
				val = 2UL; // AF2
			}
			else if (TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11 ){
				val = 3UL; // AF3
			}
			port->AFR[1] |= val << (4 * (pin-8));
		}	*/
		
		
		if(pin >= 0 && pin <= 7){
		if(TIMx == TIM1 || TIMx == TIM2){
			port->AFR[0] |= 1UL << (4 * pin);
		}
		else if(TIMx == TIM3 || TIMx == TIM4 || TIMx == TIM5){
			port->AFR[0] |= 2UL << (4 * pin);
		}
		else if(TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11){
			port->AFR[0] |= 3UL << (4 * pin);
		}
	}
	
	else if(pin >=8 && pin <= 15){
		if(TIMx == TIM1 || TIMx == TIM2){
			port->AFR[1] |= 1UL << (4 * (pin-8));
		}
		else if(TIMx == TIM3 || TIMx == TIM4 || TIMx == TIM5){
			port->AFR[1] |= 2UL << (4 * (pin-8));
		}
		else if(TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11){
			port->AFR[1] |= 3UL << (4 * (pin-8));
		}
	}

// 3. Initialize Timer 
		TIM_init(TIMx, m_sec, 1);	// with default msec=1 value.		

// 3-2. Direction of Counter
		
		TIMx->CR1 &= ~TIM_CR1_DIR;    // Counting direction: 0 = up-counting, 1 = down-counting
	
			
// 4. Configure Timer Output mode as PWM
		uint32_t ccVal=TIMx->ARR/2;  // default value  CC=ARR/2
		if(CHn == 1){
			TIMx->CCMR1 &= ~TIM_CCMR1_OC1M;                     // Clear ouput compare mode bits for channel 1
			//TIMx->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; 												// OC1M = 110 for PWM Mode 1 output on ch1. #define TIM_CCMR1_OC1M_1          (0x2UL << TIM_CCMR1_OC1M_Pos)
			TIMx->CCMR1 |= (6UL << 4);
			TIMx->CCMR1	|= TIM_CCMR1_OC1PE;                     // Output 1 preload enable (make CCR1 value changable)
			
			TIMx->CCR1  = ccVal; 																// Output Compare Register for channel 1 (default duty ratio = 50%)		
			TIMx->CCER &= ~TIM_CCER_CC1P;                       // select output polarity: active high	
			TIMx->CCER  |= TIM_CCER_CC1E;											// Enable output for ch1
		}
		else if(CHn == 2){
			TIMx->CCMR1 &= ~TIM_CCMR1_OC2M;                     // Clear ouput compare mode bits for channel 2
			TIMx->CCMR1 |= (6UL << 12); 															// OC1M = 110 for PWM Mode 1 output on ch2
			//TIMx->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2; 												// OC1M = 110 for PWM Mode 1 output on ch1. #define TIM_CCMR1_OC1M_1          (0x2UL << TIM_CCMR1_OC1M_Pos)
			TIMx->CCMR1	|= TIM_CCMR1_OC2PE;                     // Output 1 preload enable (make CCR1 value changable)
			
			TIMx->CCR2  = ccVal; 																// Output Compare Register for channel 1 (default duty ratio = 50%)		
			TIMx->CCER &= ~TIM_CCER_CC2P;                       // select output polarity: active high	
			TIMx->CCER  |= TIM_CCER_CC2E;															// Enable output for ch2
		}
		else if(CHn == 3){
			TIMx->CCMR2 &= ~TIM_CCMR2_OC3M;                     // Clear ouput compare mode bits for channel 3
			//TIMx->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2; 												// OC1M = 110 for PWM Mode 1 output on ch1. #define TIM_CCMR1_OC1M_1          (0x2UL << TIM_CCMR1_OC1M_Pos)
			TIMx->CCMR2 |= (6UL << 4);
			TIMx->CCMR2	|= TIM_CCMR2_OC3PE;                     // Output 1 preload enable (make CCR1 value changable)
			
			TIMx->CCR3  = ccVal; 																// Output Compare Register for channel 1 (default duty ratio = 50%)		
			TIMx->CCER &= ~TIM_CCER_CC3P;                       // select output polarity: active high	
			TIMx->CCER  |= TIM_CCER_CC3E;																// Enable output for ch3
		}
		else if(CHn == 4){
			TIMx->CCMR2 &= ~TIM_CCMR2_OC4M;                     // Clear ouput compare mode bits for channel 3
			//TIMx->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2; 												// OC1M = 110 for PWM Mode 1 output on ch1. #define TIM_CCMR1_OC1M_1          (0x2UL << TIM_CCMR1_OC1M_Pos)
			TIMx->CCMR2 |= (6UL << 12);
			TIMx->CCMR2	|= TIM_CCMR2_OC4PE;                     // Output 1 preload enable (make CCR1 value changable)
			
			TIMx->CCR4  = ccVal; 																// Output Compare Register for channel 1 (default duty ratio = 50%)		
			TIMx->CCER &= ~TIM_CCER_CC4P;                       // select output polarity: active high	
			TIMx->CCER  |= TIM_CCER_CC4E;	
		}	
		
		
		
	// 5. Enable Timer Counter
		if(TIMx == TIM1) {
			TIMx->BDTR |= TIM_BDTR_MOE;					// Main output enable (MOE): 0 = Disable, 1 = Enable	
		}
		
		TIMx->CR1  |= TIM_CR1_CEN;  													// Enable counter
}


void PWM_period_ms(PWM_t *PWM_pin, uint32_t msec){
	TIM_TypeDef *TIMx = PWM_pin->timer;
	TIM_period_ms(TIMx,msec); //PWM period = timer period  
}

void PWM_period_us(PWM_t *PWM_pin, uint32_t usec){
	TIM_TypeDef *TIMx = PWM_pin->timer;
	TIM_period_us(TIMx,usec); 	
}


void PWM_pulsewidth_ms(PWM_t *pwm, float pulse_width_ms){ 
	TIM_TypeDef *TIMx = pwm->timer;
	int CHn = pwm->ch;
	uint32_t fsys = 0;
	uint32_t psc = pwm->timer->PSC;
	
	// Check System CLK: PLL or HSI
	if((RCC->CFGR & (3<<0)) == 2)      { fsys = 84000; }  // for msec 84MHz/1000
	else if((RCC->CFGR & (3<<0)) == 0) { fsys = 16000; }
	

	float fclk = fsys/(psc+1);			// fclk=fsys/(psc+1);
	float ccval = pulse_width_ms *fclk;					// width_ms *fclk - 1;
	
	
	switch(CHn){
		case 1: pwm->timer->CCR1 = ccval; break;
		case 2: pwm->timer->CCR2 = ccval; break;
		case 3: pwm->timer->CCR3 = ccval; break;
		case 4: pwm->timer->CCR4 = ccval; break;
		default: break;
	}
}

void PWM_pulsewidth_us(PWM_t *pwm, float pulse_width_us){ 
	TIM_TypeDef *TIMx = pwm->timer;
	int CHn = pwm->ch;
	uint32_t fsys = 0;
	uint32_t psc = pwm->timer->PSC;
	
	// Check System CLK: PLL or HSI
	if((RCC->CFGR & (3<<0)) == 2)      { fsys = 84; }  // for msec 84MHz/1000
	else if((RCC->CFGR & (3<<0)) == 0) { fsys = 16; }
	

	float fclk = fsys/(psc+1);			// fclk=fsys/(psc+1);
	float ccval = pulse_width_us *fclk;					// width_ms *fclk - 1;
	
	
	switch(CHn){
		case 1: pwm->timer->CCR1 = ccval; break;
		case 2: pwm->timer->CCR2 = ccval; break;
		case 3: pwm->timer->CCR3 = ccval; break;
		case 4: pwm->timer->CCR4 = ccval; break;
		default: break;
	}
}


void   PWM_duty(PWM_t *pwm, float duty) { 
		TIM_TypeDef *TIMx = pwm->timer;	//  duty=0 to 1	
		float ccval =(TIMx->ARR +1)*duty;    								// (ARR+1)*dutyRatio - 1          
		int CHn = pwm->ch;
  
		
		switch(CHn){
			case 1: pwm->timer->CCR1 = ccval; break;
			case 2: pwm->timer->CCR2 = ccval; break;
			case 3: pwm->timer->CCR3 = ccval; break;
			case 4: pwm->timer->CCR4 = ccval; break;
			default: break;
		}
}


// DO NOT MODIFY HERE
	void PWM_pinmap(PWM_t *PWM_pin){
 GPIO_TypeDef *port = PWM_pin->port;
 int pin = PWM_pin->pin;
 
 if(port == GPIOA) {
		switch(pin){
			 case 0 : PWM_pin->timer = TIM2; PWM_pin->ch = 1; break;
			 case 1 : PWM_pin->timer = TIM2; PWM_pin->ch = 2; break;
			 case 5 : PWM_pin->timer = TIM2; PWM_pin->ch = 1; break;
			 case 6 : PWM_pin->timer = TIM3; PWM_pin->ch = 1; break;
			 //case 7: PWM_pin->timer = TIM1; PWM_pin->ch = 1N; break;
			 case 8 : PWM_pin->timer = TIM1; PWM_pin->ch = 1; break;
			 case 9 : PWM_pin->timer = TIM1; PWM_pin->ch = 2; break;
			 case 10: PWM_pin->timer = TIM1; PWM_pin->ch = 3; break;
			 case 15: PWM_pin->timer = TIM2; PWM_pin->ch = 1; break;
			 default: break;
		}         
 }
 else if(port == GPIOB) {
		switch(pin){
			 //case 0: PWM_pin->timer = TIM1; PWM_pin->ch = 2N; break;
			 //case 1: PWM_pin->timer = TIM1; PWM_pin->ch = 3N; break;
			 case 3 : PWM_pin->timer = TIM2; PWM_pin->ch = 2; break;
			 case 4 : PWM_pin->timer = TIM3; PWM_pin->ch = 1; break;
			 case 5 : PWM_pin->timer = TIM3; PWM_pin->ch = 2; break;
			 case 6 : PWM_pin->timer = TIM4; PWM_pin->ch = 1; break;
			 case 7 : PWM_pin->timer = TIM4; PWM_pin->ch = 2; break;
			 case 8 : PWM_pin->timer = TIM4; PWM_pin->ch = 3; break;
			 case 9 : PWM_pin->timer = TIM4; PWM_pin->ch = 3; break;
			 case 10: PWM_pin->timer = TIM2; PWM_pin->ch = 3; break;
			 
			 default: break;
		}
 }
 else if(port == GPIOC) {
		switch(pin){
			 case 6 : PWM_pin->timer = TIM3; PWM_pin->ch = 1; break;
			 case 7 : PWM_pin->timer = TIM3; PWM_pin->ch = 2; break;
			 case 8 : PWM_pin->timer = TIM3; PWM_pin->ch = 3; break;
			 case 9 : PWM_pin->timer = TIM3; PWM_pin->ch = 4; break;
			 
			 default: break;
		}
 }
 // TIM5 needs to be added, if used.
}