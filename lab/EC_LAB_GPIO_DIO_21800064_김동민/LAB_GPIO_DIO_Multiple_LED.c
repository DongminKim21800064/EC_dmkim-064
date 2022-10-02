
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

void setup(void);

int main(void) { 
	 uint32_t i=0;
   // Initialiization --------------------------------------------------------
   multipleLED_init();
   
   // Inifinite Loop ----------------------------------------------------------
   while(1){
      if(GPIO_read(GPIOC, BUTTON_PIN) == 0){
         i++;
         if(i==5) i = 0;
			}
   multipleLED(i);
		}
}




