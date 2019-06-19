#include "pwm.h"
#include "led.h"
#include "usart.h"
 
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F4¹¤³ÌÄ£°å-¿âº¯Êý°æ±¾
//ÌÔ±¦µêÆÌ£ºhttp://mcudev.taobao.com								  
////////////////////////////////////////////////////////////////////////////////// 	 
extern int servo_angle;

//TIM3 PWM²¿·Ö³õÊ¼»¯ 
//PWMÊä³ö³õÊ¼»¯
//arr£º×Ô¶¯ÖØ×°Öµ
//psc£ºÊ±ÖÓÔ¤·ÖÆµÊý
void TIM3_CH1_PWM(u16 servoInitAngle)
{	
	
	//´Ë²¿·ÖÐèÊÖ¶¯ÐÞ¸ÄIO¿ÚÉèÖÃ
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3Ê±ÖÓÊ¹ÄÜ    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//Ê¹ÄÜPORTAÊ±ÖÓ	
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3); //GPIOA6¸´ÓÃÎª¶¨Ê±Æ÷3
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOFA
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //¸´ÓÃ¹¦ÄÜ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//ËÙ¶È100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //ÍÆÍì¸´ÓÃÊä³ö
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //ÉÏÀ­
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //³õÊ¼»¯PA6
	  
	
	TIM_TimeBaseStructure.TIM_Prescaler=839;  //¶¨Ê±Æ÷·ÖÆµ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //ÏòÉÏ¼ÆÊýÄ£Ê½
	TIM_TimeBaseStructure.TIM_Period=2000;   //×Ô¶¯ÖØ×°ÔØÖµ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//³õÊ¼»¯¶¨Ê±Æ÷3
	
	//³õÊ¼»¯TIM14 Channel1 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //Êä³ö¼«ÐÔ:TIMÊä³ö±È½Ï¼«ÐÔµÍ
	TIM_OCInitStructure.TIM_Pulse = servoInitAngle*200/180+50;//è„‰å®½å€¼
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //¸ù¾ÝTÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯ÍâÉèTIM1 4OC1

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR1ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
 
  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEÊ¹ÄÜ 
	
	TIM_Cmd(TIM3, ENABLE);  //Ê¹ÄÜTIM3
 
	servo_angle=servoInitAngle;									  
}  


