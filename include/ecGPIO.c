/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : SSS Lab
Created          : 05-03-2021
Modified         : 10-01-2022 by DongMin Kim
Language/ver     : C++ in Keil uVision

Description      : Distributed to Students for LAB_GPIO
/----------------------------------------------------------------*/



#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "ecGPIO.h"
#include "ecSysTick.h"

void bit_toggle(GPIO_TypeDef* Port, int pin){
	(Port->ODR) ^= (1UL << pin);
}

void GPIO_init(GPIO_TypeDef *Port, int pin, int mode){     
	// mode  : Input(0), Output(1), AlterFunc(2), Analog(3)   
	if (Port == GPIOA)
		RCC_GPIOA_enable();
	if (Port == GPIOB)
		RCC_GPIOB_enable();
	if (Port == GPIOC)
		RCC_GPIOC_enable();
	
	//[TO-DO] YOUR CODE GOES HERE
	// Make it for GPIOB, GPIOD..GPIOH


	// You can also make a more general function of
	// void RCC_GPIO_enable(GPIO_TypeDef *Port); 

	GPIO_mode(Port, pin, mode);
	
}


// GPIO Mode          : Input(00), Output(01), AlterFunc(10), Analog(11)
void GPIO_mode(GPIO_TypeDef *Port, int pin, int mode){
   Port->MODER &= ~(3UL<<(2*pin));     
   Port->MODER |= mode <<(2*pin);    
}


// GPIO Speed          : Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
void GPIO_ospeed(GPIO_TypeDef *Port, int pin, int speed){
	  Port->OSPEEDR &= 	~(3UL<<(2*pin));
		Port->OSPEEDR |=  	speed <<(2*pin);								 //10:Fast Speed
}

// GPIO Output Type: Output push-pull (0, reset), Output open drain (1)
void GPIO_otype(GPIO_TypeDef *Port, int pin, int type){
		Port->OTYPER &= 		~(type<<(pin));							 	// 0:Push-Pull   
}

// GPIO Push-Pull    : No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
void GPIO_pupd(GPIO_TypeDef *Port, int pin, int pupd){
   	Port->PUPDR &= 	~(3UL<<(2*pin));
		Port->PUPDR  |=		pupd<<(2*pin);									// 10: Pull-UP		
}

int GPIO_read(GPIO_TypeDef *Port, int pin){

	unsigned int btVal=0;
			//Read bit value of Button
			btVal=(Port->IDR>>pin) & 1UL;	
	return btVal;    	//[TO-DO] YOUR CODE GOES HERE	
}



void GPIO_write(GPIO_TypeDef *Port, int pin, int Output){
	Port->ODR &= ~(1UL<<(pin));
  Port->ODR |= (Output <<(pin));
}


void multipleLED_init(void)
{
	RCC_HSI_init();	
	SysTick_init();
	
	GPIO_init(GPIOC, BUTTON_PIN, INPUT);  // calls RCC_GPIOC_enable()
	GPIO_init(GPIOA, 5, OUTPUT);    // calls RCC_GPIOA_enable()
	GPIO_init(GPIOA, 6, OUTPUT);
	GPIO_init(GPIOA, 7, OUTPUT);
	GPIO_init(GPIOB, 6, OUTPUT);

	// Digital in --------------------------------------------------------------
	GPIO_pupd(GPIOC, BUTTON_PIN, EC_PU);

	// Digital out -------------------------------------------------------------
	GPIO_pupd(GPIOA, 5, EC_PU);
	GPIO_otype(GPIOA, 5, PUSH_PULL);
	GPIO_ospeed(GPIOA, 5, MEDIUM_SPEED);

	GPIO_pupd(GPIOA, 6, EC_PU);
	GPIO_otype(GPIOA, 6, PUSH_PULL);
	GPIO_ospeed(GPIOA, 6, MEDIUM_SPEED);

	GPIO_pupd(GPIOA, 7, EC_PU);
	GPIO_otype(GPIOA, 7, PUSH_PULL);
	GPIO_ospeed(GPIOA, 7, MEDIUM_SPEED);

	GPIO_pupd(GPIOB, 6, EC_PU);
	GPIO_otype(GPIOB, 6, PUSH_PULL);
	GPIO_ospeed(GPIOB, 6, MEDIUM_SPEED);

}


void multipleLED(uint32_t  num){
	int count = 0;
	int number[5][4] = {
		{0,0,0,0},
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1},
	};
		GPIO_write(GPIOA, 5, number[num][0]);
		GPIO_write(GPIOA, 6, number[num][1]);
		GPIO_write(GPIOA, 7, number[num][2]);
		GPIO_write(GPIOB, 6, number[num][3]);
	
		delay_ms(50);
		
		count++;
		if (count >10) count =0;
		SysTick_reset();
}

void sevensegment_init(void){

	GPIO_init(GPIOA, 8, OUTPUT);		// A
	GPIO_init(GPIOB, 10, OUTPUT);		// B	
	GPIO_init(GPIOA, 7, OUTPUT);		// C
	GPIO_init(GPIOA, 6, OUTPUT);		// D
	GPIO_init(GPIOA, 5, OUTPUT);		// E
	GPIO_init(GPIOA, 9, OUTPUT);		// F
	GPIO_init(GPIOC, 7, OUTPUT);		// G
	GPIO_init(GPIOB, 6, OUTPUT);		// DP
	
	//Set PULL-UP Mode
	GPIO_pupd(GPIOC, BUTTON_PIN, EC_PU); 			// PULL-UP  
	
	GPIO_pupd(GPIOA, LED_PIN, EC_PU);					// PULL-UP
	GPIO_otype(GPIOA, LED_PIN, PUSH_PULL); 		// PUSH-PULL
	GPIO_ospeed(GPIOA, LED_PIN,MEDIUM_SPEED); // MEDIUM-SPEED
}

void sevensegment_decode(uint8_t  num){
	
	// 7-segments Reversed TruthTable
		int number[10][8] = {
									// A B C D E F G DP
										{0,0,0,0,0,0,1,1},          //zero
                    {1,0,0,1,1,1,1,1},          //one
                    {0,0,1,0,0,1,0,1},          //two
                    {0,0,0,0,1,1,0,1},          //three
                    {1,0,0,1,1,0,0,1},          //four
                    {0,1,0,0,1,0,0,1},          //five
                    {0,1,0,0,0,0,0,1},          //six
                    {0,0,0,1,1,1,1,1},          //seven
                    {0,0,0,0,0,0,0,1},          //eight
                    {0,0,0,0,1,0,0,1},          //nine
						};				

		GPIO_write(GPIOA, 8, number[num][0]);  // A
		GPIO_write(GPIOB, 10, number[num][1]); // B
		GPIO_write(GPIOA, 7, number[num][2]);  // C
		GPIO_write(GPIOA, 6, number[num][3]);  // D
		GPIO_write(GPIOA, 5, number[num][4]);  // E
		GPIO_write(GPIOA, 9, number[num][5]);  // F
		GPIO_write(GPIOC, 7, number[num][6]);  // G
		GPIO_write(GPIOB, 6, number[num][7]);  // DP
		 
		
	}	
					