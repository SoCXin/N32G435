1������˵��
    1��LP SLEEPģʽ�Ľ�����˳���


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
        ��KEIL�±������¼�������壬���ӵ������ϵ���һ�ᣬ�������Ա�С�����»��Ѱ���PA0���������
              �ڹ�һ�ᣬ�����ֱ�С��
            


4��ע������
    LP RUN���Ѻ���Ƚ���LP RUN������LP RUN�˳���RUNģʽ



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

