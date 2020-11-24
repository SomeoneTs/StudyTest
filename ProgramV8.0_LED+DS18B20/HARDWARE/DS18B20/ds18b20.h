#ifndef __DS18B20_H
#define __DS18B20_H
#include "sys.h"


//IO��������
#define DS18B20_IO_IN()  {GPIOF->MODER&=~(3<<(8*2));GPIOF->MODER|=0<<(8*2);}	//PF8����ģʽ
#define DS18B20_IO_OUT() {GPIOF->MODER&=~(3<<(8*2));GPIOF->MODER|=1<<(8*2);} 	//PF8���ģʽ
 
////IO��������											   
#define	DS18B20_DQ_OUT PFout(8) //���ݶ˿�	PF8
#define	DS18B20_DQ_IN  PFin(8)  //���ݶ˿�	PF8 
   	
u8 DS18B20_Init(void);			//��ʼ��DS18B20
short DS18B20_Get_Temp(void);	//��ȡ�¶�
void DS18B20_Start(void);		//��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);		//����һ���ֽ�
u8 DS18B20_Read_Bit(void);		//����һ��λ
u8 DS18B20_Check(void);			//����Ƿ����DS18B20
void DS18B20_Rst(void);			//��λDS18B20 
#endif
