/**
******************************************************************************
* @author  Dongmin Kim & Jinho Kiik
* @Mod		 2022-12-16 by Dongmin Kim  	
* @brief   Embedded Controller:  Final Project_ Forklift_Piezosensor
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
#include "ecEXTI.h"
#include "math.h"
#include "string.h"



//IR parameter//
uint32_t IR1, IR2;
//int flag = 0;
int seqCHn[1] = {8};
int forklift_flag = 0;


#define END_CHAR 13
#define A 0
#define B 1
#define MAX_BUF 100

PWM_t pwm11;

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
int Auto_mode = 1;
int pressure = 0;

uint16_t flagidx =0;



uint32_t ovf_cnt = 0;
float distance = 0;
float timeInterval = 0;
float time1 = 0;
float time2 = 0;



void setup(void);





int main(void) { 

   // Initialiization --------------------------------------------------------
   setup();
     printf("Hello Nucleo\r\n");
      ADC_start();


   
   // Inifinite Loop ----------------------------------------------------------
   while(1){   
       if (pressure >= 100){
         GPIO_write(GPIOA, 5, 1);
         delay_ms(1000);
       }
       
       else if (pressure < 100){
         GPIO_write(GPIOA, 5, 0);
      delay_ms(1000);
               }   
   printf("pressure = %d \r\n", pressure);        
       }         
 }

             

// Initialiization 
void setup(void)
{   
   RCC_PLL_init();                         // System Clock = 84MHz
   UART2_init();
   SysTick_init(1);
  // TIM_INT_enable(TIM4); 
      GPIO_init(GPIOA, 5, 0x01);
      USART_init(USART2, 9600);
   //   USART_begin(USART1, GPIOA, 9, GPIOA, 5, 9600);    // PA9 - RXD , PA10 - TXD 
   
   
   
   // ADC setting
   ADC_init(GPIOB, 0, TRGO);
  

   // ADC channel sequence setting
   ADC_sequence(1, seqCHn);
   
   // ADON, SW Trigger enable
   ADC_start();
 
                                    
}

void ADC_IRQHandler(void){
   if((is_ADC_OVR())){
      clear_ADC_OVR();
   }
   
   if(is_ADC_EOC()){       //after finishing sequence
         
            pressure = ADC_read();
         
   }
}

