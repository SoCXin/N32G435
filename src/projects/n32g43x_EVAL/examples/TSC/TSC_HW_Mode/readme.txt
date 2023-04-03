1、功能说明
    TSC低功耗模式唤醒演示

2、使用环境
    软件开发环境：KEIL MDK-ARM V5.26
    硬件环境：基于测试板N32L43XM-TB-TSC开发

3、使用说明
    
    系统配置；
        1、时钟源：HSE+PLL
        2、系统时钟：16MHz
        3、TSC端口： 
            PA2:CH1     PA3:CH4     PA4:CH5     PA5:CH6     
            PB0:CH7     PB1:CH8     PB2:CH9     PB11:CH10   
            PB12:CH11   PB14:CH12   PC6:CH13    PC7:CH14    
            PB15:CH15   PB13:CH16   PC8:CH17    PD10:CH19
            PA7:CH20    PC4:CH21    PC5:CH22    PA6:CH23
        4、LED控制端口：
            PC0:D3      PC1:D2      PC2:D1
        5、UART4端口：
            TX:PC10     RX:PC11

    使用方法：
        1、在KEIL下编译后烧录到测试板，通过J36连接PC,通电，D1、D2、D3点亮
        2、约15后LED全部熄灭，MCU进入低功耗模式，可通过任意触摸按键唤醒
        2、在PC端打开串口调试软件，可看到相应信息
        
4、注意事项
    无