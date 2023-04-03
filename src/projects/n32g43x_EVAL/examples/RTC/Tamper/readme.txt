1������˵��
    1��ͨ�����PC13 IO �ߵ�ƽ���������жϡ�

2��ʹ�û���

    �������������KEIL MDK-ARM V5.25
    Ӳ��������
        1������������N32G43XRL-STB V1.0����
        2��MCU��N32G435RBL7

3��ʹ��˵��
    
    ϵͳ���ã�
        1��ʱ��Դ��HSE/32
        2�����ּ��IO��PC13
        3���������ã�
                            - ����ΪUSART1��TX��PA9  RX��PA10��:
                            - ����λ��8
                            - ֹͣλ��1
                            - ��żУ�飺��
                            - �����ʣ� 115200 
    ʹ�÷�����
        �������¼�������壬�ϵ����Ϊ��PC13����ߵ�ƽ���������RTC Tamper Interrupt��˵�����ּ�ⷢ���������ж�
                
4��ע������
    ��


1. Function description

	1. Tamper interrupt is triggered by detecting PC13 IO high level.

2. Use environment

	Software development environment: KEIL MDK-ARM V5.25
	Hardware environment:
		1. based on the evaluation board N32G43XRL-STB V1.0 development
		2. MCU��N32G435RBL7

3. Instructions for use

	System configuration:

		1. RTC Clock source: HSE/32
        2. Tamper detection IO: PC13
		3. Serial port configuration:
							- Serial port: USART1 (TX: PA9 RX: PA10) :
							- Data bit: 8
							- Stop bit: 1
							- Parity check: None
							- Baud rate: 115200

	Instructions:
		After compiling, it is burned to the evaluation board. After powering on, high level is artificially injected into PC13 and "RTC Tamper interrupt" is output through the serial port. 
        It indicates that the tamper interrupt is detected
        
4. Matters needing attention
	None