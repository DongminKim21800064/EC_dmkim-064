/**
******************************************************************************
* @author	SSSLAB
* @Modified         : 10-10-2022 by DongMin Kim   	
* @brief	Embedded Controller:  LAB 7-segment 
*					 - 7 segment decoder
* 					-  PA5, PA6, PA7, PB6, PC7, PA9, PA8, PB10  for DOUT
******************************************************************************
*/

#include "stm32f4xx.h"
#include "ecGPIO.h"
#include "ecRCC.h"

#define LED_PIN 	5
#define BUTTON_PIN 13

void setup(void);


      
                  

int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	unsigned int cnt = 0;
	
										
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		sevensegment_decode(cnt % 10);
		if(GPIO_read(GPIOC, BUTTON_PIN) == 0) cnt++; 
		if (cnt > 9) cnt = 0;
		for(int i = 0; i < 500000;i++){}
	}
	
}


// Initialiization 
void setup(void)
{
	RCC_HSI_init();	
	GPIO_init(GPIOC, BUTTON_PIN, INPUT);  // calls RCC_GPIOC_enable()
	sevensegment_init();
}

					
			