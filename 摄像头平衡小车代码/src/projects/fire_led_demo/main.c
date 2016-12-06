//sysinit()��printf()��UART���ض���  ����printf����ֱ��������ⳤ�ȵ�ʮ���Ƶ���ֵ
//�����BUS__CLK��Ƶ�ʵ�ʱ��ͼ���ϵ����ȫ����ʧ��---k60_fire.h���޸�ʱ��Ƶ��
//    PTB0-PTB7   Y0-Y7
//    PTD12       PCLK
//    PTA24       VSYN
//    PTD13       HREF
//    PTE10       SCL
//    PTE12       SDA
//    PTD15       FODD
#include "common.h"
#include "include.h"
#include "car.h"
#include "dma.h"
extern s16  Gyro_Angle0;//������0ƫֵ
extern s16  J_Angle0;//���ٶ�0ƫֵ
extern s16  ANGLE_SET;//��ʼ�趨�ĽǶ�ֵ
extern float g_fAngleControlOut;//�Ƕ����ֱ���������Ƶ��
extern float KP_Angle;
extern float KD_Angle;//����
extern u16 count;
extern float g_fSpeedControlOutNew;
extern float g_fLeftMotorOut,g_fRightMotorOut; 
extern float g_fSpeedControlOut;//�ٶȵ����
extern float SPEED_CONTROL_P;//
extern float SPEED_CONTROL_I;//�ٶȿ���I���� 
extern float SPEED_CONTROL_D;

extern s16   g_fLeftDirectionSigma;
extern s16   g_fRightDirectionSigma;
/***********����ͷ����**************/
extern u8  VSYN_Flag;//����ɱ�־
extern u8  VSYN1_FLAG;//��ֵ�������־λ
u8 Buffer1[ROW][COL]={0};//ͼ��洢
extern u8 SampleFlag;
volatile u32 rowCnt=0;//�м���
u16  speed1=0;
extern u16 count;
extern u16 middle_num;
extern u16 row_qian;
extern u16 turn_left;
extern u16 turn_right;
extern float DIR_CONTROL_P;
extern float DIR_CONTROL_D;
extern u8    shiziflag;
extern u16   shizinum;
float          PreDirection=0;
float          PreDirection1=0;
/*******************Ѱ·��******************/
/************����*************/
void EXTI_Init();//10ns;
void set_speed(void);
void  main(void)
{  
    DisableInterrupts;//���жϳ�ʼ��
    FTM_PWM_init(FTM0, CH4, 20000,0);//���1��  PTD4  
    FTM_PWM_init(FTM0, CH5, 20000,0);//���1��  PTD5
    FTM_PWM_init(FTM0, CH6, 20000,0);//���2��  PTD6
    FTM_PWM_init(FTM0, CH7, 20000,0);//���2��  PTD7  20khz

    gpio_init(PORTA,14,GPO,1);//����״̬��
    gpio_init(PORTA,16,GPO,1);
    gpio_init(PORTA,15,GPO,1);
    gpio_init(PORTA,17,GPO,1);
    gpio_init(PORTC,0,GPO,1);
    gpio_init(PORTC,1,GPO,1);//�ٶȿ�ǰհ��Զһ��  �ٶ���ǰհ����һ��
    
    //�ٶ����ó�ʼ��
    gpio_init(PORTC,13,GPI_DOWN,0);
    gpio_init(PORTC,12,GPI_DOWN,0);
    gpio_init(PORTC,11,GPI_DOWN,0);
    gpio_init(PORTC,10,GPI_DOWN,0);
    gpio_init(PORTC,9,GPI_DOWN,0);
    gpio_init(PORTC,8,GPI_DOWN,0);
    gpio_init(PORTC,7,GPI_DOWN,0);
    gpio_init(PORTC,6,GPI_DOWN,0);
    /**********������ʼ��**************/
    KP_Angle=11.5;//11.89��Ҫ����
    KD_Angle=1.25;//1.5  ֱ������С��ͬʱһ��Ҫ���ڼ�С�ٶȵı�����
    SPEED_CONTROL_P=1.5;//4.2����ԽС����Խ�ȵ����ٶ�̫��Խ���������׶���
    SPEED_CONTROL_I=0.95;//0.25Խ����С����Խ����
    ANGLE_SET=0;//��ʼֵһ���趨Ϊ0
    uart_init(UART1,9600);
    EXTI_Init();
    pit_init_ms(PIT0,1);//1ms�Ķ�ʱ����
    set_irq_priority(PIT0+68,14);//PIT�ж�
    adc_init(ADC1,SE4a);//PE0 4a  Gyro���ٶ�  
    adc_init(ADC1,SE5a);//PE1 5a  J�Ƕ�       
    adc_init(ADC1,SE6a);//PE2   ����
    adc_init(ADC1,SE7a);//PE3   ����
    /***�����ٶ�*********/
   
   /*******************��������***********************/
    FTM_QUAD_Init1(FTM1, CH0);//PA8   ��
    FTM_QUAD_Init1(FTM2, CH0);//PA10  ��
    
    Gyro_Angle0=ad_ave(ADC1,SE4a,ADC_12bit,200); //���0ƫֵ ���ٶ�0ƫת
    J_Angle0=ad_ave(ADC1,SE5a,ADC_12bit,200); //���0ƫֵ    ֱ�Ӷ�ȡ�Ƕ�
    shizinum=0;
    set_speed();
    VSYN_Flag=0;
    rowCnt=0;
    count=0;
    EnableInterrupts;//���жϽ��빤��
    while(1)
    { 
        if(VSYN_Flag==1)//һ��16.64ms
         {   
            gpio_set(PORTA,14,0);//����״̬��
            VSYN1_FLAG = 0;
            VSYN_Flag=0;
            ImageProc();
            gpio_set(PORTA,16,0);
            rowCnt=0;
            SampleFlag=0;
            enable_irq(PORTA + 87);
            enable_irq(PORTD + 87);
            
         }
    }
}

void EXTI_Init()
{
    //----��ʼ���ⲿ�ж�---//
    exti_init(PORTD, 13, rising_down);      //HREF----PORTD13 �ж˿��ⲿ�жϳ�ʼ�� �������ش����жϣ��ڲ�����
    exti_init(PORTA, 24, rising_down);      //VSYN----PORTA24 ���˿��ⲿ�жϳ�ʼ�� �������ش����жϣ��ڲ�����
    set_irq_priority(PORTD+87,10);//�ж�����,���ȼ����ж�
    set_irq_priority(PORTA+87,2);//���ж�
}
void set_speed(void)
{
  
     if(gpio_get(PORTC,9)==1)//�ٶ�5��   ֱ����Ӳ���µ�
    {
         row_qian=65;//250һ��76��ǰհ   260,270�����ٶ����ǰհ
         speed1=320;
         DIR_CONTROL_D=1.98;
         DIR_CONTROL_P=1.53;
         PreDirection=DIR_CONTROL_P;
         PreDirection1=4.5;
         KP_Angle=11.5;//11.89��Ҫ����
         KD_Angle=1.43;//1.5  ֱ������С��ͬʱһ��Ҫ���ڼ�С�ٶȵı�����
    } 
    
    
    
    if(gpio_get(PORTC,13)==1)//�ٶ�1��
    {
         row_qian=65;//250һ��76��ǰհ   260,270�����ٶ����ǰհ
         speed1=250;
         DIR_CONTROL_D=1.84;
         DIR_CONTROL_P=1.4;
         PreDirection=DIR_CONTROL_P;
         PreDirection1=1.5;
    }
    if(gpio_get(PORTC,12)==1)//�ٶ�2��
    {
         row_qian=65;//250һ��76��ǰհ   260,270�����ٶ����ǰհ
         speed1=280;
         DIR_CONTROL_D=1.84;
         DIR_CONTROL_P=1.4;
         PreDirection=DIR_CONTROL_P;
         PreDirection1=1.8;
    }
    if(gpio_get(PORTC,11)==1)//�ٶ�3��
    {
         row_qian=60;//
         speed1=300;
         DIR_CONTROL_D=1.96;
         DIR_CONTROL_P=1.85;
         PreDirection=DIR_CONTROL_P;
         PreDirection1=1.8;
       
    }
    if(gpio_get(PORTC,10)==1)//�ٶ�4��
    {
         row_qian=60;//250һ��76��ǰհ   260,270�����ٶ����ǰհ
         speed1=320;
         DIR_CONTROL_D=1.98;
         DIR_CONTROL_P=1.53;
         PreDirection=DIR_CONTROL_P;
         PreDirection1=4.5;
    }    
    if(gpio_get(PORTC,8)==1)//������
    {
       shiziflag=1;
    } 
    if(gpio_get(PORTC,7)==1)//������ת
    {
       shizinum=40;
    }
    if(gpio_get(PORTC,6)==1)//������ת
    {
       
       shizinum=220;
    }
     if((gpio_get(PORTC,12)==1)&&(gpio_get(PORTC,13)==1))//1.2
    {    
         row_qian=55;//250һ��76��ǰհ   260,270�����ٶ����ǰհ
         speed1=330;
         DIR_CONTROL_D=1.98;
         DIR_CONTROL_P=1.53;
         PreDirection=DIR_CONTROL_P;
         PreDirection1=4.0;
    }
     if((gpio_get(PORTC,11)==1)&&(gpio_get(PORTC,12)==1))//2.3
    {    
         row_qian=50;//250һ��76��ǰհ   260,270�����ٶ����ǰհ
         speed1=340;
         DIR_CONTROL_D=1.98;
         DIR_CONTROL_P=1.53;
         PreDirection=DIR_CONTROL_P;
         PreDirection1=4.0;
    }
     if((gpio_get(PORTC,11)==1)&&(gpio_get(PORTC,10)==1))//3.4
    {    
         row_qian=45;//250һ��76��ǰհ   260,270�����ٶ����ǰհ
         speed1=360;
         DIR_CONTROL_D=2.18;
         DIR_CONTROL_P=1.63;
         PreDirection=DIR_CONTROL_P;
         PreDirection1=4.0;
    }
     if((gpio_get(PORTC,10)==1)&&(gpio_get(PORTC,9)==1))//4.5
    {    
         row_qian=40;//250һ��76��ǰհ   260,270�����ٶ����ǰհ
         speed1=380;
         DIR_CONTROL_D=2.38;
         DIR_CONTROL_P=1.63;
         PreDirection=DIR_CONTROL_P;
         PreDirection1=4.0;
    }
}

