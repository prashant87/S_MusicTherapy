#include "X9C103.h"


/*��ʼ��X9C103�ܽ�*/
void X9C103_Config(void)
{
  /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
  GPIO_InitTypeDef GPIO_InitStructure; 

	/*ʹ��x9c103ʹ�õ�GPIOʱ��*/
  RCC_APB2PeriphClockCmd(CS_GPIO_CLK, ENABLE); 	//|RCC_APB2Periph_AFIO
  /*PB3 PB4 ��λ����ΪJTAG���ؿ�ʹ�ã���Ҫ��IO�ڣ���Ҫ�������£RCC_APB2Periph_AFIO�*/ 
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = CS_GPIO_PIN|INC_GPIO_PIN|UD_GPIO_PIN; //PB0 PB1 PB5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //GPIO����������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(CS_GPIO_PORT, &GPIO_InitStructure);  /*���ÿ⺯������ʼ��GPIO*/
  GPIO_SetBits(CS_GPIO_PORT,CS_GPIO_PIN|INC_GPIO_PIN|UD_GPIO_PIN);/* ��λ����GPIO��	*/
  
//  GPIO_InitStructure.GPIO_Pin = LCD_BRIGHT_UD|LCD_BRIGHT_INC|LCD_BRIGHT_CS; //??PG3~PG5
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //GPIO?????????
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIO_LCDBRIGHT, &GPIO_InitStructure);  //???GPIO????
//  GPIO_SetBits(GPIO_LCDBRIGHT,LCD_BRIGHT_UD|LCD_BRIGHT_INC|LCD_BRIGHT_CS);
}

//��ʱus�ӳ��� 
void Delay(unsigned int t) 
{ 
unsigned int i; 
for(i=0;i<t;i++) ;

} 

//************************************************************************
// ���ֵ�λ�����ϵ�һ��
// ���ֵ�λ��100����ͷ���൱��99��
//************************************************************************
void X9C103_Inc_N_Step(unsigned char N)
{
   unsigned char i=0; 
          
        CS(0);             // CS  ����
        UD(1);             // U/D ����   �������INC���أ�ִ��UP����  
        Delay(3);           // ��ʱ��Լ2us
        for(i = N; i>0; i--)
        {
            INC(0);         // ��ΪGPIO��ʼ��ʱ��INC�Ѿ������ˡ�INC ����;  // ����һ������
            Delay(200);       // ��ʱ2us����
            INC(1);         // ����INC //����ģʽ
        }
        CS(1);              // ���CS���� //store

}
//************************************************************************
// ���ֵ�λ�����µ�һ��
// ���ֵ�λ��100����ͷ���൱��99��
//************************************************************************
void X9C103_Dec_N_Step(unsigned char N)
{
   unsigned char i=0; 
    UD(0);               //CLRB_X9C103_UD;   // U/D ��0��  �������INC���أ�ִ��Down����  
    Delay(3);            // ��ʱ��Լ2us
    CS(0);  
 
   for(i=N;i>0;i--) 
  { 
     INC(1);               // ����INC    ��ΪINC��������Ч
     Delay(2);              // ��ʱ2us����
     INC(0);                // INC ����;  // ����һ������
     Delay(600);            // ��ʱ��Լ500us, Rw�ȴ�����ȶ�
  }
     INC(0);//����ģʽ
     CS(1);                 // ���CS���� // store 
 

}

void X9C103_Init(void)//��ʼ�����м�λ��
{
 X9C103_Dec_N_Step(99); 
 delay_ms(2000);
 X9C103_Inc_N_Step(49); 
} 

void Init_x109_1_3_6(void)
{
	u8 i;
								/*1*/
									GPIO_ResetBits(GPIOC,GPIO_Pin_12);//UD(0);               //CLRB_X9C103_UD;   // U/D ��0��  �������INC���أ�ִ��Down����  
									Delay(3);            // ��ʱ��Լ2us
									GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CS(0);  
							 
								 for(i=99;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOC,GPIO_Pin_11);//INC(1);               // ����INC    ��ΪINC��������Ч
									 Delay(2);              // ��ʱ2us����
									 GPIO_ResetBits(GPIOC,GPIO_Pin_11);//INC(0);                // INC ����;  // ����һ������
									 Delay(600);            // ��ʱ��Լ500us, Rw�ȴ�����ȶ�
								}
									 GPIO_ResetBits(GPIOC,GPIO_Pin_11);//INC(0);//����ģʽ
									 GPIO_SetBits(GPIOC,GPIO_Pin_10);//CS(1); 
								/*3*/
									GPIO_ResetBits(GPIOA,GPIO_Pin_8);//UD(0);               //CLRB_X9C103_UD;   // U/D ��0��  �������INC���أ�ִ��Down����  
									Delay(3);            // ��ʱ��Լ2us
									GPIO_ResetBits(GPIOA,GPIO_Pin_12);//CS(0);  
							 
								 for(i=99;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOA,GPIO_Pin_11);//INC(1);               // ����INC    ��ΪINC��������Ч
									 Delay(2);              // ��ʱ2us����
									 GPIO_ResetBits(GPIOA,GPIO_Pin_11);//INC(0);                // INC ����;  // ����һ������
									 Delay(600);            // ��ʱ��Լ500us, Rw�ȴ�����ȶ�
								}
									 GPIO_ResetBits(GPIOA,GPIO_Pin_11);//INC(0);//����ģʽ
									 GPIO_SetBits(GPIOA,GPIO_Pin_12);//CS(1); 
								/*6*/
									GPIO_ResetBits(GPIOB,GPIO_Pin_10);//UD(0);               //CLRB_X9C103_UD;   // U/D ��0��  �������INC���أ�ִ��Down����  
									Delay(3);            // ��ʱ��Լ2us
									GPIO_ResetBits(GPIOB,GPIO_Pin_12);//CS(0);  
							 
								 for(i=99;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOB,GPIO_Pin_11);//INC(1);               // ����INC    ��ΪINC��������Ч
									 Delay(2);              // ��ʱ2us����
									 GPIO_ResetBits(GPIOB,GPIO_Pin_11);//INC(0);                // INC ����;  // ����һ������
									 Delay(600);            // ��ʱ��Լ500us, Rw�ȴ�����ȶ�
								}
									 GPIO_ResetBits(GPIOB,GPIO_Pin_11);//INC(0);//����ģʽ
									 GPIO_SetBits(GPIOB,GPIO_Pin_12);//CS(1);                 
}