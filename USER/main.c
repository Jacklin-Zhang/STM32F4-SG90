#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"

//   0.5ms--------------0度；
//   1.0ms------------45度；
//   1.5ms------------90度；
//   2.0ms-----------135度；
//   2.5ms-----------180度；

int servo_angle , servo_temp;

void setServoAngle(int angle)
{

if(angle>180)
angle=180;
else if(angle<0)
angle=0;

servo_temp=angle*200/180+50;//计算占空比

TIM_SetCompare1(TIM3,servo_temp);

//计算延迟时间
servo_temp=servo_angle-angle;
if(servo_temp<0)
servo_temp=-servo_temp;
servo_temp=servo_temp*3+10;

//USART_SendNumber(USART1,angle);
delay_ms(servo_temp);

servo_angle=angle;

}

int main()
{	  
	TIM3_CH1_PWM(180);	 
	
	while(1)
	{
		
		setServoAngle(150);
	}
}
