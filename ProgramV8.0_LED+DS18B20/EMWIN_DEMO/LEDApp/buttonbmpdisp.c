#include "GUI.h"
#include "DIALOG.h"
#include "BUTTON.h"

#include "buttonbmp.h"
#include "buttonbmpdisp.h"

#include "led.h"
 	

#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0 (GUI_ID_USER + 0x01)
#define ID_BUTTON_1 (GUI_ID_USER + 0x02)
#define ID_TEXT_0 (GUI_ID_USER + 0x03)
#define ID_TEXT_1 (GUI_ID_USER + 0x04)

#define ID_BUTTON_2 (GUI_ID_USER + 0x05)
#define ID_BUTTON_3 (GUI_ID_USER + 0x06)
#define ID_TEXT_2 (GUI_ID_USER + 0x07)
#define ID_TEXT_3 (GUI_ID_USER + 0x08)

GUI_BITMAP buttonbmp_tab[2];

//对话框资源表
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = 
{
	{ FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 480, 320, 0, 0x64, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 105, 60, 110, 40, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 105, 140, 110, 40, 0, 0x0, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_0, 25, 70, 80, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_1, 25, 150, 80, 20, 0, 0x64, 0 },

	{ TEXT_CreateIndirect, "Text", ID_TEXT_2, 240, 70, 80, 20, 0, 0x64, 0 },
	{ TEXT_CreateIndirect, "Text", ID_TEXT_3, 240, 150, 80, 20, 0, 0x64, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 320, 60, 110, 40, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_BUTTON_3, 320, 140, 110, 40, 0, 0x0, 0 },
};

WM_HWIN hWin1;

//对话框回调函数
static void _cbDialog(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	int     NCode;
	int     Id;


	switch (pMsg->MsgId) 
	{
		case WM_PAINT:
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			break;
		case WM_INIT_DIALOG:
			//初始化对话框
			hItem = pMsg->hWin;
			FRAMEWIN_SetTitleHeight(hItem, 30);
			FRAMEWIN_SetText(hItem, "LED");
			FRAMEWIN_SetFont(hItem, GUI_FONT_24_ASCII);
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetTextColor(hItem, 0x0000FFFF);
			FRAMEWIN_AddCloseButton(hItem,FRAMEWIN_BUTTON_RIGHT,2); //添加关闭按钮
		
			//初始化BUTTON0
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetBitmapEx(hItem,0,&buttonbmp_tab[0],0,0);
			BUTTON_SetText(hItem, "");
			
			//初始化BUTTON1
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
			BUTTON_SetBitmapEx(hItem,0,&buttonbmp_tab[0],0,0);
			BUTTON_SetText(hItem, "");

			//初始化BUTTON2
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
			BUTTON_SetBitmapEx(hItem, 0, &buttonbmp_tab[0], 0, 0);
			BUTTON_SetText(hItem, "");

			//初始化BUTTON3
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
			BUTTON_SetBitmapEx(hItem, 0, &buttonbmp_tab[0], 0, 0);
			BUTTON_SetText(hItem, "");
			
			//初始化TEXT0
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32_ASCII);
			TEXT_SetText(hItem, "LED1:");
			
			//初始化TEXT1
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32_ASCII);
			TEXT_SetText(hItem, "LED2:");

			//初始化TEXT2
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32_ASCII);
			TEXT_SetText(hItem, "LED3:");

			//初始化TEXT3
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
			TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_32_ASCII);
			TEXT_SetText(hItem, "LED4:");
			break;
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{
				case ID_BUTTON_0: //BUTTON_0的通知代码，控制LED0
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED: //按钮被按下并释放
							LED0 = !LED0;
							BUTTON_SetBitmapEx(hItem,0, LED0 ?&buttonbmp_tab[1]:&buttonbmp_tab[0],0,0);
							break;	
					}
					break;
				case ID_BUTTON_1: //BUTTON_1的通知代码，控制LED1
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
							break;
						case WM_NOTIFICATION_RELEASED:
							LED1 = !LED1;
                            BUTTON_SetBitmapEx(hItem,0, LED1 ?&buttonbmp_tab[0]:&buttonbmp_tab[1],0,0);
							break;
					}
					break;
				case ID_BUTTON_2: //BUTTON_2的通知代码，控制LED2
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
					switch (NCode)
					{
					case WM_NOTIFICATION_CLICKED:
						break;
					case WM_NOTIFICATION_RELEASED:
						LED2 = !LED2;
						BUTTON_SetBitmapEx(hItem, 0, LED2 ? &buttonbmp_tab[0] : &buttonbmp_tab[1], 0, 0);
						break;
					}
					break;
				case ID_BUTTON_3: //BUTTON_3的通知代码，控制LED3
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
					switch (NCode)
					{
					case WM_NOTIFICATION_CLICKED:
						break;
					case WM_NOTIFICATION_RELEASED:
						LED3 = !LED3;
						BUTTON_SetBitmapEx(hItem, 0, LED3 ? &buttonbmp_tab[0] : &buttonbmp_tab[1], 0, 0);
						break;
					}
					break;
			}
			break;
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}

//创建一个对话框
WM_HWIN CreateFramewin(void) 
{
	WM_HWIN hWin;
	buttonbmp_tab[0]=bmBUTTONOFF;
	buttonbmp_tab[1]=bmBUTTONON;
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	return hWin;
}

//BUTTON按钮上显示位图
void Buttonbmp_Demo(void)
{
	hWin1=CreateFramewin();
	while(1)
	{
		GUI_Delay(100);
	}
}

































