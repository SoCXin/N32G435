1������˵��

	1��������չʾ��ȡ�˿ڸߵ͵�ƽ������ LED��D1��D2��D3����˸
	2������ IO �ڵ�ƽ��ת

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺NS3602_LQFP100_V0.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	1��SystemClock��108MHz
	2��GPIO��PA8��PA9��PA10 ���� LED(D1��D2��D3) ��˸


	/* ����Demo�Ĳ��Բ�������� */
	1.��������س���λ���У�
	2.�ϵ�� D1 ������D2��D3 ��˸��

4��ע������


1. Function description

	1. This example shows the read port high and low levels, and controls the LEDs (D1, D2, D3) to flash
	2. Control IO port level flip


2. Use environment

	/* Hardware environment: the development hardware platform corresponding to the project */
	Development board: NS3602_LQFP100_V0.1

3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
	SystemClock: 108MHz
	GPIO: PA8, PA9, PA10 control LED (D1, D2, D3) to blink


	/* Describe the test steps and phenomena of the Demo */
	1. After compiling, download the program to reset and run;
	2. After power-on, D1 is always on, and D2 and D3 are flashing;


4. Matters needing attention
	None.