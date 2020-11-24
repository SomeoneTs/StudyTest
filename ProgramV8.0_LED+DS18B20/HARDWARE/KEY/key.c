#include "key.h"


void key_init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOI_CLK_ENABLE();           //GPIOI时钟
	__HAL_RCC_GPIOE_CLK_ENABLE();           //GPIOG时钟
	
    GPIO_Initure.Pin=GPIO_PIN_7|GPIO_PIN_11;   //PIN7|PIN11
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;     //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;             //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;        //高速
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_5;    //PIN3|PIN5
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_7,GPIO_PIN_SET);	   //初始化完后都默认置为1
	HAL_GPIO_WritePin(GPIOI,GPIO_PIN_11,GPIO_PIN_SET);	 
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);
}


