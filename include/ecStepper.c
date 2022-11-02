/**
******************************************************************************
* @author							DongMin Kim  
* @Modified         : 11-02-2022 by DongMin Kim   	
* @brief	Embedded Controller:  Stepper Motor 
*					 
******************************************************************************
*/

#include "stm32f4xx.h"
#include "ecStepper.h"

//State number 
#define S0 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define S7 7


// Stepper Motor function
uint32_t direction = 1; 
uint32_t step_delay = 100 ; 
uint32_t step_per_rev = 32*64;
	 

// Stepper Motor variable
volatile Stepper_t myStepper; 


//FULL stepping sequence  - FSM
typedef struct {
	uint8_t out;
  uint32_t next[2];
} State_full_t;

State_full_t FSM_full[4] = {  
 {0xC,{S3,S1}},
 {0x6,{S0,S2}},
 {0x3,{S1,S3}},
 {0x9,{S2,S0}},
	
};

//HALF stepping sequence
typedef struct {
	uint8_t out;
  uint32_t next[2];
} State_half_t;

State_half_t FSM_half[8] = { 
 {0x8,{S7,S1}},
 {0xC,{S0,S2}},
 {0x4,{S1,S3}},
 {0x6,{S2,S4}},
 {0x2,{S3,S5}},
 {0x3,{S4,S6}},
 {0x1,{S5,S7}},
 {0x9,{S6,S0}},
};



void Stepper_init(GPIO_TypeDef* port1, int pin1, GPIO_TypeDef* port2, int pin2, GPIO_TypeDef* port3, int pin3, GPIO_TypeDef* port4, int pin4){
	 
//  GPIO Digital Out Initiation
	 myStepper.port1 = port1;
   myStepper.pin1  = pin1;

	 myStepper.port2 = port2;
   myStepper.pin2  = pin2;
		
	 myStepper.port3 = port3;
   myStepper.pin3  = pin3;
	
	 myStepper.port4 = port4;
   myStepper.pin4  = pin4;
	
	
//  GPIO Digital Out Initiation
		// No pull-up Pull-down , Push-Pull, Fast	
		// Port1,Pin1 ~ Port4,Pin4
		GPIO_init(port1, pin1, OUTPUT);
		GPIO_init(port2, pin2, OUTPUT);
		GPIO_init(port3, pin3, OUTPUT);
		GPIO_init(port4, pin4, OUTPUT);
		GPIO_output(port1, pin1, PUSH_PULL, NONE, FAST_SPEED);
		GPIO_output(port2, pin2, PUSH_PULL, NONE, FAST_SPEED);
		GPIO_output(port3, pin3, PUSH_PULL, NONE, FAST_SPEED);
		GPIO_output(port4, pin4, PUSH_PULL, NONE, FAST_SPEED);
}

void Stepper_pinOut (uint32_t state, int mode){
	
	   if (mode == FULL){         // FULL mode
			GPIO_write(myStepper.port1, myStepper.pin1,(FSM_full[state].out>>3)&1);
			GPIO_write(myStepper.port2, myStepper.pin2,(FSM_full[state].out>>2)&1);
			GPIO_write(myStepper.port3, myStepper.pin3,(FSM_full[state].out>>1)&1);
			GPIO_write(myStepper.port4, myStepper.pin4,(FSM_full[state].out)&1);
			}	 
		 else if (mode == HALF){    // HALF mode
			GPIO_write(myStepper.port1, myStepper.pin1,(FSM_half[state].out>>3)&1);
			GPIO_write(myStepper.port2, myStepper.pin2,(FSM_half[state].out>>2)&1);
			GPIO_write(myStepper.port3, myStepper.pin3,(FSM_half[state].out>>1)&1);
			GPIO_write(myStepper.port4, myStepper.pin4,(FSM_half[state].out)&1);
			}
}


void Stepper_setSpeed (long whatSpeed, int mode){      // rpm
	if(mode == FULL)
		step_delay = (uint32_t) (60000*1000)/(step_per_rev*whatSpeed);// Convert rpm to milli sec
	else if(mode == HALF)
		step_delay = (uint32_t) (60000*1000)/(step_per_rev*whatSpeed*2);
	// 1rpm = 1rev / min
		// 1rev = 2048 steps ; 2rev = 4096 steps ....
		// 1 min = 60 sec = 60000 milli sec
		
}


void Stepper_step(int steps, int direction, int mode){
	 uint32_t state = 0;
   myStepper._step_num = steps;

	 for(; myStepper._step_num > 0; myStepper._step_num--){ // run for step size
				delay_us(step_delay);                             // delay (step_delay); 
					 
		    if (mode == FULL) 		 												
						state = FSM_full[state].next[direction];   // state = next state
				else if (mode == HALF) 
						state = FSM_half[state].next[direction];   // state = next state

				Stepper_pinOut(state, mode);
   }
}


void Stepper_stop (void){ 
     
    	myStepper._step_num = 0;    
			// All pins(Port1~4, Pin1~4) set as DigitalOut '0'
			GPIO_write(myStepper.port1, myStepper.pin1,0);
			GPIO_write(myStepper.port2, myStepper.pin2,0);
			GPIO_write(myStepper.port3, myStepper.pin3,0);
			GPIO_write(myStepper.port4, myStepper.pin4,0);
}

