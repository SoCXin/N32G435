1������˵��
    1��IWDG��λ���ܡ�


2��ʹ�û���

    �������������KEIL MDK-ARM V5.25

    Ӳ��������
        1������������N32G43XR-STB V1.0����
        2��MCU��N32G435RBL7


3��ʹ��˵��
    
    ϵͳ���ã�
        1��IWDGʱ��Դ��LSI/32
        2����ʱʱ��ֵ��250ms
        3��ָʾ�ƣ�LED1(PA8) LED2(PB4)
        4���������ã�
                   - ����ΪUSART1��TX��PA9  RX��PA10��:
                   - ����λ��8
                   - ֹͣλ��1
                   - ��żУ�飺��
                   - �����ʣ� 115200            



    ʹ�÷�����
           1����KEIL�±������¼�������壬�ϵ��ָʾ��LED2��ͣ����˸��˵��IWDG����ι���������������С�
           2����Delay(249)���������ĳ�Delay(252)����ʱ250ms���ϣ���MCU���ڲ��ϸ�λ״̬�����ڲ��ϴ�ӡ��
           ��Reset by IWDG����


4��ע������


1. Function description
    1. IWDG reset function.
	
2. Use environment
    Software development environment: KEIL MDK-ARM V5.25.0.0
	
    Hardware environment: 
		1.Developed based on the evaluation board N32G43XR-STB
		2.MCU��N32G435RBL7
	
3. Instructions for use
    System Configuration;
        1. IWDG clock source: LSI/32

		2. Timeout value: 250ms

		3. Indicator light: LED1(PA8) LED2(PB4)

		4. Serial port configuration:

			- Serial port: USART1 (TX: PA9 RX: PA10) :

			- Data bit: 8

			- Stop bit: 1

			- Parity check: None

			- Baud rate: 115200

    Instructions:
        1. After compiling in KEIL, it was burned to the evaluation board. After powering on,the indicator controled by PB5 pin kept flashing. The IWDG feeds the dog properly and the code runs properly.
		2. When the Delay(249) function parameter is changed to more than 250, the entire system will always be reset. The serial port continuously prints reset by IWDG.
		
4. Matters needing attention
    None.