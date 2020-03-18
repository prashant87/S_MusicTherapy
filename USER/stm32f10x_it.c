/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "usart.h"
#include "delay.h" 
#include "X9C103.h"

void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}


u8 flag =0;
void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;
	u8 i;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		
		if((USART_RX_STA&0x8000)==0)//����δ���
			{
			if(USART_RX_STA&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)
					USART_RX_STA=0;//���մ���,���¿�ʼ
				else //���������
				{
					USART_RX_STA|=0x8000;	 
				  flag=1;
	        USART_RX_STA = 0;
				}
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			} 
///////////////�������//////////////////
		if(flag)
				 {
					 flag = 0;
					 //cmd = USART_RX_BUF[0];//�и裬��һ�ף���һ�ס�
					 switch(USART_RX_BUF[0])//�ж�ͨ������
					 {
						case 0x01://1ͨ����
								{
								 switch(USART_RX_BUF[1])	
								 {
									 case 0x44://�������ӣ�
										 X9C103_Inc_N_Step(5);
//										 USART_SendData( USART1, 0x01);	
//									 delay_ms(50);
//										 USART_SendData( USART1, 0x44);
									 	GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CS(0);             // CS  ����
										GPIO_SetBits(GPIOC,GPIO_Pin_12);//UD(1);             // U/D ����   �������INC���أ�ִ��UP����  
										Delay(3);           // ��ʱ��Լ2us
										for( i = 5; i>0; i--)
										{
												GPIO_ResetBits(GPIOC,GPIO_Pin_11);//INC(0);         // ��ΪGPIO��ʼ��ʱ��INC�Ѿ������ˡ�INC ����;  // ����һ������
												Delay(200);       // ��ʱ2us����
												GPIO_SetBits(GPIOC,GPIO_Pin_11);//INC(1);         // ����INC //����ģʽ
										}
										GPIO_SetBits(GPIOC,GPIO_Pin_10);//CS(1);
											break;							 
									 case 0x55://������С��
//										 X9C103_Dec_N_Step(5);
//										 USART_SendData( USART1, 0x01);	
//									 delay_ms(50);
//										 USART_SendData( USART1, 0x55);	
									GPIO_ResetBits(GPIOC,GPIO_Pin_12);//UD(0);               //CLRB_X9C103_UD;   // U/D ��0��  �������INC���أ�ִ��Down����  
									Delay(3);            // ��ʱ��Լ2us
									GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CS(0);  
							 
								 for(i=5;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOC,GPIO_Pin_11);//INC(1);               // ����INC    ��ΪINC��������Ч
									 Delay(2);              // ��ʱ2us����
									 GPIO_ResetBits(GPIOC,GPIO_Pin_11);//INC(0);                // INC ����;  // ����һ������
									 Delay(600);            // ��ʱ��Լ500us, Rw�ȴ�����ȶ�
								}
									 GPIO_ResetBits(GPIOC,GPIO_Pin_11);//INC(0);//����ģʽ
									 GPIO_SetBits(GPIOC,GPIO_Pin_10);//CS(1);                 
											break;
									 default:	
											break;		
								 }
								}				 
					 		break;						
						case 0x02://2ͨ����
					 {
             switch(USART_RX_BUF[1])	
						 {
							 case 0x44://�������ӣ�
							 X9C103_Inc_N_Step(1);
								 USART_SendData( USART1, 0x02);	
							 delay_ms(50);
							   USART_SendData( USART1, 0x44);
									break;							 
               case 0x55://������С��
								 USART_SendData( USART1, 0x02);	
							 delay_ms(50);
							   USART_SendData( USART1, 0x55);	
									break;
               default:	
								  break;	
						 }	
						}
						break;
						case 0x03://3ͨ����							
					 {
             switch(USART_RX_BUF[1])	
						 { case 0x44://�������ӣ�
//							   X9C103_Inc_N_Step(1);
//								 USART_SendData( USART1, 0x03);	
//							 delay_ms(50);
//							   USART_SendData( USART1, 0x44);
							 		  GPIO_ResetBits(GPIOA,GPIO_Pin_12);//CS(0);             // CS  ����
										GPIO_SetBits(GPIOA,GPIO_Pin_8);//UD(1);             // U/D ����   �������INC���أ�ִ��UP����  
										Delay(3);           // ��ʱ��Լ2us
										for( i = 5; i>0; i--)
										{
												GPIO_ResetBits(GPIOA,GPIO_Pin_11);//INC(0);         // ��ΪGPIO��ʼ��ʱ��INC�Ѿ������ˡ�INC ����;  // ����һ������
												Delay(200);       // ��ʱ2us����
												GPIO_SetBits(GPIOA,GPIO_Pin_11);//INC(1);         // ����INC //����ģʽ
										}
										GPIO_SetBits(GPIOA,GPIO_Pin_12);//CS(1);
									break;							 
               case 0x55://������С��
//								 X9C103_Dec_N_Step(1); 
//								 USART_SendData( USART1, 0x03);	
//							 delay_ms(50);
//							   USART_SendData( USART1, 0x55);
									GPIO_ResetBits(GPIOA,GPIO_Pin_8);//UD(0);               //CLRB_X9C103_UD;   // U/D ��0��  �������INC���أ�ִ��Down����  
									Delay(3);            // ��ʱ��Լ2us
									GPIO_ResetBits(GPIOA,GPIO_Pin_12);//CS(0);  
							 
								 for(i=5;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOA,GPIO_Pin_11);//INC(1);               // ����INC    ��ΪINC��������Ч
									 Delay(2);              // ��ʱ2us����
									 GPIO_ResetBits(GPIOA,GPIO_Pin_11);//INC(0);                // INC ����;  // ����һ������
									 Delay(600);            // ��ʱ��Լ500us, Rw�ȴ�����ȶ�
								}
									 GPIO_ResetBits(GPIOA,GPIO_Pin_11);//INC(0);//����ģʽ
									 GPIO_SetBits(GPIOA,GPIO_Pin_12);//CS(1);                 							 
									break;
               default:	
								  break;	}	
						}			
            break;						
						case 0x04://4ͨ����
					 {
             switch(USART_RX_BUF[1])	
						 { case 0x44://�������ӣ�
							   X9C103_Inc_N_Step(1);
								 USART_SendData( USART1, 0x04);	
							 delay_ms(50);
							   USART_SendData( USART1, 0x44);
									break;							 
               case 0x55://������С��
                 X9C103_Dec_N_Step(1);								
							   USART_SendData( USART1, 0x04);	
							 delay_ms(50);
							   USART_SendData( USART1, 0x55);	
									break;
               default:	
								  break;	}	
						}
						break;
						case 0x05://5ͨ����
					 {
             switch(USART_RX_BUF[1])	
						 {case 0x44://�������ӣ�						 
									X9C103_Inc_N_Step(1);
									USART_SendData( USART1, 0x05);	
									delay_ms(50);
							    USART_SendData( USART1, 0x44);
									break;							 
               case 0x55://������С��
								 X9C103_Dec_N_Step(1); 
						  	 USART_SendData( USART1, 0x05);	
							 delay_ms(50);
							   USART_SendData( USART1, 0x55);	
									break;
               default:	
								  break;		}
						}
						break;
						case 0x06://6ͨ����
					 {
             switch(USART_RX_BUF[1])	
						 {case 0x44://�������ӣ�
//							   X9C103_Inc_N_Step(5);
//								 USART_SendData( USART1, 0x06);
//									delay_ms(50);							 
//							   USART_SendData( USART1, 0x44);
							      GPIO_ResetBits(GPIOB,GPIO_Pin_12);//CS(0);             // CS  ����
										GPIO_SetBits(GPIOB,GPIO_Pin_10);//UD(1);             // U/D ����   �������INC���أ�ִ��UP����  
										Delay(3);           // ��ʱ��Լ2us
										for( i = 5; i>0; i--)
										{
												GPIO_ResetBits(GPIOB,GPIO_Pin_11);//INC(0);         // ��ΪGPIO��ʼ��ʱ��INC�Ѿ������ˡ�INC ����;  // ����һ������
												Delay(200);       // ��ʱ2us����
												GPIO_SetBits(GPIOB,GPIO_Pin_11);//INC(1);         // ����INC //����ģʽ
										}
										GPIO_SetBits(GPIOB,GPIO_Pin_12);//CS(1);              // ���CS���� //store             
									break;							 
               case 0x55://������С��
//                 X9C103_Dec_N_Step(5);
//							   USART_SendData( USART1, 0x06);	
//							 delay_ms(50);  
//							 USART_SendData( USART1, 0x55);	
									GPIO_ResetBits(GPIOB,GPIO_Pin_10);//UD(0);               //CLRB_X9C103_UD;   // U/D ��0��  �������INC���أ�ִ��Down����  
									Delay(3);            // ��ʱ��Լ2us
									GPIO_ResetBits(GPIOB,GPIO_Pin_12);//CS(0);  
							 
								 for(i=5;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOB,GPIO_Pin_11);//INC(1);               // ����INC    ��ΪINC��������Ч
									 Delay(2);              // ��ʱ2us����
									 GPIO_ResetBits(GPIOB,GPIO_Pin_11);//INC(0);                // INC ����;  // ����һ������
									 Delay(600);            // ��ʱ��Լ500us, Rw�ȴ�����ȶ�
								}
									 GPIO_ResetBits(GPIOB,GPIO_Pin_11);//INC(0);//����ģʽ
									 GPIO_SetBits(GPIOB,GPIO_Pin_12);//CS(1);                 // ���CS���� // store 
									break;
               default:	
								  break;	}	
						}
						break;
						case 0x07://7ͨ����
				   Init_x109_1_3_6();// X9C103_Dec_N_Step(99);//������ 
						break;
						
					 }
					 
				 }			
     }
		
	 }
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
