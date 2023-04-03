1、功能说明
    1、LP SLEEP模式的进入和退出。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
        1、基于评估板N32G43XRL-STB V1.0开发
        2、MCU：N32G435RBL7


3、使用说明
    
    系统配置；
        1、时钟源：HSE+PLL/MSI
        2、时钟频率：48M/4M

    使用方法：
        在KEIL下编译后烧录到评估板，串接电流表，上电后过一会，电流明显变小。按下唤醒按键PA0，电流变大。
              在过一会，电流又变小。
            


4、注意事项
    LP RUN唤醒后会先进入LP RUN，再由LP RUN退出到RUN模式



1. Function description
    1. Enter and exit LP SLEEP mode.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1. Development based on evaluation board N32G43XRL-STB V1.0
	2. MCU: N32G435RBL7

3. Instructions for use   
    System configuration;
	1. Clock source: HSE+PLL/MSI
	2, clock frequency: 48M/4M
    Instructions:
	After compiling under KEIL, it was burned to the evaluation board and connected to the ammeter in series. After powering on for a while, the current decreased significantly. Press the wake button PA0 and the current increases.
	After a while, the current decreases again.
            
4. Matters needing attention
    After waking up from LP RUN, the system enters LP RUN and exits the RUN mode from LP RUN

