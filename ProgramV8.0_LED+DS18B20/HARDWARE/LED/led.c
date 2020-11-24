#include "led.h"


//��ʼ��LED 
//LED0 PI9 
//LED1 PI10
//LED2 PG7
//LED3 PF10
void led_init(void)                       
{
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOI_CLK_ENABLE();           //GPIOIʱ��
	__HAL_RCC_GPIOG_CLK_ENABLE();           //GPIOGʱ��
	__HAL_RCC_GPIOF_CLK_ENABLE();           //GPIOFʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_9|GPIO_PIN_10;   //PIN9|PIN10
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;     //�������
    GPIO_Initure.Pull=GPIO_PULLUP;             //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;        //����
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_7;            //PIN7
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_10;            //PIN10
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_9,GPIO_PIN_SET);	   //��ʼ�����Ĭ����Ϊ1��LED��Ϩ��
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_10,GPIO_PIN_SET);	 
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_7,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_SET);
}
