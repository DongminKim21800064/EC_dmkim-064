# LAB: EXTI SysTick 

**Date:** 2022-10-19

**Author/Partner:** DongMin Kim / SeongJun Park

**Github:**  

**Demo Video:**  https://youtu.be/HSpYIvjLOF0

# Introduction

In this lab, you are required to create two simple programs: toggling multiple LEDs with a push-button input and displaying the number counting from 0 to 9 at 1 second rate on a 7-segment display.



# Requirement

##### Hardware

- MCU

  - NUCLEO-F411RE

- Display

  - 4 LEDs and load resistance
  - 7-segment display(5101ASR)
- Others 

  - Array resistor (330 ohm)

  - Breadboard
  
    

#####  Software

- Keil uVision, CMSIS, EC_HAL library



# Problem 1: LED Toggle with EXTI Button

A program that toggles multiple LEDs with a push-button input using external interrupt.

### Create HAL library

 Declare and Define the following functions in your library. You must

update your header files located in the directory `EC \lib\`.

**ecEXTI.h**

```c
void EXTI_init(GPIO_TypeDef *port, int pin, int trig_type, int priority);
void EXTI_enable(uint32_t pin);  // mask in IMR
void EXTI_disable(uint32_t pin);  // unmask in IMR
uint32_t  is_pending_EXTI(uint32_t pin);
void clear_pending_EXTI(uint32_t pin);
```



### Procedure

1. Create a new project under the directory `\repos\EC\LAB\LAB_EXTI`

- The project name is “**LAB_EXTI”.**
- Create a new source file named as “**LAB_EXTI.c”**

> You MUST write your name on the source file inside the comment section.

2. Include your updated library in `\repos\EC\lib\` to your project.

- **ecGPIO.h, ecGPIO.c**
- **ecRCC.h, ecRCC.c**
- **ecEXTI.h, ecEXTI.c**

1. Connect 4 LEDs externally on a breadboard.
2. Toggle LEDs, turning on one LED at a time by pressing the push button.
   - Example: LED0--> LED1--> …LED3--> …LED0….
3. You must use your library function of EXTI.
4. Refer to the [sample code](https://ykkim.gitbook.io/ec/firmware-programming/example-code#button-interrupt)



### Configuration

| Button        | LED                              |
| ------------- | -------------------------------- |
| Digital In    | Digital Out                      |
| GPIOC, Pin 13 | PA5, PA6, PA7, PB6               |
| PULL-UP       | Push-Pull, Pull-up, Medium Speed |



### Circuit Diagram

> You need to include the circuit diagram

![image-20221019114026373](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20221019114026373.png)



### Discussion

1. To detect an external signal we can use two different methods: polling and interrupt. What are the advantages and disadvantages of each approach?

   ​	Interrupts and polling are the ways to handle events.

   ​	**Polling** is a method of running an event when it is received by periodically checking whether it has been received or not. The advantage of polling is that the process of implementing it with code is also simple. There is a disadvantage in that the reaction time is slow and takes up a lot of resources.

   ​	**Interrupt** is a method of performing an event directly through the handler when you receive a signal to perform the event. Interrupts have the advantages of accurate timing, short reaction time, and the disadvantages of implementation because they have to be through handlers.

   

2. What would happen if the EXTI  interrupt handler does not clear the interrupt pending flags? Check with your code

   ​	Once the LED is turn on, LED looks like never turns off before reset. In reality, because the pending value was not cleared, the function in the interrupt  handler was repeatedly running at a very high speed, which seemed to keep the LED  turning on state because it could not be recognized by the human eye. 
   
   To check this phenomenon, i tried to these process. As you can see, the code was  written to repeat the function of turning off the LED while the handler function was  running once, and it was confirmed that the brightness of the LED decreased.

![image-20221019212211346](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20221019212211346.png)

### Code

Your code goes here :

##### LAB_EXIT.c

```c
#include "ecRCC.h"
#include "ecGPIO.h"
#include "ecEXTI.h"
#include "stm32f411xe.h"

void setup(void);
void EXTI15_10_IRQHandler(void);

int main(void) {

	// System CLOCK, GPIO Initialiization ----------------------------------------
	setup();

	while (1){}
}

void EXTI15_10_IRQHandler(void) {
	uint32_t count=0;
	while(1){
	if (is_pending_EXTI (BUTTON_PIN)) {
			if(count==4) count = 0;
			multipleLED(count);
			count++;
		 clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
			}	
		}
	}
 
// Initialiization 
void setup(void)
{
	RCC_PLL_init();                         
	// Initialize multipleLED_init() for Output
  	multipleLED_init();
	EXTI_init(GPIOC, BUTTON_PIN, FALL, 0);
}
```

**code: EXTI15_10_IRQHandler**

​	The BUTTON_PIN is pin 13 so, it operates in External Line[15:10].  When the BUTTON_PIN interrupt, multipleLED start and cleared by ''clear_pending_EXTI(BUTTON_PIN)".

​	In this lab, I use 4 LED pins and toggled them. In the iteration, 'count' is increased until 4 and reset for turning on 4 LED pins sequentially.

**code: multipleLED_init()**

​	"multipleLED_init" is initialized digital in and out. To match the configuration, the button pin is pull-up mode, and the led pins are push-pull, pull-up and medium-speed mode like below.

```c
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
```

**code: EXTI_init**

​	Exti_init initialize port, pin number, trig type, and priority. 

### Results

Experiment images and results

> ![image-20221019212740823](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20221019212740823.png)



**Demo Video:** https://youtu.be/HSpYIvjLOF0





# Problem 2: Counting number on 7-Segment

Display the number 0 to 9 on the 7-segment LED at the rate of 1 sec. After displaying up to 9, then it should display ‘0’ and continue counting.

When the button is pressed, the number should be reset ‘0’ and start counting again.

### Create HAL library

Declare and Define the following functions in your library. You must

update your header files located in the directory `EC \lib\`.

##### ecSysTick.h

```c
void SysTick_init(uint32_t msec);
void delay_ms(uint32_t msec);
uint32_t SysTick_val(void);
void SysTick_reset (void);
void SysTick_enable(void);
void SysTick_disable (void)
```



###  Procedure

1. Create a new project under the directory

   `\repos\EC\LAB\LAB_EXTI_SysTick`

- The project name is “**LAB_EXTI_SysTick”.**

- Create a new source file named as “**LAB_EXTI_SysTick.c”**

> You MUST write your name on the source file inside the comment section.

2. Include your updated library in `\repos\EC\lib\` to your project.

- **ecGPIO.h, ecGPIO.c**
- **ecRCC.h, ecRCC.c**
- **ecEXTI.h, ecEXTI.c**
- **ecSysTick.h, ecSysTick.c**

1. First, check if every number, 0 to 9, can be displayed properly on the 7-segment.
2. Then, create a code to display the number counting from 0 to 9 and repeat at the rate of 1 second.
3. When the button is pressed, it should start from '0' again. Use EXTI for this reset.
4. Refer to the [sample code](https://ykkim.gitbook.io/ec/stm32-m4-programming/example-code#systick-interrupt)



### Configuration

| Digital In for Button (B1) | Digital Out for 7-Segment                                    |
| -------------------------- | ------------------------------------------------------------ |
| Digital In                 | Digital Out                                                  |
| PC13                       | PA5, PA6, PA7, PB6, PC7, PA9, PA8, PB10 ('a'~'h', respectively) |
| PULL-UP                    | Push-Pull, No Pull-up-Pull-down, Medium Speed                |



### Circuit Diagram


![image](https://user-images.githubusercontent.com/91419683/194772659-14e47d9d-f85f-48e9-8f10-4b829c286b05.png)



### Code

Your code goes here :

**LAB_EXIT_SysTick.c**

```c
#include "stm32f411xe.h"
#include "ecGPIO.h"
#include "ecRCC.h"
#include "ecEXTI.h"
#include "ecSysTick.h"

static volatile uint32_t count = 0;
static volatile uint32_t flag = 0;


void setup(void);
void EXTI15_10_IRQHandler(void);	

int main(void) { 
	// Initialiization --------------------------------------------------------
		setup();
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){

		
		if(flag==0){
			sevensegment_decode(count);
			delay_ms(1000);
			count++;
		if (count >9) count =0;
		
	}
		else if(flag==1){
			count = 0;
			sevensegment_decode(count);
			flag = 0;
		}
		SysTick_reset();
	}
}

void EXTI15_10_IRQHandler(void) {
	if (is_pending_EXTI (BUTTON_PIN)) {
			flag= 1;
			clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
			}	
		}
	
// Initialiization 
void setup(void)
{
	RCC_PLL_init();
	SysTick_init(1000); //systick period : 1000=1ms , 2000=0.5ms, 500=2ms
	sevensegment_init();
	EXTI_init(GPIOC, BUTTON_PIN, FALL, 0);
}
```

**code: main**

​	Flag distinguishes whether button is pressed or not.  If the flag is 0, seven-segment starts to display up-counting from 0 to 9. If the flag is 1, seven-segment display 0.

**code: EXTI15_10_IRQHandler**

​	The BUTTON_PIN is pin 13 so, it operates in External Line[15:10].  When the BUTTON_PIN interrupt, flag is on  and cleared by ''clear_pending_EXTI(BUTTON_PIN)".

**code: SysTick_init()**

​	"SysTick_init" is initialized and control the systick period. If I insert '1000', then 7-segment display 1 sec per number.

**code: sevensegment_init()**

​	"sevensegment_init" is initialized digital in and out. To match the configuration, the button pin is pull-up mode, and the 7 segment pins are push-pull, NO pull-up-pull-down and medium-speed mode.

**code: EXTI_init**

​	Exti_init initialize port, pin number, trig type, and priority. 

### Results

Experiment images and results

> ![image-20221019224046333](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20221019224046333.png)

demo video: https://youtu.be/HSpYIvjLOF0 



### Analysis





### Reference

Complete list of all references used (github, blog, paper, etc)



### Troubleshooting



