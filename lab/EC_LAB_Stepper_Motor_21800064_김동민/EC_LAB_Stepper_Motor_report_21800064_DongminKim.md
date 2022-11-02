# LAB: Stepper Motor 

**Date:** 2022-11-01

**Author/Partner:** DongMin Kim / SeongJun Park

**Github:**  https://github.com/DongminKim21800064/EC_dmkim-064

**Demo Video:**  https://youtu.be/L4a_5KlcQZk

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
![image](https://user-images.githubusercontent.com/91419683/199210301-5c73ff59-49e2-455d-9655-1b991acc6c63.png)

**Half-stepping sequence**

![img](https://user-images.githubusercontent.com/91526930/197429006-d552ab16-0bbf-4c52-bdce-a0f2bfe5f0d8.png)
![image](https://user-images.githubusercontent.com/91419683/199210347-66f6adcc-43a2-4050-af87-f41a91991b08.png)

### Finite State Machine

Draw a State Table for Full-Step Sequence. Use Moore FSM for this case. See *‘Programming FSM’* for hints.

- Full-Stepping Sequence

  ![image](https://user-images.githubusercontent.com/91419683/199210419-95ff33f6-d831-4d38-937b-bbfa31f7a4f8.png)


- Half-Stepping Sequence
![image](https://user-images.githubusercontent.com/91419683/199210509-a0fd02e9-620c-49d6-aa05-4b7b0f343bc5.png)

  

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

   - The project name is “**LAB_Stepper_Motor”.**

   - Create a new source file named as “**LAB_Stepper_Motor.c”**

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

   > **Rectangular **
   >
   > ![img](https://blogfiles.pstatic.net/MjAyMjA5MjJfMzAw/MDAxNjYzODQ0NTMwMjY4.RJI5BUhFRhPsMgseVi6y9eX-5vYqU2jshipPJVS-adMg.hgtAabWv_kkDwJtATMB3IrgC5bRjMVyMqVGcAL5uFfgg.PNG.licky8131/20220921_222656.png)
   >
   > **Trapezoid**
   >
   > ![img](https://blogfiles.pstatic.net/MjAyMjA5MjJfODkg/MDAxNjYzODQ0NTIzNTM5.LxpCVm6jCEnUUcel5Ms_uvsUMvb8pAzWJ9Ma4rkreTQg.iLUlXfOhp6hHOOU-Gw-lGaJNBzhkqb9dvDTZ9tyRPSYg.PNG.licky8131/20220921_215444.png)
   >
   >  If the output power of the motor suddenly changes from LOW to HIGH, overshoot is generated at the point where it becomes HIGH, as in the Rectangular waveform, resulting in vibration of the motor. 
   >
   >  This is related to the law of inertia. Increasing the power of the motor, such as the trapezoid, low generates inertia, reducing the generation of overshoot and reducing the vibration of the motor.
   >
   > Therefore, the trapezoid can be more stable for motor control.

   

2. How would you change the code more efficiently for micro-stepping control? You don’t have to code this but need to explain your strategy.

   > ![image-20221102211050654](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20221102211050654.png)
   >
   > ![img](https://blogfiles.pstatic.net/MjAyMTA0MjdfMjkz/MDAxNjE5NTA5NzgxOTI0.fqf823kcR0wZROZE854OhSdNEganF8CQx6cB5Ll7wBUg.O72cIhRBTed8gEchg6xBdWX8CN8eFcF3w4xiIA4nyEEg.JPEG.jeonghyun_0/%EB%A7%88%EC%9D%B4%ED%81%AC%EB%A1%9C_%EC%8A%A4%ED%85%8C%ED%95%91.jpg) 
   >
   >  Micro-stepping, which is used as a way to control the operation of the step motor more precisely, is controlled by dividing the rotation angle corresponding to the pull-step into multiple sub-steps. When the full step angle is 90 degrees, it is decomposed into multiple steps such as 1/4, 1/8, 1/16, 1/32 to control the rotation at a more precise step angle.
   >
   > In my code, decomposed into multipel steps like  
   >
   > S0-> (S0_1,S0_2,S0_3,S0_4), ... S0-> (S3_1,S3_2,S3_3,S3_4)  and   
   >
   > S0_1 = (0.25 0.25 0 0), S0_2 = (0.5 0.5 0 0), S0_3 = (0.75 0.75 0 0), S0_4 = (1 1 0 0)... 

### Code

Your code goes here: https://github.com/DongminKim21800064/EC_dmkim-064

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
volatile uint32_t rev = 10;
volatile uint32_t rpm = 20;
volatile uint32_t mode = HALF;
int main (void){
	// Initialization------------------------------------------------
	setup();
	
	Stepper_step(2048*rev, 0, mode); // (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)

	// Infinite Loop -------------------------------------------------
	while(1){;}
}

// Initialization
void setup(void){
	RCC_PLL_init();																				// System Clock = 84Mz 																		
	SysTick_init(1);																		// Systick init
		
	EXTI_init(GPIOC, BUTTON_PIN, FALL, 0);		// External Interrupt Setting
	GPIO_init(GPIOC, BUTTON_PIN, INPUT);		// GPIOC pin 13 Initialization
	// Stepper GPIO pin Initializaion 
    // No pull-up Pull-down , Push-Pull, Fast	
	Stepper_init(GPIOB, 10, GPIOB, 4 , GPIOB,5, GPIOB,3); 
	Stepper_setSpeed(rpm,mode);					// set stepper motor speed
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

> ![image-20221102212038935](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20221102212038935.png)

Demo Video Link : https://youtu.be/L4a_5KlcQZk



### Analysis

 In this experiment, an experiment was conducted to control the stepper motor. The four coils of the stepper motor were controlled according to the finite state with four pins outputs. The rotation direction and speed of the motor could be controlled through the code, and it could be made into a pause state through the EXTI interrupt. In addition, I learned the difference between Full stepping and Half stepping.



## Reference

Given reference

https://ykkim.gitbook.io/ec/course/lab/lab-stepper-motor

## Troubleshooting

**Delay mode issue**

> ​	In the delay_ms function, an integer type must be input, but a real number less than 1 was input, causing a problem. To avoid this, there is a method of allowing a function input to be received in a real number type or creating a delay_us. 
>
>  In the case of the first method, a type problem may occur in ecSysTick.h, so it was solved using the second method. If the second method is used, it can have a value of 1 or more since the denominator is smaller than the molecule at 
>
> (60000*1000)/(step_per_rev *whatSpeed).

