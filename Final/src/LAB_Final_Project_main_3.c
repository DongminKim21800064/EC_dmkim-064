/**
******************************************************************************
* @author  Dongmin Kim & Jinho Kiik
* @Mod		 2022-12-16 by Dongmin Kim  	
* @brief   Embedded Controller:  Final Project_ Cooler&Alarm
* 
******************************************************************************
*/
#include "stm32f4xx.h"
#include "ecGPIO.h"
#include "ecRCC.h"
#include "ecUART.h"
#include "ecTIM.h"
#include "ecPWM.h"
#include "ecSysTick.h"
#include "ecADC.h"
#include "math.h"

//#define VOLTS_PER_UNIT 0.00122F
//IR parameter//
static volatile double result_v =0;
static volatile double volts =0;
static volatile double temperature =0;

// Control the Setting of temperature//
static volatile double set_temperature = 20;

static volatile double temp1 =0;
static volatile double temp2 =0;

static volatile int flag =0;
int seqCHn[16] = {8,9,};

//Ultro Sonic parameters//
uint32_t ovf_cnt = 0;
float distance = 0;
float timeInterval = 0;
float time1 = 0;
float time2 = 0;



void setup(void);
void ADC_IRQHandler(void);
void TIM2_IRQHandler(void);

#define A 0
#define B 1

PWM_t pwm11;
_Pin dcPwmPin[2] = {
   {GPIOC, 9}, // TIM3 Ch3 A-IA
   {GPIOC, 8}   // TIM3 Ch4 B-IA
};

PWM_t dcPwm[2];

_Pin dcDirPin[2] = {
   {GPIOB, 8}, //A-IB
   {GPIOC, 6}   //B-IB
};



int main(void) { 
   // Initialiization --------------------------------------------------------
   setup();
   
   // Inifinite Loop ----------------------------------------------------------
   while(1){
 
			
		  // Calculate the distance
      distance = (float) timeInterval * 340.0 / 2.0 / (10.0 * 100);
      printf("raw_distance = %f [cm]\r\n", distance); 
      delay_ms(500);
        
		  // If Forklift so close, Buzzer On!
		  if(distance < 20.0 && 2 < distance) {         
            printf("Caution! Danger detected!! \r\n");
            GPIO_toggle(GPIOC,3);
                  } 

      // Calculate the temperature => result_v is output of temperature sensor  
      temperature = ((float)result_v/10)-7;									
      printf("temperature : %.3f 'c \r\n", temperature);
        
			// set_temperture = 20 C degree
			// If temperature up to 20+2, Cooler Fan On
       if(temperature > set_temperature+2 || temp1 >set_temperature+2 || temp2 >set_temperature+2){
                PWM_period_ms(&dcPwm[A], 40);      
                PWM_duty(&dcPwm[A], 0.2);
                GPIO_write(dcDirPin[A].port, dcDirPin[A].Pin, 1);
                       delay_ms(50);
		  // If temperature down to 20-2, Cooler Fan Off 
         } else if(temperature < set_temperature-2 || temp1 <set_temperature-2 || temp2 < set_temperature-2)
			 {
                PWM_period_ms(&dcPwm[A], 40);      
                PWM_duty(&dcPwm[A], 1);
                GPIO_write(dcDirPin[A].port, dcDirPin[A].Pin, 1);
                        delay_ms(50);
         }
			 // To save previous temperature
         temp2 = temp1;
         temp1 = temperature;   
				delay_ms(500);
   }
}





// Initialiization 
void setup(void)
{   
   RCC_PLL_init();                         // System Clock = 84MHz
   SysTick_init(1);
   UART2_init();
   ADC_init(GPIOB, 0, TRGO);
   //ADC_continue(CONT);
   
//ADC_sequence(1, seqCHn);  
   ADC_start();
   
// Buzzer => PC3
   GPIO_init(GPIOC, 3, 0x01);

// Enable TIMx interrupt         -----------------------------------------------------------------------   
   TIM_INT_enable(TIM4);                 // TIM2 Interrupt Enable    
   
// PWM configuration ---------------------------------------------------------------------   
   PWM_t trig;                                    // PWM1 for trig
   PWM_init(&trig, GPIOA, 8);                         // PA_6: Ultrasonic trig pulse
   PWM_period_us(&trig, 50000);       // PWM of 50ms period. Use period_us()
   PWM_pulsewidth_us(&trig, 10);      // PWM pulse width of 10us
   
// Input Capture configuration -----------------------------------------------------------------------   
	 IC_t echo;                                    // Input Capture for echo
   ICAP_init(&echo, GPIOB, 6);          // PB10 as input caputre
   ICAP_counter_us(&echo, 10);         // ICAP counter step time as 10us
   ICAP_setup(&echo, 1, RISE);      // TIM2_CH3 as IC3 , rising edge detect
   ICAP_setup(&echo, 2, FALL);      // TIM2_CH3 as IC4 , falling edge detect


	 PWM_init(&pwm11, GPIOA, 1);
   PWM_period_ms(&pwm11, 20);

   // PWM
   PWM_init(&dcPwm[A], dcPwmPin[A].port, dcPwmPin[A].Pin);
   PWM_period_ms(&pwm11, 20);

   PWM_init(&dcPwm[B], dcPwmPin[B].port, dcPwmPin[B].Pin);
   PWM_init(&dcPwm[A], dcPwmPin[A].port, dcPwmPin[A].Pin);
      
   for (int i = 0; i < 2; i++){
      GPIO_init(dcDirPin[i].port, dcDirPin[i].Pin,OUTPUT);
      GPIO_pupd(dcDirPin[i].port, dcDirPin[i].Pin, 01);
      GPIO_otype(dcDirPin[i].port, dcDirPin[i].Pin, 0);
      GPIO_ospeed(dcDirPin[i].port, dcDirPin[i].Pin, 11);
   
    }
   }

void TIM4_IRQHandler(void){
   if(is_UIF(TIM4)){                   
      ovf_cnt++;                           
      clear_UIF(TIM4);                           
   }
   if(is_CCIF(TIM4, 1)){                         
      time1 = TIM4->CCR1;                     
      clear_CCIF(TIM4, 1);                 
   }                                              
   else if(is_CCIF(TIM4, 2)){                      
      time2 = TIM4->CCR2;                              
      timeInterval = ( (time2 - time1) + ( (TIM4->ARR) + 1 )*ovf_cnt );       
      ovf_cnt = 0;                           
      clear_CCIF(TIM4, 2);                           
   }
}
            
      
void ADC_IRQHandler(void){
   if((is_ADC_OVR())){
      clear_ADC_OVR();
   }
   
   if( is_ADC_EOC() ){       //after finishing sequence
     result_v = ADC_read();
      
      
 }
}