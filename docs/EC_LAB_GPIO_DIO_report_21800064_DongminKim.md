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

``` c

```

## Discussion

1. Find out a typical solution for software debouncing and hardware debouncing. 
2. What method of debouncing did this NUCLEO board used for the push-button(B1)?
3. 

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

image



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

