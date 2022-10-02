# LAB: GPIO Digital InOut 

**Date:** 2022-10-02

**Author/Partner:** Dongmin Kim / Jinho Guk

**Github:** repository link

**Demo Video:** Youtube link

# Introduction

In this lab, you are required to create a simple program that toggle multiple LEDs with a push-button input. Create HAL drivers for GPIO digital in and out control and use your library.



# Requirement

##### Hardware

- MCU

  - NUCLEO-F401RE

- Actuator/Sensor/Others:

  - LEDs x 4

  - Resistor 330 ohm x 3, breadboard

    

#####  Software

- Keil uVision, CMSIS, EC_HAL library



# Problem 1: Create EC_HAL library

## Procedure

Create the library directory `\repos\EC\lib\`.

Save your header library files in this directory. [See here for detail.](https://ykkim.gitbook.io/ec/uvision/adding-my-api-header-in-uvision)

> DO NOT make duplicates of library files under each project folders

List of functions for Digital_In and Out .

[Library file LINK such as github](https://github.com/ykkimhgu/EC-student/)

**ecRCC.h** (provided)

```
void RCC_HSI_init(void);  
void RCC_GPIOA_enable(void);   
void RCC_GPIOB_enable(void); 
void RCC_GPIOC_enable(void);
```

**ecGPIO.h**

```
void GPIO_init(GPIO_TypeDef *Port, int pin,  int mode);  

void GPIO_write(GPIO_TypeDef *Port, int pin,  int output);  

int  GPIO_read(GPIO_TypeDef *Port, int pin);  

void GPIO_mode(GPIO_TypeDef* Port, int pin, int mode);  

void GPIO_ospeed(GPIO_TypeDef* Port, int pin,  int speed);  

void GPIO_otype(GPIO_TypeDef* Port, int pin,  int type);  

void GPIO_pupd(GPIO_TypeDef* Port, int pin,  int pupd);
```

#####  ecRCC.c

See Appendix

 ##### ecGPIO.c

See Appendix



# Problem 2: Toggle LED with Button

## Procedure

1. Create a new project under the directory  `\respos\EC\LAB\ `



- The project name is “**LAB_GPIO_DIO_LED”.**
- Name the source file as “**LAB_GPIO_DIO_LED.c”**
- Use the [example code provided here](https://github.com/ykkimhgu/EC-student/blob/main/lab/lab-student/LAB_GPIO_DIO_LED_student.c).

2. Include your library **ecGPIO.h, ecGPIO.c** in `\repos\EC\lib\`.

> You MUST write your name in the top of the source file, inside the comment section.

3. Toggle the LED by pushing button.

- Pushing button (LED ON), Pushing Button (LED OFF) and repeat



## Configuration

| Button (B1)   | LED                               |
| ------------- | --------------------------------- |
| Digital In    | Digital Out                       |
| GPIOC, Pin 13 | GPIOA, Pin 5                      |
| PULL-UP       | Open-Drain, Pull-up, Medium Speed |

## Code

Your code goes here: [ADD Code LINK such as github](https://github.com/ykkimhgu/EC-student/)

Explain your source code with necessary comments.

**LAB_GPIO_DIO_LED.c**

``` c
#include "stm32f4xx.h"
#include "ecRCC.h"
#include "ecGPIO.h"
#include "ecSysTick.h"

#define LED_PIN 	5
#define BUTTON_PIN 13

void setup(void);
	
int main(void) { 

	// Initialiization --------------------------------------------------------
	setup();
	
	 //Inifinite Loop ----------------------------------------------------------
	while(1){
		// When the button pressed
		if(GPIO_read(GPIOC, BUTTON_PIN) == 0){
			bit_toggle(GPIOA, LED_PIN);
		}	
		// For debouncing
		delay_ms(50);
		SysTick_reset();
	}
}

// Initialiization 
void setup(void)
{
	RCC_HSI_init();	
	SysTick_init();
	GPIO_init(GPIOC, BUTTON_PIN, INPUT);  		// calls RCC_GPIOC_enable()
	GPIO_pupd(GPIOC, BUTTON_PIN, EC_PU); 		// PULL-UP  
	
	GPIO_init(GPIOA, LED_PIN, OUTPUT);    		// calls RCC_GPIOA_enable()
	GPIO_pupd(GPIOA, LED_PIN, EC_PU);			// PULL-UP
	GPIO_otype(GPIOA, LED_PIN, OPEN_DRAIN); 	// OPEN-DRAIN
	GPIO_ospeed(GPIOA, LED_PIN,MEDIUM_SPEED);   // MEDIUM-SPEED
}
```

This is the main code of Problem 2. I included the necessary header file and defined the pin number of the LED and Button.

In the **setup** function, I declared GPIO functions for requiring configurations. As you can see from the code, the Button pin set PULL-UP and the LED pin set PULL-UP, OPEN-DRAIN, and MEDIUM-SPEED. 

In the **main** function, I made the infinite loop. When I pressed the button, LED will toggle. The details of **bit_toggle** are below.

**bit_toggle**

```c
void bit_toggle(GPIO_TypeDef* Port, int pin){
	(Port->ODR) ^= (1UL << pin);
}
```

Enter the GPIOC port and toggle the position of the LED pin using XOR bitwise.

## Discussion

1. Find out a typical solution for software debouncing and hardware debouncing. 

   There's the word bouncing, which means that when a human-touch sensor, such as a real switch button, presses this sensor, and at the moment, the on/off is repeated several times in the sensor's close contact.

   Software

   A typical solution to solve Bouncing with software is giving a time delay. For example, if the time to Bouncing when the switch is pressed is 30 ms.  the time delay is given to 50 ms. there is a time delay of 20 ms after the Bouncing is over, so the Bouncing can be solved.

   Hardware

   To eliminate Bouncing(chattering) in the switch button by hardware way, I can add capacitors that can act on the switch. The timing of chattering is different depending on the type of switch and the attached instrument, so the resistance is added to each application to control the timing to prevent chattering by adjusting the time constant by RC.

2. What method of debouncing did this NUCLEO board used for the push-button(B1)?

   The NUCLEO board used a method of solving Bouncing by giving time delay to  software. I gave a delay to the main function using the functions "ecSysTick.c" and "ecSysTick.h" given in the class.

# Problem 3: Toggle multi-LED with Button

## Procedure

1. Create a new project under the directory  `\respos\EC\LAB\ `
- The project name is “**LAB_GPIO_DIO_multiLED”.** 
  
- Name the source file as “**LAB_GPIO_DIO_multiLED.c”**

   > You MUST write your name in the top of the source file, inside the comment section.

   1. Include your library **ecGPIO.h, ecGPIO.c** in `\repos\lib\`.
   2. Connect 4 LEDs externally with necessary load resistors.

   - As Button B1 is Pressed, light one LED at a time, in sequence.
   - Example: LED0--> LED1--> …LED3--> …LED0….

## Configuration

| Button (B1)   | LED                              |
| ------------- | -------------------------------- |
| Digital In    | Digital Out                      |
| GPIOC, Pin 13 | PA5, PA6, PA7, PB6               |
| PULL-UP       | Push-Pull, Pull-up, Medium Speed |



## Circuit Diagram

Circuit diagram

lab/EC_LAB_GPIO_DIO_21800064_김동민/multipleLED_Circuit_Diagram.png  





## Code

Your code goes here: [ADD Code LINK such as github](https://github.com/ykkimhgu/EC-student/)

Explain your source code with necessary comments.

```c
// Your MAIN CODE ONLY
```



## Discussion

1. Find out a typical solution for software debouncing and hardware debouncing. What method of debouncing did this NUCLEO board used for the push-button(B1)?

## Reference



## Troubleshooting



## Appendix

