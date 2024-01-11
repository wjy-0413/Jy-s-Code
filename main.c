/*--------------------------------------------------------------------------------
 * ��Ŀ����:

     �жϰ������Գ��� V1.0.0

 * ��������:

     ͨ���ⲿ�ж�0����LED��3�����⣬ͨ������ͨ�š������ߴ��䵽2��LED��ͬ��������ͬ���رա�
 

-------------------------------------------------------------------------------------*/
/************************����ͷ�ļ�***************************************************/

#include<STC15W.h>
#include<stdio.h>
//#include <intrins.h>
sbit PWM_PIN = P3^5; // PWM�������
sbit TOUCH_PIN = P3^2; // TTP223����ģ������
unsigned char i = 0; // ���ȵ�λ��0-3����Ӧ�ĸ���λ
bit touched = 1; // ��־λ����ʾ�Ƿ��⵽�����ش���
unsigned int flag = 0; //��������
unsigned int t = 0; //��ʱ����
unsigned int PWM_T = 0; //PWM����ֵ	
void UartInit();
void SendByte(unsigned char dat);
void ReceiveByte();
void Delay(unsigned char m);

void main()
{
		IT0 = 1;  //����������1=�½��ش�����0=�͵�ƽ����
		EX0 = 1;  //�ⲿ�жϿ��أ�1=�򿪣�0=�ر�
//		ES = 1;      //���Ŵ����ж�
		EA  = 1;  //ȫ���жϴ򿪣�1=�򿪣�0=�ر�
		UartInit();  //���ڳ�ʼ��
		PWM_PIN = 0; //PWM������
//		SendByte(i);   //����i��0-3��ֵ

    while(1)
    {
		 // 	  SendByte(i);   //����i��0-3��ֵ
					switch(i)
					{
							case 0:
									PWM_PIN = 1;
							//		PWM_T = 50;   //�ص�
							break;
							case 1:
									PWM_PIN = 1;
									Delay(50);
									PWM_PIN = 0;
									Delay(10);
									PWM_PIN = 1;
									Delay(50);
									PWM_PIN = 0;
									Delay(10);
						//			PWM_T = 30;  //һ������
									break;
							case 2:
									PWM_PIN = 1;
									Delay(10);
									PWM_PIN = 0;
									Delay(10);
									PWM_PIN = 1;
									Delay(10);
									PWM_PIN = 0;
									Delay(10);
					//				PWM_T = 50;    //��������
									break;
							case 3:
									PWM_PIN = 1;
									Delay(10);
									PWM_PIN = 0;
									Delay(50);
									PWM_PIN = 1;
									Delay(10);
									PWM_PIN = 0;
									Delay(50);
					//				PWM_T = 80;    //�������ȣ����ɵ�����Ƶ�ʴ�ԼΪ10KHz
									break;
							default:
									PWM_PIN = 1;
					}
		}
}				
	//***********************�ⲿ�жϺ���***********************//
				void exint0() interrupt 0 
				{
					EX0 = 0;  //�ⲿ�жϿ��أ�1=�򿪣�0=�ر�
					i = (i + 1) % 4; // �������ȵ�λ��ѭ����0-3֮��
		//			flag=1;
					SendByte(i);   //����i��0-3��ֵ
		//			 PWM_PIN =!PWM_PIN;
					EX0 = 1;  //�ⲿ�жϿ��أ�1=�򿪣�0=�ر�
				}
				
				void UartInit(void)		//9600bps@11.0592MHz
				{
					SCON = 0x50;		//8λ����,�ɱ䲨����
					AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
					AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
					T2L = 0xE0;		//�趨��ʱ��ֵ
					T2H = 0xFE;		//�趨��ʱ��ֵ
					AUXR |= 0x10;		//������ʱ��2
					ES = 1;
					EA = 1;
				}

//***********************���ڷ����ַ�����***********************//
				void SendByte(unsigned char dat)
				{
					SBUF = dat;
					while(!TI);
					TI = 0;
				}
			//----------------------------------------------------------   
			//  �������ƣ�void SerialPortInte(void)
			//  �������ܣ������жϷ�ʽ����һ���ַ�
			//----------------------------------------------------------   
			void SerialPortReceive(void) interrupt 4 
			{ 
					 while(!RI); 					//��ѯ���ձ�־λ���Ƿ������ݵ��ﻺ����
					 RI=0;						    //������ձ�־λ
					 i=SBUF;					//��ȡ������������
			}			
//���ܣ���ʱ�Ӻ���.
//------------------------------------------------------------------------------------
				void Delay(unsigned char m)
				{
					unsigned char i,j,k;
					for(i=0;i<m;i++)
						for(j=0;j<2;j++)
							for(k=0;k<25;k++)
							{
								;
							}
				}
/**********************************THE END**********************************/ 