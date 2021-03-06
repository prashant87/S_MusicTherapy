#include "X9C103.h"


/*初始化X9C103管脚*/
void X9C103_Config(void)
{
  /*定义一个GPIO_InitTypeDef类型的结构体*/
  GPIO_InitTypeDef GPIO_InitStructure; 

	/*使能x9c103使用的GPIO时钟*/
  RCC_APB2PeriphClockCmd(CS_GPIO_CLK, ENABLE); 	//|RCC_APB2Periph_AFIO
  /*PB3 PB4 复位后，作为JTAG下载口使用，想要用IO口，需要配置以下CC_APB2Periph_AFIO�*/ 
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = CS_GPIO_PIN|INC_GPIO_PIN|UD_GPIO_PIN; //PB0 PB1 PB5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //GPIO工作在推挽模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(CS_GPIO_PORT, &GPIO_InitStructure);  /*调用库函数，初始化GPIO*/
  GPIO_SetBits(CS_GPIO_PORT,CS_GPIO_PIN|INC_GPIO_PIN|UD_GPIO_PIN);/* 置位所有GPIO灯	*/
  
//  GPIO_InitStructure.GPIO_Pin = LCD_BRIGHT_UD|LCD_BRIGHT_INC|LCD_BRIGHT_CS; //??PG3~PG5
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //GPIO?????????
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIO_LCDBRIGHT, &GPIO_InitStructure);  //???GPIO????
//  GPIO_SetBits(GPIO_LCDBRIGHT,LCD_BRIGHT_UD|LCD_BRIGHT_INC|LCD_BRIGHT_CS);
}

//延时us子程序 
void Delay(unsigned int t) 
{ 
unsigned int i; 
for(i=0;i<t;i++) ;

} 

//************************************************************************
// 数字电位器向上调一步
// 数字电位器100个抽头，相当于99步
//************************************************************************
void X9C103_Inc_N_Step(unsigned char N)
{
   unsigned char i=0; 
          
        CS(0);             // CS  拉低
        UD(1);             // U/D 拉高   则下面的INC下沿，执行UP操作  
        Delay(3);           // 延时大约2us
        for(i = N; i>0; i--)
        {
            INC(0);         // 因为GPIO初始化时，INC已经拉高了。INC 拉低;  // 产生一个下沿
            Delay(200);       // 延时2us左右
            INC(1);         // 拉高INC //保存模式
        }
        CS(1);              // 完毕CS拉高 //store

}
//************************************************************************
// 数字电位器向下调一步
// 数字电位器100个抽头，相当于99步
//************************************************************************
void X9C103_Dec_N_Step(unsigned char N)
{
   unsigned char i=0; 
    UD(0);               //CLRB_X9C103_UD;   // U/D 清0，  则下面的INC下沿，执行Down操作  
    Delay(3);            // 延时大约2us
    CS(0);  
 
   for(i=N;i>0;i--) 
  { 
     INC(1);               // 拉高INC    因为INC的下沿有效
     Delay(2);              // 延时2us左右
     INC(0);                // INC 拉低;  // 产生一个下沿
     Delay(600);            // 延时大约500us, Rw等待输出稳定
  }
     INC(0);//保存模式
     CS(1);                 // 完毕CS拉高 // store 
 

}

void X9C103_Init(void)//初始化至中间位置
{
 X9C103_Dec_N_Step(99); 
 delay_ms(2000);
 X9C103_Inc_N_Step(49); 
} 

void Init_x109_1_3_6(void)
{
	u8 i;
								/*1*/
									GPIO_ResetBits(GPIOC,GPIO_Pin_12);//UD(0);               //CLRB_X9C103_UD;   // U/D 清0，  则下面的INC下沿，执行Down操作  
									Delay(3);            // 延时大约2us
									GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CS(0);  
							 
								 for(i=99;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOC,GPIO_Pin_11);//INC(1);               // 拉高INC    因为INC的下沿有效
									 Delay(2);              // 延时2us左右
									 GPIO_ResetBits(GPIOC,GPIO_Pin_11);//INC(0);                // INC 拉低;  // 产生一个下沿
									 Delay(600);            // 延时大约500us, Rw等待输出稳定
								}
									 GPIO_ResetBits(GPIOC,GPIO_Pin_11);//INC(0);//保存模式
									 GPIO_SetBits(GPIOC,GPIO_Pin_10);//CS(1); 
								/*3*/
									GPIO_ResetBits(GPIOA,GPIO_Pin_8);//UD(0);               //CLRB_X9C103_UD;   // U/D 清0，  则下面的INC下沿，执行Down操作  
									Delay(3);            // 延时大约2us
									GPIO_ResetBits(GPIOA,GPIO_Pin_12);//CS(0);  
							 
								 for(i=99;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOA,GPIO_Pin_11);//INC(1);               // 拉高INC    因为INC的下沿有效
									 Delay(2);              // 延时2us左右
									 GPIO_ResetBits(GPIOA,GPIO_Pin_11);//INC(0);                // INC 拉低;  // 产生一个下沿
									 Delay(600);            // 延时大约500us, Rw等待输出稳定
								}
									 GPIO_ResetBits(GPIOA,GPIO_Pin_11);//INC(0);//保存模式
									 GPIO_SetBits(GPIOA,GPIO_Pin_12);//CS(1); 
								/*6*/
									GPIO_ResetBits(GPIOB,GPIO_Pin_10);//UD(0);               //CLRB_X9C103_UD;   // U/D 清0，  则下面的INC下沿，执行Down操作  
									Delay(3);            // 延时大约2us
									GPIO_ResetBits(GPIOB,GPIO_Pin_12);//CS(0);  
							 
								 for(i=99;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOB,GPIO_Pin_11);//INC(1);               // 拉高INC    因为INC的下沿有效
									 Delay(2);              // 延时2us左右
									 GPIO_ResetBits(GPIOB,GPIO_Pin_11);//INC(0);                // INC 拉低;  // 产生一个下沿
									 Delay(600);            // 延时大约500us, Rw等待输出稳定
								}
									 GPIO_ResetBits(GPIOB,GPIO_Pin_11);//INC(0);//保存模式
									 GPIO_SetBits(GPIOB,GPIO_Pin_12);//CS(1);                 
}