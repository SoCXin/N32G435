1、功能说明
    1、WWDG复位功能。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
        1、基于评估板N32G43XR-STB V1.0开发
        2、MCU：N32G435RBL7


3、使用说明
    
    系统配置；
        1、WWDG时钟源：PCLK1
        2、窗口值：57.06ms < n <77.69ms
        3、指示灯：PA8(LED1)   PB5(LED3)
             



    使用方法：
        1、在KEIL下编译后烧录到评估板，上电后，指示灯LED3不停的闪烁。说明窗口值刷新正常，代码正常运行。
        2、当把Delay(60)函数参数改成80以上，整个系统将一直处于复位状态。LED1、LED3常亮。


4、注意事项
     无

1. Function description
    1. WWDG reset function.
	
2. Use environment
    Software development environment: KEIL MDK-ARM V5.25.
	
    Hardware environment: 
		1.Developed based on the evaluation board N32G43XR-STB
		2.N32G435RBL7
	
3. Instructions for use
    System Configuration;
        1. WWDG clock source: PCLK1

		2. window value: 57.06ms < n <77.69ms

		3. Indicator light: PA8(LED1)   PB5(LED3)


    Instructions:
        1. After compiling under KEIL, it is burned to the evaluation board. After powering on, the indicator light LED3 keeps flashing. The window value is refreshed properly, and the code is running properly.
		2. When the parameter of Delay(60) function  is changed to more than 50, the whole system will always be reset. LED1,LED3 are always on.
		
4. Matters needing attention
    None.