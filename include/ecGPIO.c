/**
******************************************************************************
* @author  SSSLAB
* @Mod		 2022-11-09 by Dongmin Kim  	
* @brief   Embedded Controller:  EC_HAL
* 
******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "ecGPIO.h"
#include "ecSysTick.h"

void bit_toggle(GPIO_TypeDef* Port, int pin){
	(Port->ODR) ^= (1UL << pin);
}

void LED_toggle(void){
	GPIOA->ODR ^= 1<< LED_PIN;
}

void GPIO_init(GPIO_TypeDef *Port, int pin, int mode){     
	// mode  : Input(0), Output(1), AlterFunc(2), Analog(3)   
	if (Port == GPIOA)
		RCC_GPIOA_enable();
	if (Port == GPIOB)
		RCC_GPIOB_enable();
	if (Port == GPIOC)
		RCC_GPIOC_enable();

	GPIO_mode(Port, pin, mode);
	
}

void GPIO_output(GPIO_TypeDef *Port, int pin, int type, int pupd, int speed){
		// Set TYPE
		Port->OTYPER &= 		~(type<<(pin));							 	// 0:Push-Pull
		// Set PUPD
		Port->PUPDR &= 	~(3UL<<(2*pin));
		Port->PUPDR  |=		pupd<<(2*pin);									// 10: Pull-UP
		// Set SPEED
		Port->OSPEEDR &= 	~(3UL<<(2*pin));
		Port->OSPEEDR |=  	speed <<(2*pin);
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


void multipleLED_init(void){
	
	//SysTick_init();
		
	

}


void multipleLED(uint32_t  num){   // Displaying 4xLEDs 0000 ~ 1111
	int count = 0;
	int number[8][3] = {
		{0,0,0}, 
		{0,0,1}, 
		{0,1,0}, 
		{0,1,1}, 
		{1,0,0},
		{1,0,1},
		{1,1,0},
		{1,1,1},
			};
		GPIO_write(GPIOA, 0, number[num][0]);
		GPIO_write(GPIOA, 1, number[num][1]);
		GPIO_write(GPIOB, 0, number[num][2]);		
		count++;
		if (count >10) count =0;

}



void sevensegment_init(void){

	GPIO_init(GPIOA, 8, OUTPUT);		// A
	GPIO_init(GPIOB, 10, OUTPUT);		// B	
	GPIO_init(GPIOA, 7, OUTPUT);		// C
	GPIO_init(GPIOA, 6, OUTPUT);		// D
	GPIO_init(GPIOB, 9, OUTPUT);		// E
	GPIO_init(GPIOA, 9, OUTPUT);		// F
	GPIO_init(GPIOC, 7, OUTPUT);		// G
	GPIO_init(GPIOB, 6, OUTPUT);		// DP
	

		//Set 7segment_PIN Push-Pull, No Pull-up/Pull-down, Medium Speed

	GPIO_output(GPIOA, 8, NONE, PUSH_PULL, MEDIUM_SPEED);		// A
	GPIO_output(GPIOB, 10,NONE, PUSH_PULL, MEDIUM_SPEED);		// B	
	GPIO_output(GPIOA, 7, NONE, PUSH_PULL, MEDIUM_SPEED);		// C
	GPIO_output(GPIOA, 6, NONE, PUSH_PULL, MEDIUM_SPEED);		// D
	GPIO_output(GPIOB, 9, NONE, PUSH_PULL, MEDIUM_SPEED);		// E
	GPIO_output(GPIOA, 9, NONE, PUSH_PULL, MEDIUM_SPEED);		// F
	GPIO_output(GPIOC, 7, NONE, PUSH_PULL, MEDIUM_SPEED);		// G
	GPIO_output(GPIOB, 6, NONE, PUSH_PULL, MEDIUM_SPEED);		// DP
		
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
		GPIO_write(GPIOB, 9, number[num][4]);  // E
		GPIO_write(GPIOA, 9, number[num][5]);  // F
		GPIO_write(GPIOC, 7, number[num][6]);  // G
		GPIO_write(GPIOB, 6, number[num][7]);  // DP
		 
		
	}	

void reverse_sevensegment_decode(uint8_t  num){
	
	// 7-segments Reversed TruthTable
		int number[10][8] = {
									// A B C D E F G DP
										{0,0,0,0,1,0,0,1},          //nine
									  {0,0,0,0,0,0,0,1},          //eight
                    {0,0,0,1,1,1,1,1},          //seven
                    {0,1,0,0,0,0,0,1},          //six										
                    {0,1,0,0,1,0,0,1},          //five										
                    {1,0,0,1,1,0,0,1},          //four										
                    {0,0,0,0,1,1,0,1},          //three									     
                    {0,0,1,0,0,1,0,1},          //two
										{1,0,0,1,1,1,1,1},          //one
										{0,0,0,0,0,0,1,1},          //zero
             
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
	
void pause_sevensegment_decode(void){   //For display 'P'
		
	//Clear
		GPIO_write(GPIOA, 8, HIGH);  // A
		GPIO_write(GPIOB, 10,HIGH); // B
		GPIO_write(GPIOA, 7, HIGH);  // C
		GPIO_write(GPIOA, 6, HIGH);  // D
		GPIO_write(GPIOB, 9, HIGH);  // E
		GPIO_write(GPIOA, 9, HIGH);  // F
		GPIO_write(GPIOC, 7, HIGH);  // G
		GPIO_write(GPIOB, 6, HIGH);  // DP
		
	// Set P
		GPIO_write(GPIOA, 8, LOW);  // A
		GPIO_write(GPIOB, 10,LOW); // B
		GPIO_write(GPIOB, 9, LOW);  // E
		GPIO_write(GPIOA, 9, LOW);  // F
		GPIO_write(GPIOC, 7, LOW);  // G
	}
			