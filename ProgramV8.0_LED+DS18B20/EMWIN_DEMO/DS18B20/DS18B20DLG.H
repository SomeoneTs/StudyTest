#ifndef _DS18B20DLG_H_
#define _DS18B20DLG_H_

#include "GUI.h"
#include "DIALOG.h"



#define BORDER_TOP        	10
#define BORDER_BOTTOM     	20
#define BORDER_LEFT       	40
#define BORDER_RIGHT      	10
#define VERMULTIPLE         (10)        //垂直刻度缩放因子


static GRAPH_SCALE_Handle hScaleV;   	//垂直刻度句柄 
static GRAPH_SCALE_Handle hScaleH;   	//水平刻度句柄



typedef struct
{
	int* buffer;				        //温度数据存放区
	U8 	temflag;					    //是否采集温度标志
	int dataxsize, dataysize;	        //示波器数据区X,Y大小
	U8 	linecolorindex, backcolorindex;	//线条颜色索引值和背景颜色索引值
	GUI_COLOR linecolor, backcolor;		//线条颜色和背景颜色
	GRAPH_DATA_Handle  graphdata; 	    //GRAHP_DATA的数据句柄
	int div;					        //一格代表几秒
	float resolut;                      //每个AD原始值代表多高的温度(单位为℃)
}temperature;

extern temperature tem;

WM_HWIN CreateDS18B20(void);


#endif
