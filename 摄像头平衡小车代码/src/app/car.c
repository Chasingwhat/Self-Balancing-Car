#include "car.h"
#include  "math.h"
/**************ֱ����ز���****************/
s16  Gyro_Angle0=0;//������0ƫֵ
s16  J_Angle0=0;//���ٶ�0ƫֵ�ڳ�ʼ��ʱ��ⶨ
float  KP_Angle=0;//�Ƕȿ���P����
float  KD_Angle=0;//�Ƕȿ���D����
s16  ANGLE_SET=0;//��ʼ�趨�ĽǶ�ֵ
s16  J_Angle_Num;
s16  Gyro_Angle_Num;
float   g_fAngleControlOut;//ֱ�����
/**************ֱ����ز���***************/

/************�ٶ���ز���***************/
float CAR_SPEED_SET=0;//�ٶ��趨�ĳ�ֵ
s16 g_fCarSpeed;//�����ٶ�
s16 g_fSpeedControlIntegral=0;//���ֲ���
float g_fSpeedControlOutOld=0;//��һ�ε��ٶ�
float g_fSpeedControlOutNew=0;//��ǰ���ٶ�

s16 g_nLeftMotorPulse=0;
s16 g_nRightMotorPulse=0;
s16 g_LeftMotorPulseSigma=0;//���ֵ��������
s16 g_RightMotorPulseSigma=0;//���ֵ��������

float  g_fLeftMotorOut=0;
float  g_fRightMotorOut=0;
float g_fSpeedControlOut=0;//�ٶȵ����
float SPEED_CONTROL_P=0;//
float SPEED_CONTROL_I=0;//�ٶȿ���I���� 
float SPEED_CONTROL_D=0;
u16   g_nSpeedControlPeriod=0,g_SpeedControlCount=0;
/***********�ٶ���ز���**************/
/***********������Ʋ���*************/
float g_DirectionControlOut;//�������
float g_fDirectionControlOutNew,g_fDirectionControlOutOld;//���ڻ��巽������
u8 g_nDirectionControlCount,g_nDirectionControlPeriod;
float DIR_CONTROL_P=1.55;//�����⾶��
float DIR_CONTROL_D=1.83;//0.35�����DԽ�������ڹ�S���������������  �����ھ���
float DIR_CONTROL_I=0;   //180���ٶȶ�Ӧ  0.85  0.80
s16   g_fLeftDirectionSigma;
s16   g_fRightDirectionSigma;
extern u8 Buffer1[ROW][COL];
extern u32 rowCnt;
s32 zuoPos = 0;          //��߽�λ��[�з�����]
s32 youPos = 0;          //�ұ߽�λ��[�з�����]
u8 zuoEdgeFlag = 0;      //�ұ߽�ȷ�ϱ�־���ҵ���߽���λ
u8 time;   //��߽�ȷ�ϱ�־���ҵ���߽���λ
u8 youEdgeFlag = 0;
u8  FLAG_YOU=0;
u8  FLAG_ZUO=0;
u16  capture[10]={0};
u16  zuo=0;
u16  you=0;
u8  first_row=0;
float   flag_left=0;
float   flag_right=0;
u8   FLAG1=0;
u8   FLAG2=0;
u8   hinder_left=0;
u8   hinder_right=0;
u16   posleft=0;
u16   posright=0;
u8   hinder_left1=0;
u8   hinder_right1=0;
u8   hinder_right2=0;
u8   middle=0;
u8   flag_you=0;


u16  shizileft=0;
u16  shiziright=0;
u8   zuoflag=0;
u8   youflag=0;
u8   shiziflag=0;
u8   row_qian=0;
u16  shizinum=0;
s16   turn_left=0;
s16   turn_right=0;
extern u16 speed1;

u8  start_run=0;
u16 middle_num=0;

u8  wanflag1=0;
u8  wanflag2=0;
u16 poszuo=0;
u16 posyou=0;

int Gyro_numcha=0;
extern u16 count;
extern float  PreDirection;
extern float  PreDirection1;
float abs(float __x);
/*******��ȡ�Ƕȵ�ģ��ֵ*****/
void Get_AD_angle()
{
       u16 Gyro_Angle,J_Angle;
       Gyro_Angle=ad_ave(ADC1,SE4a,ADC_12bit,70); //50��ֵ�˲�;֮ǰ�õ���10���˲������ڸ�Ϊ��100�ε��˲�������ͷ����������ǳ���������)
       J_Angle=ad_ave(ADC1,SE5a,ADC_12bit,70); //��ֵ�˲�50;
       Gyro_Angle_Num =Gyro_Angle0 - Gyro_Angle;//�����ǽ��ٶ�
       J_Angle_Num=J_Angle0-J_Angle;//�Ƕ�
       Gyro_numcha=Gyro_Angle_Num;
}
//*************�Ƕȿ��ƺ���*******//
void Angle_Control()//�Ƕ�PD�����㷨
{
       float fValue;
       Get_AD_angle();
       fValue=(ANGLE_SET-J_Angle_Num)*KP_Angle+(Gyro_Angle_Num)*KD_Angle; //PD����        
       if(fValue>Angle_Out_Max)  fValue = Angle_Out_Max;//�����޿��Բ�Ҫ
       if(fValue<Angle_Out_Min)   fValue =Angle_Out_Min;	         
       g_fAngleControlOut=fValue;
      
   
}
/****************�ٶȿ���**********************/


void SpeedControl(void)
{
    float fDelta;
    float fP,fI,fD;
    static float Error_Error;
    g_fCarSpeed=(g_LeftMotorPulseSigma+g_RightMotorPulseSigma)/2;//�����ٶ�
    g_LeftMotorPulseSigma=g_RightMotorPulseSigma=0;
    
    fDelta = CAR_SPEED_SET - g_fCarSpeed;//���
   
    fP = fDelta * SPEED_CONTROL_P;//�������� 
    fI = fDelta * SPEED_CONTROL_I;//���ֲ���
    g_fSpeedControlIntegral += fI;//�������
    fD=( fDelta-Error_Error)* SPEED_CONTROL_D;
    fD=0;
    if(g_fSpeedControlIntegral>=100){g_fSpeedControlIntegral=100;}
    if(g_fSpeedControlIntegral<=(-100)){g_fSpeedControlIntegral=-100;}//���ֱ��ʹ���
    g_fSpeedControlOutOld = g_fSpeedControlOutNew;
    g_fSpeedControlOutNew = fP + g_fSpeedControlIntegral + fD;//���������Ŀ�ľ���Ϊ�����ƽ�����ٶ�
    if(g_fSpeedControlOutNew>CAR_SPEED_SET)
    {
       g_fSpeedControlOutNew=CAR_SPEED_SET;
    }
    Error_Error=fDelta;

}   
//��ΪMOTOROUT��5msִ��һ�� ����100ms���ٶȱ仯���ָ��20��5ms�ĵ��ڹ���
void SpeedControlOutput(void)//�ٶ�ƽ������  ���þ���ʹ�ٶ����������ӵ�������ֵ�����м�����޶������ƱȽ�ƽ�� 
{
    float fValue;
    fValue = g_fSpeedControlOutNew - g_fSpeedControlOutOld;//NEW��OLD����100ms�Ÿ���һ�� 
    g_fSpeedControlOut = fValue * (g_nSpeedControlPeriod + 1) / SPEED_CONTROL_PERIOD + g_fSpeedControlOutOld;
}
void GetMotorspeed(void)//��ȡ������� 5ms����һ�β���100ms
//��ΪAB��ֻ����һ��,ֻ����������ò������жϷ���
//�жϷ����Ǹ���g_fLeftMotorOut���������������
{
g_nRightMotorPulse=FTM1_CNT;//��
g_nLeftMotorPulse =FTM2_CNT;//��
FTM2_CNT=0;//����ǰ����������ֵΪ�����˶�Ϊ��
FTM1_CNT=0;//����ǰ����������ֵΪ������Ϊ��                                                                   
       if(g_fLeftMotorOut<0)  g_nLeftMotorPulse = -g_nLeftMotorPulse;
       if(g_fRightMotorOut<0)	g_nRightMotorPulse = -g_nRightMotorPulse;//Ϊʲô�ĳ�С��0�Ϳ�������		
g_LeftMotorPulseSigma+=g_nLeftMotorPulse;
g_RightMotorPulseSigma+=g_nRightMotorPulse;

}
/*************�������***************************/
void DirectionControl(void)
{
      float  fValue,D_Error=0; 
      float RL_Value,fDValue,fPValue,fIValue=0; 
      RL_Value=115-capture[9];
      g_fDirectionControlOutOld = g_fDirectionControlOutNew; 
      fDValue = DIR_CONTROL_D*(RL_Value-D_Error);//(RL_Value-D_Error);//���˲���
      fPValue=RL_Value*DIR_CONTROL_P;//��������
      fIValue+=RL_Value;
      fIValue=fIValue * DIR_CONTROL_I;
      D_Error=RL_Value;
      fValue   = fPValue+fDValue;//-fD_g*Gyro_Angle_Num;//-(CAR_SPEED_SET*RL_Value)/1000;
      g_fDirectionControlOutNew = fValue;
       
}
void DirectionControlOutput(void)
{
  float fValue;
  fValue = g_fDirectionControlOutNew - g_fDirectionControlOutOld;
  g_DirectionControlOut =fValue * (g_nDirectionControlPeriod + 1)/DIRECTION_CONTROL_PERIOD+ g_fDirectionControlOutOld;
}

//************����PWM****************************//
void SetMotorPWM(float L_Motor_PWMOUT,float R_Motor_PWMOUT) //4ǰ5�� 6��7ǰ
{          
       if (L_Motor_PWMOUT<0)
  	  {
     	     FTM_PWM_Duty(FTM0,CH4,(int)(-L_Motor_PWMOUT));	//4,5
             FTM_PWM_Duty(FTM0,CH5,0);
          }
	else
     	{
	     FTM_PWM_Duty(FTM0,CH5,(int)(L_Motor_PWMOUT));	//5,4
             FTM_PWM_Duty(FTM0,CH4,0);
     	}
	if (R_Motor_PWMOUT<0)
     	{
	     FTM_PWM_Duty(FTM0,CH7,(int)(-R_Motor_PWMOUT));//7,6	
             FTM_PWM_Duty(FTM0,CH6,0);
     	}
  	else
      	{
	      FTM_PWM_Duty(FTM0,CH6,(int)(R_Motor_PWMOUT));//6,7	
              FTM_PWM_Duty(FTM0,CH7,0);
      	}	
  
  
}
/********************����������ѹ����***********************/
void MotorSpeedOut(void) 
{  
    float L_Motor_PWM,R_Motor_PWM;
    L_Motor_PWM=g_fLeftMotorOut;
    R_Motor_PWM=g_fRightMotorOut;
    
     if(L_Motor_PWM>0) 	 	//
	  L_Motor_PWM+=MOTOR_OUT_DEAD_VAL;
  	else 	
	  L_Motor_PWM-=MOTOR_OUT_DEAD_VAL;//��������Ŀ���   һ������Ϊ0
    
	if(R_Motor_PWM>0)	 
	  R_Motor_PWM+=MOTOR_OUT_DEAD_VAL;
	else   
	  R_Motor_PWM-=MOTOR_OUT_DEAD_VAL;	
	if( L_Motor_PWM>1200)   L_Motor_PWM=1200;//���ʹ���
	if( L_Motor_PWM<-1200)	 L_Motor_PWM=-1200;
	if( R_Motor_PWM>1200)   R_Motor_PWM=1200;
	if( R_Motor_PWM<-1200) 	 R_Motor_PWM=-1200; //�ж��Ƿ񳬳����ռ�ձ�	
	SetMotorPWM(L_Motor_PWM,R_Motor_PWM);	//���õ�������PWM
        
	
  }
/*******************�������**************/
void MotorOutput(void) 
{ 
  float fLeft, fRight;

  fLeft  = g_fAngleControlOut - g_fSpeedControlOut + g_DirectionControlOut; //�ٶȽǶ�
  fRight = g_fAngleControlOut - g_fSpeedControlOut - g_DirectionControlOut; //�ٶȽǶ�֮��
  g_fLeftMotorOut = fLeft; 
  g_fRightMotorOut= fRight; 
  MotorSpeedOut();
}
 void ImageProc()//�������150   ����ֵ125  �yֵ140
{
   u32 i=0,j=0,m=0;
   for(i=39;i>=30;i--)   //90-99  
     {
          for(j=130;j>5;j--)  
          {
            if(Buffer1[i+row_qian][j]<140) 
            {
              zuoPos = j;
              FLAG_ZUO=1;
              break;
            }
            else
            {
               zuoPos = j;//δ�������߽�
               continue;//����������һ��
            }
          } 
         for(j=130;j<COL-1;j++)          
          {
                if(Buffer1[i+row_qian][j]<140)   
                {
                  youPos = j;//ƫ���м�λ�õ�ֵ
                  FLAG_YOU=1;
                  break;
                }
                else
                {
                  youPos = j;  //δ�������߽�
                  continue;//������һ������
                }
           }
          if((FLAG_ZUO==1)&&(FLAG_YOU==1))
          {
          
               FLAG_ZUO=0;
               FLAG_YOU=0;
               capture[39-i]=(zuoPos+youPos)/2;
              if(capture[39-i]!=130)
              {
                middle++;
              }
               if(39-i==9)
               {
                  zuo=zuoPos;
                  you=youPos;
               }//ȡ��������λ��
          }
          else
          {
             
               if((FLAG_ZUO==1)&&(FLAG_YOU==0))//��������� ����ת�� ƫ�����0   
               {
                    if((zuoPos>50)&&(zuoPos<60))
                        {
                         
                           capture[39-i]=(zuoPos+280)/2;//280  ��Ҫ���е��� �����������
                        }
                        if((zuoPos>60)&&(zuoPos<70))
                        {
                          
                           capture[39-i]=(zuoPos+275)/2;//280  ��Ҫ���е��� �����������
                        }
                        if((zuoPos>70)&&(zuoPos<80))
                        {
                         
                         capture[39-i]=(zuoPos+270)/2;
                        }
                        if((zuoPos>80)&&(zuoPos<90))
                        {
                          
                           capture[39-i]=(zuoPos+265)/2;//���漸�䲻������
                        }
                        if((zuoPos>90)&&(zuoPos<100))
                        {
                           capture[39-i]=(zuoPos+270)/2;
                        }
                        else
                        {
                            capture[39-i]=(zuoPos+265)/2;
                        }
               }  
               if((FLAG_ZUO==0)&&(FLAG_YOU==1))//�ұ��������� ����ת��  ��ƫ��С��0
               {
               
                  if((youPos>130)&&(youPos<140))
                  {
                     capture[39-i]=(youPos+40)/2;
                  }
                 if((youPos>140)&&(youPos<150))
                  {
                     capture[39-i]=(youPos+38)/2;
                  }
                 if((youPos>150)&&(youPos<160))
                  {
                     capture[39-i]=(youPos+28)/2;
                  }
                 if((youPos>170)&&(youPos<180))
                  {
                     
                     capture[39-i]=(youPos+27)/2;
                  }
                 if((youPos>180)&&(youPos<190))
                  {
                    
                     capture[39-i]=(youPos+15)/2;
                  }
                 if((youPos>200)&&(youPos<210))
                  {
                  
                     capture[39-i]=(youPos-10)/2;//���漸�䲻������
                  }
                 if((youPos>210)&&(youPos<220))
                  {
                   
                     capture[39-i]=(youPos-30)/2;
                  }
                 else
                 {
                     capture[39-i]=(youPos-40)/2;
                 }
                 
               }
               if((FLAG_ZUO==0)&&(FLAG_YOU==0))//ʮ����
               {
                    
                     for(m=130;m>1;m--)
                       {
                          if(Buffer1[60][m]<140) 
                            {
                               shizileft = m;
                               zuoflag=1;
                               break;
                            }
                          else
                            {
                                shizileft = m;  //δ�������߽�
                                continue;//����������һ��
                            }
                       }
          
          
          
          
                    for(m=130;m<COL-5;m++)
                    {
                      if(Buffer1[60][m]<140) 
                      {
                        shiziright = m;
                        youflag=1;
                        break;
                      }
                      else
                      {
                         shiziright = m;  //δ�������߽�
                         continue;//����������һ��
                      }
                    }
                    if((zuoflag==1)&&(youflag==1)&&(shizileft==130)&&(shiziright==130))
                    {
                      capture[9]=130;
                    }
                    if((zuoflag==1)&&(youflag==1)&&(shizileft!=130)&&(shiziright!=130))
                    {
                         capture[9]=(shizileft+shiziright)/2;
                    }
                    else
                    {
                      capture[9]=115;
                    }
                    shiziright=0;
                    shizileft=0;
                    zuoflag=0;
                    youflag=0;
                    m=0;
                     
               FLAG_ZUO=0;
               FLAG_YOU=0;   
          }     
      }
      FLAG_ZUO=0;
      FLAG_YOU=0;
     }
/***************************************************************************/
/************************************************************/
     DIR_CONTROL_P=PreDirection;
/*******************************������Խ�紦��************************/
      if(capture[9]==130)
      {
           for(i=130;i>110;i--)
          {
            if(Buffer1[30+row_qian][i]>140)//�������ȫ��������20�������Խ�紦��
            {
              posleft = i;
              hinder_left=1;
              break;
            }
            else
            {
               posleft = i;  //δ�������߽������10����Խ�紦��
               continue;//����������һ��
            }
          }
          
          
          
          
          for(i=130;i<150;i++)//���������20����
          {
            if(Buffer1[30+row_qian][i]>140) 
            {
              posright = i;
              hinder_right=1;
              break;
            }
            else
            {
               posright = i;  //δ�������߽�
               continue;//����������һ��
            }
          }
          if((hinder_left==1)&&(hinder_right==0))//����������ױ�  
          {
              
              if(130-posleft<20)
              {
               capture[9]=40;
            
              }
                
          }else  if((hinder_left==0)&&(hinder_right==1))
          {
              if(posright-130<20)
              {
               capture[9]=220;
               
              }
          }else if((hinder_left==0)&&(hinder_right==0))
          {
               
               
                for(i=130;i>115;i--)
                          {
                           if(Buffer1[60][i]>140)//100�������ȫ��������10�������Խ�紦��
                            {
                              posleft = i;
                              hinder_left=1;
                              break;
                            }
                            else
                            {
                               posleft = i;  //δ�������߽������10����Խ�紦��
                               continue;//����������һ��
                            }
                          }
             
                            for(i=130;i<145;i++)//���������ʮ����
                            {
                              if(Buffer1[60][i]>140)//100 
                              {
                                posright = i;
                                hinder_right=1;
                                break;
                              }
                              else
                              {
                                 posright = i;  //δ�������߽�
                                 continue;//����������һ��
                              }
                            }
                         if((hinder_left==0)&&(hinder_right==0))
                         {
                             capture[9]=shizinum;
                             DIR_CONTROL_P=PreDirection1;
                         }
               
          }
      }
  /*************************����***************************/
   
/*****************************�����ߵ�ʶ��***************************/
       if(middle==10&&abs(capture[9]-124)<5)
       {
         for(j=80;j<170;j+=3)//ÿ��3������һ��
         {
              for(i=150;i<160;i++)
              {
                if(Buffer1[i][j]<140)
                {
                   FLAG1=1;
                   if(FLAG2==1)
                   {
                     start_run++;
                     FLAG2=0;
                   }
                }
                else
                {
                  FLAG2=1;
                  if(FLAG1==1)
                  {
                     FLAG1=0;
                     start_run+=1;
                  }
                }
              }
         }
       }
       if(start_run>=2&&count==8000&&shiziflag==1)//ͣ��
       {
          CAR_SPEED_SET=0;
          delayms(50);
          FTM_PWM_init(FTM0, CH4, 20000,0);//���1��  PTD4  
          FTM_PWM_init(FTM0, CH5, 20000,0);//���1��  PTD5
          FTM_PWM_init(FTM0, CH6, 20000,0);//���2��  PTD6
          FTM_PWM_init(FTM0, CH7, 20000,0);//���2��  PTD7  20khz
          DisableInterrupts;
       }
    
/**********************************************************************/
          FLAG1=0;
          FLAG2=0;
          flag_right=0;
          start_run=0;
          middle=0;
          flag_you=0;
          posleft=0;
          posright=0;
          hinder_right=0;
          hinder_right1=0;
          hinder_right2=0;
          hinder_left=0;
          hinder_left1=0;
}