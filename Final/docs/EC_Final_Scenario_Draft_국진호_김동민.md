# LAB Final Project Scenario

Embedded Controller Lab Report

## Industrial work place safety automation

**Date:** 2022 / 12 / 08

**Author/Partner:** Dongmin Kim / Jinho Kook

**Github:** https://github.com/DongminKim21800064/EC_dmkim-064/blob/main/Final/docs/EC_Final_Scenario_Draft_%EA%B5%AD%EC%A7%84%ED%98%B8_%EA%B9%80%EB%8F%99%EB%AF%BC.md

![image](https://user-images.githubusercontent.com/91419683/206231821-090e539b-e625-4fea-9966-71463d0ef9ee.png)




## Scenario Checklist 

| Scenario |                           Contents                           | Confirmation |
| :------: | :----------------------------------------------------------: | :----------: |
|    1     | The forklift  runs along the line designated as "Line Tracing Mode". |              |
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

![image](https://user-images.githubusercontent.com/91419683/206232289-7500d66a-7447-4a0b-8edc-052a28fca3ab.png)


**1.2 Manual Mode (Push the 'E' on the PC)**

**Manual Mode(Push the E)**

- It moves according to the value entered by the PC.

**Inputs**

- Move Fork Lift : W, A, S, D

- Lift Up / Down : U, I

**Outputs**

- If the forklift is reversing or Lift Up and Down, the buzzer on.



#### 2. Cooler Fan & Caution Alarm

![image](https://user-images.githubusercontent.com/91419683/206232445-1f2994ea-1080-49b8-a85c-7158ca23e9a8.png)




## Flow Chart

### Total Flow chart

![image](https://user-images.githubusercontent.com/91419683/206232533-eeb52a16-c2b5-469d-b677-5f9f83914df6.png)



### Cooler & Alarm 

![image](https://user-images.githubusercontent.com/91419683/206232619-262e7b8b-2ac8-4405-b76d-85137ba257b9.png)



### Fork Lift

![image](https://user-images.githubusercontent.com/91419683/206232677-60f9a076-fd49-4fe9-be61-e5d581351e60.png)
