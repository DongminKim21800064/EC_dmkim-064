/**
******************************************************************************
* @author  SSSLAB
* @Mod		 2022-11-30 by Dongmin Kim  	
* @brief   Embedded Controller:  EC_HAL
* 
******************************************************************************
*/
#include "stm32f411xe.h"
#include "ecGPIO.h"
#include "ecRCC.h"
#include "ecTIM.h"
#include "ecSysTick.h"
#include "ecUART.h"
#include "ecADC.h"
#include "ecPWM.h"

//IR parameter//
uint32_t IR1, IR2;
//int flag = 0;
int seqCHn[16] = {8,9,};


#define END_CHAR 13
#define A 0
#define B 1
#define MAX_BUF 100


uint8_t pcData = 0;
uint8_t mcu2Data = 0;
uint8_t btData = 0;
uint8_t buffer[MAX_BUF] = {0, };
uint8_t buffer2 = '\r\n';
int bReceive = 0;
int idx = 0;
int flag = 5;
int dis_flag =0;
int dirA =0;
int dirB =0;
int R_DC_velocity =0;
int L_DC_velocity =0;
float R_duty = 0.f;
float L_duty = 0.f;



uint16_t flagidx =0;



uint32_t ovf_cnt = 0;
float distance = 0;
float timeInterval = 0;
float time1 = 0;
float time2 = 0;

void setup(void);

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
     printf("Hello Nucleo\r\n");

//USART_write(USART1,(uint8_t*) "Hello bluetooth\r\n",17);

   
   // Inifinite Loop ----------------------------------------------------------
   while(1){
       
                   
         // For ignore Initial sensor malfunction
         //distance = (timeInterval*340/(2*1000000) ) * 100; 
         // ( timeInterval[us]*340[m/s]/(2*1000000) ) * 100 ==> distance[cm]
         distance = (float) timeInterval * 340.0 / 2.0 / (10.0 * 100);
               printf("raw_distance = %f [cm]\r\n", distance); delay_ms(500);
         //if(distance>2 && distance<400) {
         //printf("\r%f [cm]",distance);
 
               if(distance < 10.0) {
                //dis_flag =1; 
                        printf("disflag is on\n"); delay_ms(30);
                  
                  
                   PWM_period_ms(&dcPwm[A], 40);
               PWM_period_ms(&dcPwm[B], 40);
      
               PWM_duty(&dcPwm[A], 1);
               PWM_duty(&dcPwm[B], 1);
                      GPIO_write(dcDirPin[A].port, dcDirPin[A].Pin, 1);
                      GPIO_write(dcDirPin[B].port, dcDirPin[B].Pin, 1);
                  delay_ms(100);
                  
                  
                        }
                           else {

                                                           
      printf("IR1 = %d \r\n",IR1);
      printf("IR2 = %d \r\n",IR2);
      printf("\r\n");
      
            PWM_period_ms(&dcPwm[A], 40); //R
            PWM_period_ms(&dcPwm[B], 40); //L
            
            PWM_duty(&dcPwm[A], 0.7);
            PWM_duty(&dcPwm[B], 0.7);
       
            GPIO_write(dcDirPin[A].port, dcDirPin[A].Pin, 1);
        GPIO_write(dcDirPin[B].port, dcDirPin[B].Pin, 1);
            
      
      if (IR1 > 1000){
         printf("GO LEFT\r\n");
         
         PWM_period_ms(&dcPwm[A], 40);
      PWM_period_ms(&dcPwm[B], 40);
      
      PWM_duty(&dcPwm[A], 0.5);
      PWM_duty(&dcPwm[B], 1);
       
       GPIO_write(dcDirPin[A].port, dcDirPin[A].Pin, 1);
         GPIO_write(dcDirPin[B].port, dcDirPin[B].Pin, 1);
            delay_ms(10);
      }
      
      if (IR2 > 1000) {
         printf("GO RIGHT\r\n");
      printf("\r\n");
      
         
         PWM_period_ms(&dcPwm[A], 40);
      PWM_period_ms(&dcPwm[B], 40);
      
      PWM_duty(&dcPwm[A], 1);
      PWM_duty(&dcPwm[B], 0.5);
       
       GPIO_write(dcDirPin[A].port, dcDirPin[A].Pin, 1);
       GPIO_write(dcDirPin[B].port, dcDirPin[B].Pin, 1);
            delay_ms(10);
      }
      }
      }
      
   }
 

// Initialiization 
void setup(void)
{   
   RCC_PLL_init();                         // System Clock = 84MHz
   UART2_init();
   SysTick_init(1);
   TIM_INT_enable(TIM4); 
   
   GPIO_pupd(GPIOA, 8, 0x00);
   GPIO_pupd(GPIOB, 6, 0x00);
   GPIO_otype(GPIOA, 8, 0);
   GPIO_ospeed(GPIOA, 8, 2);
   
   // ADC setting
    ADC_init(GPIOB, 0, TRGO);
   ADC_init(GPIOB, 1, TRGO);

   // ADC channel sequence setting
   ADC_sequence(2, seqCHn);
   
   // ADON, SW Trigger enable
   ADC_start();
   
   
   
  
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
    

         PWM_init(&dcPwm[A], dcPwmPin[A].port, dcPwmPin[A].Pin);
         PWM_init(&dcPwm[B], dcPwmPin[B].port, dcPwmPin[B].Pin);
      
      
   
   for (int i = 0; i < 2; i++){
      GPIO_init(dcDirPin[i].port, dcDirPin[i].Pin,OUTPUT);
      GPIO_pupd(dcDirPin[i].port, dcDirPin[i].Pin, 01);
      GPIO_otype(dcDirPin[i].port, dcDirPin[i].Pin, 0);
      GPIO_ospeed(dcDirPin[i].port, dcDirPin[i].Pin, 11);
   }
}

void ADC_IRQHandler(void){
   if((is_ADC_OVR())){
      clear_ADC_OVR();
   }
   
   if(is_ADC_EOC()){       //after finishing sequence
         if (flag==0){
            IR1 = ADC_read();
         }  
         else if (flag==1){
            IR2 = ADC_read();
         }
      flag =! flag;
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
