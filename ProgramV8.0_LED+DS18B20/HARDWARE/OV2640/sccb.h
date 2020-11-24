#ifndef __SCCB_H
#define __SCCB_H
#include "sys.h"


//IO方向设置
#define SCCB_SDA_IN()  {GPIOA->MODER&=~(3<<(1*2));GPIOA->MODER|=0<<(1*2);}	  //PA1输入模式
#define SCCB_SDA_OUT() {GPIOA->MODER&=~(3<<(1*2));GPIOA->MODER|=1<<(1*2);}    //PA1输出模式

//IO操作
#define SCCB_SCL        PCout(1)    //SCL
#define SCCB_SDA        PAout(1)    //SDA 
#define SCCB_READ_SDA   PAin(1)     //输入SDA   

#define SCCB_ID   			0X60    //OV2640的ID

///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_RD_Byte(void);
u8 SCCB_WR_Reg(u8 reg,u8 data);
u8 SCCB_RD_Reg(u8 reg);
#endif













