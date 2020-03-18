#include "sys.h"
#include "delay.h"
#include "usart.h" 
//#include "led.h" 		 	 
//#include "lcd.h"  
//#include "key.h"     
//#include "usmart.h" 
//#include "malloc.h"
//#include "sdio_sdcard.h"  
//#include "w25qxx.h"    
//#include "ff.h"  
//#include "exfuns.h"   
//#include "text.h" 
//#include "vs10xx.h"
//#include "mp3player.h"	
#include "X9C103.h"
 
/************************************************
 ALIENTEKս��STM32������ʵ��43
 ���ֲ����� ʵ��
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

	
void usart_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
	USART_DeInit(USART1);//��λUSART1;
	//GPIOA�˿�ģʽ���ã�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//TX_PA9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//RX_PA10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//���ڳ�ʼ����
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure);
	
	#if EN_USART1_RX
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	#endif
	
	
	USART_Cmd(USART1,ENABLE);
	
}
void Test_X9C103_Config(void)
{
  /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
  GPIO_InitTypeDef GPIO_InitStructure; 

	/*ʹ��x9c103ʹ�õ�GPIOʱ��*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE); 	//|RCC_APB2Periph_AFIO

	/*3ͨ��*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_8; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //GPIO����������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  /*���ÿ⺯������ʼ��GPIO*/
  GPIO_SetBits(GPIOA,GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_8);/* ��λ����GPIO*/
  /*6ͨ��*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //GPIO����������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  /*���ÿ⺯������ʼ��GPIO*/
  GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10);/* ��λ����GPIO*/
	/*1ͨ��*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //GPIO����������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  /*���ÿ⺯������ʼ��GPIO*/
  GPIO_SetBits(GPIOC,GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10);/* ��λ����GPIO*/
}
	
 int main(void)
 {	 
 
	delay_init();	    	 //��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	usart_init(9600);	 	//���ڳ�ʼ��Ϊ115200
	USART_RX_STA=0;       //����״̬���
// 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
//	KEY_Init();					//��ʼ������
//	LCD_Init();			   		//��ʼ��LCD     
//	W25QXX_Init();				//��ʼ��W25Q128
	 
	 
// 	VS_Init();	  				//��ʼ��VS1053 			
//	
//	 
//	 
// 	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
//	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
// 	f_mount(fs[0],"0:",1); 		//����SD�� 
// 	f_mount(fs[1],"1:",1); 		//����FLASH.
//	POINT_COLOR=RED;  
	 
// 	while(font_init()) 				//����ֿ�
//	{	    
////		LCD_ShowString(30,50,200,16,16,"Font Error!");
////		delay_ms(200);				  
////		LCD_Fill(30,50,240,66,WHITE);//�����ʾ	     
//	}
// 	Show_Str(30,50,200,16,"ս�� STM32������",16,0);				    	 
//	Show_Str(30,70,200,16,"���ֲ�����ʵ��",16,0);				    	 
//	Show_Str(30,90,200,16,"����ԭ��@ALIENTEK",16,0);				    	 
//	Show_Str(30,130,200,16,"KEY0:NEXT   KEY2:PREV",16,0);
//	Show_Str(30,150,200,16,"KEY_UP:VOL+ KEY1:VOL-",16,0);
//	delay_ms(5000);	
    //X9C103_Config();
		Test_X9C103_Config();
		delay_ms(5000);
		Init_x109_1_3_6();//ȫ�����㣻
   //delay_ms(5000);
  //X9C103_Dec_N_Step(99); //�����ѹΪ0��
	//X9C103_Inc_N_Step(99); //����ѹ���������źŵ�ֵ��
    delay_ms(2000);
	while(1)		
	{

		  
//  	LED1=0; 	  
//		Show_Str(30,170,200,16,"�洢������...",16,0);
//		printf("Ram Test:0X%04X\r\n",VS_Ram_Test());//��ӡRAM���Խ��	    
//		Show_Str(30,170,200,16,"���Ҳ�����...",16,0); 	 	 
// 		VS_Sine_Test();	   
//		Show_Str(30,170,200,16,"<<���ֲ�����>>",16,0); 		 
//		LED1=1;
//		mp3_play();
//	  USART_SendData( USART1, 0x99);
		delay_ms(3000);
	} 	   										    
}



