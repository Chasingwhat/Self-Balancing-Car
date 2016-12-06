#ifndef _CAR_H_
#define _CAR_H_

#include "include.h"


#define Angle_Out_Max  (12800)//����ֵ
#define Angle_Out_Min   (-12800)//����ֵ

#define Time_PartCntMax  5   //5���ж�Ƭ


#define CAR_SPEED_CONSTANT  0.164//�ٶȵı����ĵ��ڣ�1000/(100*157))

#define  SPEED_CONTROL_COUNT  20   //�ٶȷֲ��������                       
#define  SPEED_CONTROL_PERIOD  100//����Ŀ���������100ms

#define  MOTOR_OUT_DEAD_VAL  0//�����������
#define  MOTOR_OUT_MAX 0//��������ռ�ձ�
#define  MOTOR_OUT_MIN 0//�������Сռ�ձ�

#define  DIRECTION_CONTROL_PERIOD 17	//�����������20ms
#define  DIRECTION_CONTROL_COUNT 1	//����ֲ��������10ms
#define  DIRECTION_OFFSET  0
/************����ͷ����*****************/
#define ROW 220               //����
#define COL 260              //����  Ϊ����������  ���Ըı䳵���λ��
#define PicSize  ROW*COL      //ͼ���С


#define rowStart 160       //ͼ������ʼ����100
#define rowEnd   200      //ͼ������ֹ����140
#define rowNum   rowEnd-rowStart  //��Ч����������ԭʼ�ɼ�����ΪROW(��Include.h�ж���)
#define proPix   6        //��Ե���������߽���Ч����  
#define CENTURE  154      //����ֵ

void Get_AD_angle(void);
void Angle_Control(void);//������ǵĴ�С

void SpeedControl(void);//���㳵���ٶ�
void SpeedControlOutput(void);
void GetMotorspeed(void);
void SetMotorPWM(float L_Motor_PWMOUT,float R_Motor_PWMOUT);
void MotorSpeedOut(void);
void MotorOutput(void) ;
void DirectionControlOutput(void);
void DirectionControl(void);
void DataReset(void);
void ImageProc(void);
#endif