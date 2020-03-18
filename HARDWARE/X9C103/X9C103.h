#ifndef __X9C103_H
#define __X9C103_H

#include "stm32f10x.h"

/*--------------------------------------------------------------------------
X9C103.H
X9C103 functions.
Copyright (c) 2007 DC. By Delphifx 2007-8-11.
All rights reserved.
--------------------------------------------------------------------------*/

// CS
#define CS_GPIO_PORT    	GPIOB		              /* GPIO�˿� */
#define CS_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define CS_GPIO_PIN		    GPIO_Pin_12			        /* ���ӵ�CSʱ���ߵ�GPIO */

// INC
#define INC_GPIO_PORT    	GPIOB			              /* GPIO�˿� */
#define INC_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define INC_GPIO_PIN		  GPIO_Pin_11			        /* ���ӵ�INCʱ���ߵ�GPIO */

// UD
#define UD_GPIO_PORT    	GPIOB		              /* GPIO�˿� */
#define UD_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define UD_GPIO_PIN		    GPIO_Pin_10		        /* ���ӵ�UDʱ���ߵ�GPIO */

/* �йص�λ���ĺ궨��  ʹ�ñ�׼�Ĺ̼������IO*/
#define CS(a)	if (a)\
							GPIO_SetBits(CS_GPIO_PORT,CS_GPIO_PIN);\
							else		\
							GPIO_ResetBits(CS_GPIO_PORT,CS_GPIO_PIN)

#define INC(a)	if (a)	\
								GPIO_SetBits(INC_GPIO_PORT,INC_GPIO_PIN);\
								else		\
								GPIO_ResetBits(INC_GPIO_PORT,INC_GPIO_PIN)

#define UD(a)	if (a)	\
							GPIO_SetBits(UD_GPIO_PORT,UD_GPIO_PIN);\
							else		\
							GPIO_ResetBits(UD_GPIO_PORT,UD_GPIO_PIN)



void X9C103_Inc_N_Step(unsigned char N);
void X9C103_Dec_N_Step(unsigned char N);
void Delay(unsigned int t) ;
void X9C103_Init(void);//��ʼ�����м�λ��
void X9C103_Config(void);
void Init_x109_1_3_6(void);
#endif