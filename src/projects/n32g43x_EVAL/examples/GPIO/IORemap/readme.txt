1������˵��

	1��������չʾ��ȡ�˿ڸߵ͵�ƽ������ LED��D2��D3����˸
	2������ IO �ڵ�ƽ��ת


2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺NS3602_LQFP100_V0.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	1��SystemClock��108MHz
	2��GPIO��PA8 ѡ����Ϊ��ȡ��ƽ�˿ڣ�PA9��PA10 ���� LED(D2��D3) ��˸


	/* ����Demo�Ĳ��Բ�������� */
	1.��������س���λ���У�
	2.��� PA8 �ڵ�ƽ������ǵ͵�ƽ LED��D2���������� PA8 ���� 3.3V��LED��D3�� ������


4��ע������
	����⵽ PA8 ��Ϊ�͵�ƽʱ���ر� JTAG��PA8 ��Ϊ�ߵ�ƽʱ������ JTAG
	
	
	
	
1. Function description

	1. This example shows the high and low levels of the read port and controls the flashing of the LEDs (D2, D3)
	
	2. Control IO port level flip


2. Use environment

	/* Hardware environment: the development hardware platform corresponding to the project */
	Development board: NS3602_LQFP100_V0.1

3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
	SystemClock: 108MHz
	GPIO: PA8 is selected as the read level port, PA9, PA10 control LED (D2, D3) to flash


	/* Describe the test steps and phenomena of the Demo */
	1. After compiling, download the program to reset and run;
	2. Check the level of the PA8 port, if it is a low level, the LED (D2) is always on, connect PA8 to 3.3V, and the LED (D3) is always on;


4. Matters needing attention
	When it is detected that the PA8 port is at a low level, close JTAG, and when the PA8 port is at a high level, open the JTAG.