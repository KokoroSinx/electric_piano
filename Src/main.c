/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//定义按键部分
#define Key1 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)
#define Key2 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)
#define Key3 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)
#define Key4 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)
#define Key5 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)
#define Key6 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)
#define Key7 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)
#define Key8 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15)
#define Key9 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8)





unsigned char Key1_flag=0;
unsigned char Key2_flag=0;
unsigned char Key3_flag=0;
unsigned char Key4_flag=0;
unsigned char Key5_flag=0;
unsigned char Key6_flag=0;
unsigned char Key7_flag=0;
unsigned char Key8_flag=0;                           //定义按键部分
unsigned char Key9_flag=0;                           //定义按键部分



#define led1(b)	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, (GPIO_PinState) (b));	// 
#define led2(b)	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (GPIO_PinState) (b));	// 
#define led3(b)	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (GPIO_PinState) (b));	// 
#define led4(b)	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (GPIO_PinState) (b));	// 
#define led5(b)	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (GPIO_PinState) (b));	// 
#define led6(b)	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (GPIO_PinState) (b));	// 
#define led7(b)	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (GPIO_PinState) (b));	// 




#define Smg1_0 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET)
#define Smg1_1 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET)

#define Smg2_0 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET)
#define Smg2_1 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET)

#define Smg3_0 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET)
#define Smg3_1 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET)

#define Smg4_0 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)
#define Smg4_1 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET)

#define Smg5_0 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET)
#define Smg5_1 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET)

#define Smg6_0 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET)
#define Smg6_1 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET)

#define Smg7_0 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET)
#define Smg7_1 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET)

#define Smg8_0 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET)
#define Smg8_1 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET)
uint8_t Dis_Data[]= {0x3,0x9F,0x25,0xD,0x99,0x49,0x41,0x1F,0x1,0x9,0xff}; //0,1,2,3,4,5,6,7,8,9,全灭   //定义数码管显示部分

unsigned int Fre = 0;                                                 //频率数据

unsigned int SoundFlag = 0;                                           //管脚取反标志位


#define Sound(S) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,(GPIO_PinState)(S))      //音频输出管脚IO




uint16_t voiceCount = 0 ;		//播放音乐的几个变量
uint16_t voiceNum = 0 ;			//音调
uint16_t songNum = 0 ;			//歌曲
uint16_t state = 0 ;
uint16_t stateF = 0 ;



uint16_t tone[]=		 //低音1调到高音7调
{
	63628,63835,64021,64103,64260,64400,64524,
	64580,64684,64777,64820,64898,64968,65030,
	65058,65100,65157,65178,65217,65252,65283
};



uint8_t Song[][100]=               //任意选几首音乐的旋律
{
	{1,2,3,1,1,2,3,1,3,4,5,3,4,5,5,6,5,4,3,1,5,6,5,4,3,1,1,5,1,1,5,1,255},  //《两只老虎》
	{5,6,5,6,5,6,5,5,8,7,6,5,3,5,5,3,4,5,5,3,1,4,3,2,1,2,1,255},   //《找朋友》
	{5,10,9,10,3,8,7,6,6,9,8,9,6,8,9,9,9,9,8,10,10,9,9,5,10,9,10,3,8,7,6,5,6,8,8,8,9,10,9,8,7,8,8,255},//《感恩的心》
	{1,2,3,1,5,6,6,8,6,5,6,6,8,5,6,5,6,5,3,5,3,1,2,3,1,255},   //《上学歌》


	{5,3,5,3,5,3,1,2,4,3,2,5,5,3,5,3,5,3,1,2,4,3,2,1,2,2,4,4,3,1,5,2,4,3,2,5,5,3,5,3,5,3,1,2,4,3,2,1,255},  //《粉刷匠》
//{1,2,3,4,5,3,1,8,6,4,5,5,3,1,2,3,4,5,3,2,1,2,3,2,5,1,2,3,4,5,3,1,8,6,4,5,3,1,2,3,4,5,3,2,1,2,3,1,1,8,6,4,5,5,1,8,6,4,5,3,1,2,3,4,5,3,2,1,2,3,1,1,255},//《小红帽》
//{5,8,6,8,5,3,5,2,3,5,0,3,5,6,8,5,6,5,3,5,1,3,2,0,3,2,1,2,3,6,5,3,5,6,0,5,8,6,5,3,5,2,5,2,3,2,1,255},  //《一分钱》
//{5,3,5,3,5,3,2,3,5,5,5,3,6,5,3,5,3,2,1,2,3,5,3,2,1,2,3,6,5,6,5,2,3,5,6,5,6,5,2,3,1,255},  //《丢手绢》
//{5,3,5,3,5,6,5,3,6,5,1,1,2,3,5,3,2,0,3,5,5,5,6,5,3,5,5,6,5,8,6,5,1,5,3,2,1,2,3,5,5,2,3,1,10,9,8,6,5,5,6,6,5,6,8,10,8,9,0,5,10,9,8,6,5,5,6,6,5,6,10,9,9,10,9,8,6,5,5,8,6,5,3,2,1,0,2,3,5,5,0,5,6,8,255},                //《七子之歌-澳门》
//{3,3,4,5,5,4,3,2,1,1,2,3,3,2,2,3,3,4,5,5,4,3,2,1,1,2,3,2,1,1,2,2,3,1,2,3,4,3,1,2,3,4,3,2,1,2,1,3,3,3,4,5,5,4,3,4,2,1,1,2,3,2,1,1,255},  //《欢乐颂》
//{5,8,5,4,3,2,1,1,1,2,3,3,1,3,4,5,5,5,8,5,4,3,5,2,4,3,2,6,5,2,3,1,1,0,5,3,6,8,7,6,7,5,3,9,9,9,8,7,6,8,5,5,5,3,6,8,7,6,7,8,9,5,6,7,8,9,5,8,8,255}, //《我爱北京天安门》
//{3,5,8,5,6,0,6,5,3,3,5,5,3,5,6,8,9,8,5,3,2,5,3,3,3,3,5,8,5,6,0,8,9,8,5,3,5,7,6,0,3,2,3,5,10,9,7,8,3,5,8,3,5,8,5,6,0,8,9,8,5,3,5,7,6,0,3,2,3,5,10,9,7,8,3,5,2,3,5,10,9,9,9,7,8,255},//《北京欢迎你》
//{10,9,9,10,8,0,3,8,6,5,3,5,0,5,5,6,8,8,8,6,8,3,5,5,6,5,3,2,2,0,10,9,9,10,8,0,3,8,6,5,3,5,0,5,5,6,8,8,6,5,6,3,0,3,10,10,10,10,9,6,8,255},//《当兵的人》
//{3,3,5,6,8,8,6,5,5,6,5,3,3,5,6,8,8,6,5,5,6,5,5,5,5,3,5,6,6,5,3,2,3,5,3,2,1,1,2,1,255},//《茉莉花》
//{3,1,3,3,1,3,3,5,6,5,0,6,6,5,5,4,4,4,2,3,2,1,2,0,3,1,0,3,1,0,3,3,5,6,6,0,8,5,5,6,3,2,1,2,3,5,8,5,5,6,3,2,1,2,3,1,255},//《数鸭子》
//{1,1,3,4,5,5,5,3,4,4,4,2,1,3,5,0,1,1,3,4,5,5,5,3,4,4,4,2,1,3,1,0,6,6,4,5,5,5,5,3,4,4,4,2,1,3,5,0,6,6,4,5,5,5,5,3,4,4,4,2,1,3,1,0,255},//《洋娃娃和小熊跳舞》
};
uint8_t   Len[][100]=           //上面几首音乐的旋律每个音符对应的节拍
{

	{2,2,2,2,2,2,2,2,2,2,4,2,2,4,2,2,2,2,4,4,2,2,2,2,4,4,2,3,4,2,3,4,255},		  //《两只老虎》
	{2,2,2,2,2,2,4,2,2,2,2,4,4,2,2,2,2,2,2,4,2,2,2,2,2,2,4,255},		 //《找朋友》
	{2,4,2,6,2,4,2,6,2,4,2,5,1,1,2,1,1,2,1,1,2,2,4,2,4,2,6,2,4,2,6,2,2,1,1,2,2,2,4,2,2,2,8,255},//《感恩的心》
	{2,2,2,2,6,2,2,2,2,6,2,2,4,2,2,4,2,2,2,2,2,2,2,2,6,255},//《上学歌》
	{2,2,2,2,2,2,4,2,2,2,2,4,2,2,2,2,2,2,4,2,2,2,2,4,2,2,2,2,2,2,4,2,2,2,2,4,2,2,2,2,2,2,4,2,2,2,2,4,255},		 //《粉刷匠》

//
//{2,2,2,2,4,2,2,4,2,2,2,2,4,2,2,2,2,2,2,2,2,4,4,4,4,2,2,2,2,4,2,2,4,2,2,4,4,2,2,2,2,2,2,2,2,4,4,4,4,4,2,2,2,2,4,4,2,2,4,4,2,2,2,2,2,2,2,2,4,4,4,4,255},	 //《小红帽》
//{4,4,2,2,4,2,2,2,2,4,4,2,2,2,2,2,2,2,2,2,4,2,4,4,2,2,2,2,8,2,2,2,2,4,4,2,2,2,2,2,2,4,2,2,2,2,8,255},		 //《一分钱》
//{6,2,6,2,2,2,2,2,8,2,4,2,4,4,2,2,2,2,4,4,4,4,2,2,2,2,8,2,2,2,2,2,2,4,2,2,2,2,4,4,8,255},		 //《丢手绢》
//{4,2,2,2,6,2,2,2,2,8,4,2,2,4,2,2,4,2,2,8,2,2,2,2,2,4,2,2,2,2,2,8,4,2,2,2,2,4,2,6,2,2,4,16,4,2,1,2,2,4,2,4,2,2,1,2,2,12,2,2,4,2,1,2,2,4,2,4,2,4,2,2,16,4,2,1,2,2,4,4,2,2,2,2,4,4,2,2,8,8,4,2,2,16,255},			  //《七子之歌-澳门》
//{4,4,4,4,4,4,4,4,4,4,4,4,5,2,6,4,4,4,4,4,4,4,4,4,4,4,4,5,2,6,4,4,4,4,4,2,2,4,4,4,2,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,2,4,4,4,4,5,2,6,255},//《欢乐颂》
//{2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,6,6,2,2,2,2,2,2,4,2,2,2,2,4,2,2,6,4,4,5,2,4,4,4,2,2,4,4,2,2,2,2,4,2,2,6,6,5,2,4,4,2,2,2,2,6,2,2,2,2,4,4,6,4,255},//《我爱北京天安门》
//{4,4,2,2,4,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,2,2,2,6,2,2,2,2,4,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,5,2,8,2,2,8,2,2,2,2,4,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,5,2,8,2,2,2,2,2,2,6,10,8,4,10,255},//《北京欢迎你》
//{6,4,3,2,8,4,4,4,2,2,4,8,4,4,2,2,4,3,2,4,4,6,4,2,2,4,2,2,8,4,6,4,3,2,8,4,4,4,2,2,4,8,4,2,4,2,4,4,4,2,2,4,2,2,2,4,2,4,2,2,8,4,255},//《当兵的人》
//{4,2,2,2,2,2,2,4,2,2,6,4,2,2,2,2,2,2,4,2,2,6,4,4,4,2,2,4,4,6,4,2,2,4,2,2,4,2,2,8,255},//《茉莉花》
//{4,4,2,2,4,2,2,2,2,4,4,2,2,2,2,2,2,4,2,2,2,2,4,4,4,2,2,4,2,2,2,2,2,2,4,4,4,2,2,4,4,2,2,2,2,6,4,2,2,4,4,2,2,2,2,6,255},//《数鸭子》
//{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,255},//《洋娃娃和小熊跳舞》
};






/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void DisFunction(unsigned char q)        //显示驱动
{
	if((q&0x80)==0x80) Smg1_1;
	else               Smg1_0;
	q=q<<1;

	if((q&0x80)==0x80) Smg2_1;
	else               Smg2_0;
	q=q<<1;

	if((q&0x80)==0x80) Smg3_1;
	else               Smg3_0;
	q=q<<1;

	if((q&0x80)==0x80) Smg4_1;
	else               Smg4_0;
	q=q<<1;

	if((q&0x80)==0x80) Smg5_1;
	else               Smg5_0;
	q=q<<1;

	if((q&0x80)==0x80) Smg6_1;
	else               Smg6_0;
	q=q<<1;

	if((q&0x80)==0x80) Smg7_1;
	else               Smg7_0;
	q=q<<1;

	if((q&0x80)==0x80) Smg8_1;
	else               Smg8_0;
}
uint16_t  diao = 0 ;  //音调 0 - 2 ;
uint32_t keyTim[21] ;	//记录按下的时间
uint8_t keyOrder[21] ;	//记录按下的时间
uint16_t key9F = 0 ;

void delayus(uint32_t i)
{
	while(i)
	{
		i -- ;
		__NOP() ; __NOP() ;
	}

}


void Key_Dispose()                       //按键处理函数
{
	if(keyOrder[0] > 20 )
	{
		keyOrder[0]  = 20 ;									 	//记录按键次数
		keyTim[keyOrder[0]]  = 0  ;						//记录按键按下的时间
 	}
	if(keyTim[keyOrder[0]]  > 2123123123 )	//控制按键按下的最大时间
	{
		keyTim[keyOrder[0]] = 2123123123  ;		 
	}
	
 	if( !Key1 || !Key2 || !Key3 || !Key4 || !Key5 || !Key6 || !Key7 || !Key8 )  
	{
		if(!Key1 || !Key2 || !Key3 || !Key4 || !Key5 || !Key6 || !Key7 )
		{
			if(state)
			{
 				state = 0 ;		//停止播放歌曲
				key9F = 1 ;		//清空回放内容
			}
 		}
 		if(key9F)
		{
			key9F = 0 ;				//清空回放
			keyTim[0] = keyTim[1] = keyTim[2] = keyTim[3] = keyTim[4] = keyTim[5] = keyTim[6] = keyTim[7] = keyTim[8] = 0 ;
			keyOrder[0] = keyOrder[1] = keyOrder[2] = keyOrder[3] = keyOrder[4] = keyOrder[5] = keyOrder[6] = keyOrder[7] = keyOrder[8] = 0 ;
 		}
 		
	}
	
	if(!Key1 )                             //按键按下
	{
		if(Key1_flag==1)                   //按键按下标志位
		{
			Key1_flag = 0;                  //清零标志
			songNum=0;
			state=0;

			led1(0)
			Fre = tone[diao * 7  ];					//取频率值
			MX_TIM4_Init();                 //初始化定时器
			HAL_Delay(10);                  //短延时，其实不延时也没事
			HAL_TIM_Base_Start_IT(&htim4);  //启动 定时器
 			keyOrder[0] ++ ;
 			keyOrder[keyOrder[0]] = 0 ;
 			
		}
		keyTim[keyOrder[0]] ++ ;
		HAL_Delay(1) ;
	}
	else
	{
		led1(1)
		if(Key1_flag==0)                  //按键之前有按下
		{
			Key1_flag=1;                    //置一，为按键按下做准备
			HAL_TIM_Base_Stop_IT(&htim4);
		}
	}

	if(!Key2 )                             //下面是一样的，一共是八个音乐
	{
 		if(Key2_flag==1)
		{
			Key2_flag = 0;
			Fre = tone[diao * 7  + 1 ];
			MX_TIM4_Init();
			HAL_TIM_Base_Start_IT(&htim4);
			led2(0)
 			keyOrder[0] ++ ;
 			keyOrder[keyOrder[0]] = 1 ;
 		}
		keyTim[keyOrder[0]] ++ ;
		HAL_Delay(1) ;

	}
	else
	{
		led2(1)
		if(Key2_flag==0)
		{
			Key2_flag=1;
			HAL_TIM_Base_Stop_IT(&htim4);
		}
	}


	if(!Key3 )
	{
 		if(Key3_flag==1)
		{
			Key3_flag = 0;
			Fre = tone[diao * 7  + 2 ];
			MX_TIM4_Init();

			HAL_TIM_Base_Start_IT(&htim4);
			led3(0)
 			keyOrder[0] ++ ;
 			keyOrder[keyOrder[0]] = 2 ;


		}
		keyTim[keyOrder[0]] ++ ;
		HAL_Delay(1) ;

	}
	else
	{
		led3(1)
		if(Key3_flag==0)
		{
			Key3_flag=1;
			HAL_TIM_Base_Stop_IT(&htim4);
		}
	}
	if( !Key4  )
	{
 		if(Key4_flag==1)
		{
			Key4_flag = 0;
			Fre = tone[diao * 7  + 3 ];
			MX_TIM4_Init();
			HAL_TIM_Base_Start_IT(&htim4);
			led4(0)
 			keyOrder[0] ++ ;
 			keyOrder[keyOrder[0]] = 3 ;

		}
		HAL_Delay(1) ;
		keyTim[keyOrder[0]] ++ ;
	}
	else
	{
		led4(1)
		if(Key4_flag==0)
		{
			Key4_flag=1;
			HAL_TIM_Base_Stop_IT(&htim4);
		}
	}


	if( !Key5 )
	{
 		if(Key5_flag==1)
		{
			Key5_flag = 0;
			led5(0)
			Fre = tone[diao * 7  + 4 ];
			MX_TIM4_Init();
			HAL_TIM_Base_Start_IT(&htim4);
 			keyOrder[0] ++ ;
 			keyOrder[keyOrder[0]] = 4 ;
 
		}
		HAL_Delay(1) ;
		keyTim[keyOrder[0]] ++ ;
	}
	else
	{
		if(Key5_flag==0)
		{
			led5(1)
			Key5_flag=1;
			HAL_TIM_Base_Stop_IT(&htim4);
		}
	}

	if(!Key6  )
	{
 		if(Key6_flag==1)
		{
			Key6_flag = 0;
			led6(0)
			Fre = tone[diao * 7  + 5 ];
			MX_TIM4_Init();
			HAL_TIM_Base_Start_IT(&htim4);
 			keyOrder[0] ++ ;
 			keyOrder[keyOrder[0]] = 5 ;


		}
		keyTim[keyOrder[0]] ++ ;
		HAL_Delay(1) ;
	}
	else
	{
		led6(1)
		if(Key6_flag==0)
		{
			Key6_flag=1;
			HAL_TIM_Base_Stop_IT(&htim4);
		}
	}


	if(!Key7 )
	{
 		if(Key7_flag==1)
		{
			led7(0)
			Key7_flag = 0;
			Fre = tone[diao * 7  + 6 ];
			MX_TIM4_Init();
			HAL_TIM_Base_Start_IT(&htim4);
 			keyOrder[0] ++ ;
 			keyOrder[keyOrder[0]] = 6 ;


		}
		keyTim[keyOrder[0]] ++ ;
		HAL_Delay(1) ;
 	}
	else
	{
		led7(1)
		if(Key7_flag==0)
		{
			Key7_flag=1;
			HAL_TIM_Base_Stop_IT(&htim4);
		}
	}

	if(!Key8    )
	{
 		if(Key8_flag==1)
		{
			Key8_flag = 0;
// 				 Fre = tone[15]; MX_TIM4_Init();
			HAL_TIM_Base_Start_IT(&htim4);
			songNum = 0 ;
			if(state == 1 )
			voiceNum = (voiceNum + 1) % 4  ;
			state = 1 ;
		}
	}
	else
	{
 		if(Key8_flag==0)
		{
			Key8_flag=1;
//			HAL_TIM_Base_Stop_IT(&htim4);
		}
	}
	if(!Key9  )
	{
		if(Key9_flag==1)
		{
			Key9_flag = 0;
			key9F = 1 ;
			for(uint16_t i = 1 ; i <= keyOrder[0] ; i ++  )
			{
 				Fre = tone[diao * 7  + keyOrder[i] ];
				MX_TIM4_Init();
				HAL_TIM_Base_Start_IT(&htim4);
 				uint32_t TS = keyTim[i] ;
 				DisFunction(Dis_Data[keyOrder[i]+1]) ;
				
				while(TS)
				{
					TS -- ;
					delayus(120) ;
					HAL_Delay(1) ;
 				}
 				HAL_TIM_Base_Stop_IT(&htim4);
				HAL_Delay(50) ;

			
			} 
//			diao = (diao + 1 )% 3 ;
		}
	}
	else
	{
		Key9_flag = 1;
	}
	if(Key1_flag == 0 ||Key2_flag == 0 ||Key3_flag == 0 ||Key4_flag == 0 ||Key5_flag == 0 ||Key6_flag == 0 ||Key7_flag == 0 ||Key8_flag == 0 )  //任意一个按键按下
	{
		if(Key1_flag==0)       DisFunction(Dis_Data[1]);
		else  if(Key2_flag==0) DisFunction(Dis_Data[2]);
		else  if(Key3_flag==0) DisFunction(Dis_Data[3]);
		else  if(Key4_flag==0) DisFunction(Dis_Data[4]);
		else  if(Key5_flag==0) DisFunction(Dis_Data[5]);
		else  if(Key6_flag==0) DisFunction(Dis_Data[6]);
		else  if(Key7_flag==0) DisFunction(Dis_Data[7]);
		else  if(Key8_flag==0) DisFunction(Dis_Data[8]);
		else                   DisFunction(Dis_Data[10]);  //谁按下就驱动数码管显示对应的数据，否则灯灭



	}
	else
	{
		DisFunction(Dis_Data[10]);
		if(state == 0 )  //都没按下
		{
			Sound(0);
			songNum=0;
			HAL_TIM_Base_Stop_IT(&htim4);
		}
	}	

}





void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  //定时器中断回调
{

	static uint16_t timCount = 0 ;
	if(htim==&htim1)     //是定时器 1 产生的中断
	{
		timCount = (timCount +  1)%10000 ;

		if(timCount%3 == 0 && state)
		{
			voiceCount++;
			if(voiceCount>=Len[voiceNum ][songNum])
			{
				voiceCount=0;
				songNum++;
				if(Len[voiceNum ][songNum]==255|Song[voiceNum ][songNum]==255)
				{
					songNum=0;
					state=0;
					HAL_TIM_Base_Stop_IT(&htim4);

				}
				Fre = tone[Song[voiceNum ][songNum]+2];
				MX_TIM4_Init();
			}

		}
 
		
		

	}




	if(htim==&htim4)     //是定时器 4 产生的中断
	{
		SoundFlag =! SoundFlag ;
		Sound(SoundFlag) ;
	}





}






/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_TIM4_Init();
	MX_TIM1_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim1);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

		if(state==1)
		{
			if(stateF == 1 )
			{
				stateF = 0 ;
				HAL_TIM_Base_Start_IT(&htim4);
				Fre = tone[Song[voiceNum][songNum]+2];
				MX_TIM4_Init();

			}
		}
		else
		{
			if(stateF == 0 )
			{
				stateF = 1 ;
				HAL_TIM_Base_Stop_IT(&htim4);
			}
		}

		Key_Dispose();         //按键处理函数

	}
	/* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	* in the RCC_OscInitTypeDef structure.
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	   tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
