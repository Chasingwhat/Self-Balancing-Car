/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��isr.c
 * ����         ���жϴ�������
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/
#include "common.h"
#include "include.h"
#include "isr.h"
#include "car.h"
#include "dma.h"
u16  Time_PartCnt;
extern u16 g_nSpeedControlPeriod;
extern u16 g_SpeedControlCount;
extern float   g_fAngleControlOut;
extern s16 g_nRightMotorPulse;
extern float g_fSpeedControlOutNew;
extern float g_fSpeedControlOut;

extern s16 g_RightMotorPulseSigma;
extern s16 g_LeftMotorPulseSigma;
extern float CAR_SPEED_SET;
extern u16 g_nDirectionControlPeriod;
extern u16 g_nDirectionControlCount;
u16 count=0;
u16 count1=0;
/***************����ͷ����*************/
extern u32 rowCnt ;   //�м���
extern u8 Buffer1[ROW][COL];
u8 SampleFlag = 0;
u8 VSYN_Flag=0;
u8 VSYN1_FLAG;
u8 Run_Flag=0;
float flag_count=0;
extern u16 speed1;
void delays(u16 t)
{
     while(t--);
}
void PIT0_IRQHandler(void)//ÿ��5ms��ִ��һ�� MOTOROUT    
{
      Time_PartCnt++;
      
      g_nSpeedControlPeriod++;
      SpeedControlOutput();
      
      g_nDirectionControlPeriod++;
      DirectionControlOutput();
      count1++;
      count++;
      if(count1==2500)
      {  
         Run_Flag=1;
         
      }
      if(Run_Flag==1)
      {
         flag_count++;
         CAR_SPEED_SET=(flag_count/1000.0)*speed1;
         if(CAR_SPEED_SET>=speed1)
         {
            Run_Flag=0;
            CAR_SPEED_SET=speed1;
            flag_count=0;
         }
      }
      if(count1>2600)
      {
        count1=2700;
      }
      if(count>8000)
      {
        count=8000;
      }
     if((PIT_TFLG(PIT0)&PIT_TFLG_TIF_MASK)!=0)
       {  
       
        if(Time_PartCnt>=Time_PartCntMax)//5ms��ʱ���ȡ�ٶ�����  Ƭ��5
        {
            Time_PartCnt=0;
            GetMotorspeed();
            
        }else  if(Time_PartCnt==1)//Ƭ��1  
              {
            
           
              }else if(Time_PartCnt==2)//�Ƕȿ���
                     {
                       Angle_Control();
                       
                     }else if(Time_PartCnt==3)//�ٶȿ���
                           {
                              g_SpeedControlCount++;
                              if(g_SpeedControlCount>=SPEED_CONTROL_COUNT)
                               {
                                 SpeedControl();
                                 g_SpeedControlCount=0;
                                 g_nSpeedControlPeriod=0;
                               }
                           }else if(Time_PartCnt==4)//�������
                                    {
                                      g_nDirectionControlCount++;
                                      if(g_nDirectionControlCount >= DIRECTION_CONTROL_COUNT)
    	                                  { 
                                              DirectionControl();
                                              g_nDirectionControlCount = 0; 
                                              g_nDirectionControlPeriod = 0;  
                                          }
         
                                    }     
        MotorOutput();
	PIT_TFLG(PIT0)|=PIT_TFLG_TIF_MASK;       //���־
       }
      PIT_TCTRL(PIT0)|=PIT_TCTRL_TIE_MASK;//ʹ�ܶ�ʱ���ж�
}
void PORTB_IRQHandler(void)
{
  
}
/***********************�г��ж�*****************/
void PORTA_IRQHandler(void)
{
      //---VSYN���жϴ���
    if(PORTA_ISFR & (1 << 24))         //PTA24�����ж�  ���ж�
    { 
        PORTA_ISFR  |= (1 << 24);       //д1���жϱ�־λ
        rowCnt = 0;
        SampleFlag = 1; 
    }
}
void PORTD_IRQHandler(void)
{
   //---HREF���жϴ���
    if( PORTD_ISFR & (1 << 13))        
    {
        PORTD_ISFR  |= (1 << 13);  
        
        if ( SampleFlag == 0 )         //����һ��ʱ����   ��ʵ����Ƕ�����һ���������ĳ�
        { 
          return;
        }  
        DMA_PORTx2BUFF_Init (DMA_CH4, (void *)&PTB_BYTE0_IN, Buffer1[rowCnt], PTD12, DMA_BYTE1, COL, DMA_rising_keepon);
        DMA_EN(DMA_CH4);//����ʹ��DMA��Ӳ������ 
        //һ�����ݰ������ݺ�������:���ɼ�������ʱ(DMA�жϷ�����ֹDMA),��ʵһ�в�û�н���,��ʱ����ĵ㶼�����˵��������������ʱ�������ж�Ȼ��ʹ��DMA������һ�βɼ�
        rowCnt++;
        if(rowCnt == ROW)
        {
          rowCnt = 0;
          DMA_DIS(DMA_CH4);
          VSYN_Flag = 1;//������ݵĲɼ�
          disable_irq(PORTD + 87);
         
        }
       
    }
}
void DMA_CH0_Handler(void)
{
}