# LAB Final Project Scenario

Embedded Controller Lab Report

## Industrial work place safety automation

**Date:** 2022 / 12 / 08

**Author/Partner:** Dongmin Kim / Jinho Kook



![image-20221208010650410](C:\Users\82106\AppData\Roaming\Typora\typora-user-images\image-20221208010650410.png)



## Scenario Checklist 

| Scenario |                           Contents                           | Confirmation |
| :------: | :----------------------------------------------------------: | :----------: |
|    1     | The forklift  runs along the line designated as "Line Tracking Mode". |              |
|    2     |   The forklift  senses the worker while driving and stops.   |              |
|    3     |   The alarm goes  on so that workers can alert the danger.   |              |
|    4     | The worker loads the stopped forklift. The pressure sensor on the lift detects this and  raises the lift. |              |
|    5     | Supervisor  changes to 'manual mode' and moves forklift to specific location. |              |
|    6     | A forklift backs  up to move to a specific location. The buzzer on the forklift signals danger. |              |
|    7     |      The supervisor  unloads at a particular location.       |              |
|    8     | Supervisor  matches the forklift on the line and changes it to "Line Tracking  Mode". |              |
|    9     | The temperature  inside the factory rises above 33 degrees, and the cooler fan operates. |              |
|    10    | With the cooler  running, the forklift approaches the worker, and the buzzer operates. |              |
|    11    | The worker  becomes safe, and the temperature inside the factory decreases, making the  factory in normal mode. |              |



## State Table

#### 1. Fork Lift

**1.1 Auto Mode (Push the 'Q' on the PC)**

![image-20221208005031504](C:\Users\82106\AppData\Roaming\Typora\typora-user-images\image-20221208005031504.png)

**1.2 Manual Mode (Push the 'E' on the PC)**

**Manual Mode(Push the E)**

- It moves according to the value entered by the PC.

**Inputs**

- Move Fork Lift : W, A, S, D

- Lift Up / Down : U, I

**Outputs**

- If the forklift is reversing or Lift Up and Down, the buzzer on.



#### 2. Cooler Fan & Caution Alarm

![image-20221208005319283](C:\Users\82106\AppData\Roaming\Typora\typora-user-images\image-20221208005319283.png)



## Flow Chart

### Total Flow chart

![image-20221208010947029](C:\Users\82106\AppData\Roaming\Typora\typora-user-images\image-20221208010947029.png)



### Cooler & Alarm 

![image-20221208010838681](C:\Users\82106\AppData\Roaming\Typora\typora-user-images\image-20221208010838681.png)



### Fork Lift

![image-20221208010819590](C:\Users\82106\AppData\Roaming\Typora\typora-user-images\image-20221208010819590.png)