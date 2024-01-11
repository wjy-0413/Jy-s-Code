/*--------------------------------------------------------------------------------
 * 项目名称:

     中断按键测试程序 V1.0.0

 * 功能描述:

     通过外部中断0控制LED灯3档调光，通过串口通信——无线传输到2个LED灯同步点亮，同步关闭。
 

-------------------------------------------------------------------------------------*/
/************************包含头文件***************************************************/

#include<STC15W.h>
#include<stdio.h>
//#include <intrins.h>
sbit PWM_PIN = P3^5; // PWM输出引脚
sbit TOUCH_PIN = P3^2; // TTP223触摸模块引脚
unsigned char i = 0; // 亮度档位，0-3，对应四个档位
bit touched = 1; // 标志位，表示是否检测到上升沿触摸
unsigned int flag = 0; //触摸计数
unsigned int t = 0; //定时计数
unsigned int PWM_T = 0; //PWM的阈值	
void UartInit();
void SendByte(unsigned char dat);
void ReceiveByte();
void Delay(unsigned char m);

void main()
{
		IT0 = 1;  //触发条件，1=下降沿触发，0=低电平触发
		EX0 = 1;  //外部中断开关，1=打开，0=关闭
//		ES = 1;      //开放串口中断
		EA  = 1;  //全局中断打开，1=打开，0=关闭
		UartInit();  //串口初始化
		PWM_PIN = 0; //PWM口置零
//		SendByte(i);   //发送i，0-3数值

    while(1)
    {
		 // 	  SendByte(i);   //发送i，0-3数值
					switch(i)
					{
							case 0:
									PWM_PIN = 1;
							//		PWM_T = 50;   //关灯
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
						//			PWM_T = 30;  //一档亮度
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
					//				PWM_T = 50;    //二档亮度
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
					//				PWM_T = 80;    //三档亮度，均可调整，频率大约为10KHz
									break;
							default:
									PWM_PIN = 1;
					}
		}
}				
	//***********************外部中断函数***********************//
				void exint0() interrupt 0 
				{
					EX0 = 0;  //外部中断开关，1=打开，0=关闭
					i = (i + 1) % 4; // 增加亮度档位，循环在0-3之间
		//			flag=1;
					SendByte(i);   //发送i，0-3数值
		//			 PWM_PIN =!PWM_PIN;
					EX0 = 1;  //外部中断开关，1=打开，0=关闭
				}
				
				void UartInit(void)		//9600bps@11.0592MHz
				{
					SCON = 0x50;		//8位数据,可变波特率
					AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
					AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
					T2L = 0xE0;		//设定定时初值
					T2H = 0xFE;		//设定定时初值
					AUXR |= 0x10;		//启动定时器2
					ES = 1;
					EA = 1;
				}

//***********************串口发送字符函数***********************//
				void SendByte(unsigned char dat)
				{
					SBUF = dat;
					while(!TI);
					TI = 0;
				}
			//----------------------------------------------------------   
			//  函数名称：void SerialPortInte(void)
			//  函数功能：串口中断方式接收一个字符
			//----------------------------------------------------------   
			void SerialPortReceive(void) interrupt 4 
			{ 
					 while(!RI); 					//查询接收标志位，是否有数据到达缓冲区
					 RI=0;						    //清零接收标志位
					 i=SBUF;					//读取缓冲区的数据
			}			
//功能：延时子函数.
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