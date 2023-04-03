1������˵��
    1��LP RUNģʽ�Ľ�����˳���


2��ʹ�û���

    �������������KEIL MDK-ARM V5.25

    Ӳ��������
        1������������N32G43XRL-STB V1.0����
        2��MCU��N32G435RBL7


3��ʹ��˵��
    
    ϵͳ���ã�
        1��ʱ��Դ��HSE+PLL/MSI
        2��ʱ��Ƶ�ʣ�48M/4M

    ʹ�÷�����
        ��KEIL�±������¼�������壬���ӵ������ϵ���һ�ᣬ�������Ա�С���ֹ�һ������ֱ��
              ѭ��������
            


4��ע������
    ������LP RUNģʽʱ��ϵͳʱ���л�����MSI�����˳�ʱ����Ҫ�л��û�Ĭ��ϵͳʱ��


1. Function description
    1. Enter and exit LP RUN mode.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1. based on the evaluation board N32G43XRL-STB V1.0 development
	2. MCU: N32G435RBL7

3. Instructions for use    
    System configuration;
	1. Clock source: HSE+PLL/MSI
	2, clock frequency: 48M/4M
    Instructions:
	After compiling under KEIL, it was burned to the evaluation board and connected to the ammeter in series. After powering on for a while, the current decreased significantly. After a while the current increases again.
	The cycle repeats.
            
4. Matters needing attention
	When enter LP RUN mode, the system clock is switched to MSI. When exit, you need to switch back to the default system clock

