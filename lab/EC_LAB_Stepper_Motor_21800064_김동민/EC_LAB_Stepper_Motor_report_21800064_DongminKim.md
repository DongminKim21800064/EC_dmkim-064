# LAB: Stepper Motor 

**Date:** 2022-11-01

**Author/Partner:** DongMin Kim / SeongJun Park

**Github:**  

**Demo Video:**  

# Introduction

In this lab, we will learn how to drive a stepper motor with digital output of GPIOs of MCU. You will use a FSM to design the algorithm for stepper motor control.



# Requirement

##### Hardware

- MCU

  - NUCLEO-F411RE

- Actuator

  - 3Stepper Motor 28BYJ-48
  - Motor Driver ULN2003

#####  Software

- Keil uVision, CMSIS, EC_HAL library



# Problem 1: Stepper Motor

### Hardware Connection

Read specification sheet of the motor and the motor driver for wiring and min/max input voltage/current.

![img](https://user-images.githubusercontent.com/91526930/197428440-9f4a9c8c-2d81-4d0e-a4e2-b4a4b9def44d.png)

![img](https://user-images.githubusercontent.com/91526930/197428469-a0d7a8fa-ba4c-482f-8688-ea87cfd9f4e0.png)



### Stepper Motor Sequence

We will use unipolar stepper motor for this lab

Fill in the blanks of each output data depending on the below sequence.

**Full-stepping sequence**

![img](https://user-images.githubusercontent.com/91526930/197428513-f9a23147-3448-4bed-bda2-c90325b8c143.png)

**Half-stepping sequence**

![img](https://user-images.githubusercontent.com/91526930/197429006-d552ab16-0bbf-4c52-bdce-a0f2bfe5f0d8.png)

### Finite State Machine

Draw a State Table for Full-Step Sequence. Use Moore FSM for this case. See *‘Programming FSM’* for hints.

- Full-Stepping Sequence

  

- Half-Stepping Sequence

  

## Problem 2: Firmware Programming

### Create HAL library

Declare and Define the following functions in your library. You must

update your header files located in the directory `EC \lib\`.

**ecStepper.h**

```c
// Initialize with 4 pins

void Stepper_init(GPIO_TypeDef* port1, int pin1, GPIO_TypeDef* port2, int pin2, GPIO_TypeDef* port3, int pin3, GPIO_TypeDef* port4, int pin4);



// whatSpeed [rev/min]

void Stepper_setSpeed(long whatSpeed,int mode );



// Run for n Steps

void Stepper_step(int steps, int direction, int mode); 



// Immediate Stop.

void Stepper_stop(void);
```



### Procedure

1. Create a new project under the directory `\repos\EC\LAB\LAB_Stepper_Motor`

   - 

     The project name is “**LAB_Stepper_Motor”.**

   - 

     Create a new source file named as “**LAB_Stepper_Motor.c”**

     > You MUST write your name on the source file inside the comment section.

2. Include your updated library in `\repos\EC\lib\` to your project.

   - **ecGPIO.h, ecGPIO.c**
   - **ecRCC.h, ecRCC.c**
   - **ecEXTI.h, ecEXTI.c**
   - **ecSysTick.h**, **ecSysTick.c**
   - **ecStepper.h** **ecStepper.h**

3. Connect the MCU to the motor driver and the stepper motor.

4. Find out the number of steps required to rotate 1 revolution using Full-steppping.

5. Then, rotate the stepper motor 10 revolutions with 2 rpm. Measure if the motor rotates one revolution per second.

6. Repeat the above process with the opposite direction.

7. Increase and decrease the speed of the motor as fast as it can rotate to find the max speed of the motor.

8. Apply the half-stepping and repeat the above.

### Configuration

| Digital Out          | SysTick |
| -------------------- | ------- |
| PB10, PB4, PB5, PB3  | delay() |
| NO Pull-up Pull-down |         |
| Push-Pull            |         |
| Fast                 |         |



### Requirement

You have to program the stepping sequence using the state table. You can define the states using structures. Refer to *‘Programming FSM’* for hints.

![img](https://user-images.githubusercontent.com/91526930/197430711-7610eb31-56c3-4cdd-88c7-6be689e1d3c7.png)

image

### Discussion

1. Find out the trapezoid-shape velocity profile for stepper motor. When is this profile necessary?

   > Answer discussion questions

2. How would you change the code more efficiently for micro-stepping control? You don’t have to code this but need to explain your strategy.

   > Answer discussion questions

### Code

Your code goes here: [ADD Code LINK such as github](https://github.com/ykkimhgu/EC-student/)

Explain your source code with necessary comments.

**LAB_Stepper_Motor.c**

```c
#include "stm32f411xe.h"
#include "ecGPIO.h"
#include "ecRCC.h"
#include "ecEXTI.h"
#include "ecSysTick.h"
#include "ecStepper.h"					

void setup(void);
volatile uint32_t rev = 1;

int main (void){
	// Initialization------------------------------------------------
	setup();
	
	Stepper_step(2048*rev, 1, FULL); // (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)

	// Infinite Loop -------------------------------------------------
	while(1){;}
}

// Initialization
void setup(void){
	RCC_PLL_init();		// System Clock = 84Mz 																		
	SysTick_init(1); 	// Systick init
		
	EXTI_init(GPIOC, BUTTON_PIN, FALL, 0);		// External Interrupt Setting
	GPIO_init(GPIOC, BUTTON_PIN, INPUT);		// GPIOC pin 13 Initialization
	
    // Stepper GPIO pin Initialization
    // No pull-up Pull-down , Push-Pull, Fast
	Stepper_init(GPIOB, 10, GPIOB, 4 , GPIOB,5, GPIOB,3);  	
	Stepper_setSpeed(18,FULL);	// set stepper motor speed (0~18)															
}

void EXTI15_10_IRQHandler(void){
	if(is_pending_EXTI(BUTTON_PIN)){
		Stepper_stop();
		clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
	}
}
```

**main**

> Initialize set up, and declare "Stepper_step" function.
>
> "Stepper_step" set total step, Direction(CW/CCW), and MODE(FULL/HALF).

**setup**

> Set up RCC_PLL, and SysTick(1ms or us).
>
> Set up external interrupt setting and GPIO(BUTTON PIN).
>
> Set up Stepper initialization and speed.

**EXTI15_10_IRQHandler**

> EXTI Interrupt.
>
> If button pin pushed, stepper motor go to stop mode.



**Sample Code : Stepper Motor**

![img](https://user-images.githubusercontent.com/91526930/197431877-bffe4801-453f-42d8-b6ff-e8b9525e4f95.png)

image

### Results

Experiment images and results

> Show experiment images /results

Add [demo video link](https://github.com/ykkimhgu/course-doc/blob/master/course/lab/link/README.md)



### Analysis





## Reference

Complete list of all references used (github, blog, paper, etc)

## Troubleshooting

(Option) You can write Troubleshooting section