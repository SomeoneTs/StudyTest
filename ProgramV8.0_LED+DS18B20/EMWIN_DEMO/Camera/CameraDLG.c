

#include "DIALOG.h"
#include "CameraDLG.h"
#include "sys.h"
#include "dcmi.h"
#include "tftlcd.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0  (GUI_ID_USER + 0x00)
#define ID_BUTTON_0  (GUI_ID_USER + 0x01)
#define ID_BUTTON_1  (GUI_ID_USER + 0x02)
#define ID_BUTTON_2  (GUI_ID_USER + 0x03)
#define ID_BUTTON_3  (GUI_ID_USER + 0x04)
#define ID_BUTTON_4  (GUI_ID_USER + 0x05)


// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Camera", ID_FRAMEWIN_0, 0, 0, 480, 320, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "", ID_BUTTON_0, 0, 0, 400, 300, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 410, 30, 50, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 410, 99, 50, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_3, 410, 167, 50, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_4, 410, 238, 50, 30, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)

vu8 bmp_request=0;						//bmp拍照请求:0,无bmp拍照请求;1,有bmp拍照请求,需要在帧中断里面,关闭DCMI接口.
u8 ovx_mode=0;							//bit0:0,RGB565模式;1,JPEG模式 
u16 curline=0;							//摄像头输出数据,当前行编号
u16 yoffset=0;							//y方向的偏移量

#define jpeg_buf_size   4*1024*1024		//定义JPEG数据缓存jpeg_buf的大小(4M字节)
#define jpeg_line_size	2*1024			//定义DMA接收数据时,一行数据的最大值

u32 *dcmi_line_buf[2];					//RGB屏时,摄像头采用一行一行读取,定义行缓存  
u32 *jpeg_data_buf;						//JPEG数据缓存buf 

volatile u32 jpeg_data_len=0; 			//buf中的JPEG有效数据长度 
volatile u8 jpeg_data_ok=0;				//JPEG数据采集完成标志 
										//0,数据没有采集完;
										//1,数据采集完了,但是还没处理;
										//2,数据已经处理完成了,可以开始下一帧接收

void jpeg_data_process(void)
{
	u16 i;
	u16 rlen;			//剩余数据长度
	u32 *pbuf;
	curline=yoffset;	//行数复位
	if(ovx_mode&0X01)	//只有在JPEG格式下,才需要做处理.
	{
		if(jpeg_data_ok==0)	//jpeg数据还未采集完?
		{
			__HAL_DMA_DISABLE(&DMADMCI_Handler);//关闭DMA
			while(DMA2_Stream1->CR&0X01);	//等待DMA2_Stream1可配置 
			rlen=jpeg_line_size-__HAL_DMA_GET_COUNTER(&DMADMCI_Handler);//得到剩余数据长度	
			pbuf=jpeg_data_buf+jpeg_data_len;//偏移到有效数据末尾,继续添加
			if(DMADMCI_Handler.Instance->CR&(1<<19))for(i=0;i<rlen;i++)pbuf[i]=dcmi_line_buf[1][i];//读取buf1里面的剩余数据
			else for(i=0;i<rlen;i++)pbuf[i]=dcmi_line_buf[0][i];//读取buf0里面的剩余数据 
			jpeg_data_len+=rlen;			//加上剩余长度
			jpeg_data_ok=1; 				//标记JPEG数据采集完按成,等待其他函数处理
		}
		if(jpeg_data_ok==2)	//上一次的jpeg数据已经被处理了
		{
            __HAL_DMA_SET_COUNTER(&DMADMCI_Handler,jpeg_line_size);	//传输长度为jpeg_buf_size*4字节
			__HAL_DMA_ENABLE(&DMADMCI_Handler); //打开DMA
			jpeg_data_ok=0;					//标记数据未采集
			jpeg_data_len=0;				//数据重新开始
		}
	}else
	{  
		if(bmp_request==1)	//有bmp拍照请求,关闭DCMI
		{
			DCMI_Stop();	//停止DCMI
			bmp_request=0;	//标记请求处理完成.
		}
		LCD_SetCursor(0,0);  
		LCD_WriteRAM_Prepare();				//开始写入GRAM  
	}  
} 
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Camera'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    FRAMEWIN_SetTitleHeight(hItem, 13);
    FRAMEWIN_SetFont(hItem, GUI_FONT_20_ASCII);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by ''
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_3: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_4: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateCamera
*/

WM_HWIN CreateCamera(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
