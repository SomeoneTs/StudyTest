#include "DIALOG.h"
#include "DS18B20DLG.h"
#include "ds18b20.h"



#define ID_FRAMEWIN_0        (GUI_ID_USER + 0x00)
#define ID_GRAPH_0        (GUI_ID_USER + 0x01)
#define ID_BUTTON_0        (GUI_ID_USER + 0x02)
#define ID_BUTTON_1        (GUI_ID_USER + 0x03)


temperature tem;
GUI_COLOR LineColor[] = { GUI_RED,GUI_BLACK,GUI_WHITE,GUI_YELLOW,GUI_BLUE,GUI_DARKMAGENTA };
GUI_COLOR BackColor[] = { GUI_BLACK,GUI_LIGHTRED,GUI_DARKMAGENTA,GUI_WHITE,GUI_GREEN };


static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "DS18B20", ID_FRAMEWIN_0, 0, 0, 480, 320, 0, 0x64, 0 },
  { GRAPH_CreateIndirect, "Graph", ID_GRAPH_0, 0, 0, 469, 243, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "START", ID_BUTTON_0, 189, 256, 80, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "END", ID_BUTTON_1, 337, 256, 80, 20, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};



static void _cbDialog(WM_MESSAGE* pMsg) {
	WM_HWIN hItem;
	int     NCode;
	int     Id;
	// USER START (Optionally insert additional variables)
	// USER END

	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:
		//
		// Initialization of 'DS18B20'
		//
		hItem = pMsg->hWin;
		FRAMEWIN_SetTitleHeight(hItem, 25);
		FRAMEWIN_SetText(hItem, "DS18B20");
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		FRAMEWIN_SetFont(hItem, GUI_FONT_20_ASCII);
		FRAMEWIN_AddCloseButton(hItem, FRAMEWIN_BUTTON_RIGHT, 2); //��ӹرհ�ť
		// USER START (Optionally insert additional code for further widget initialization)
		// USER END
		hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
		tem.linecolorindex = 0;	        //����Ĭ�Ϻ�ɫ
		tem.backcolorindex = 2;	        //����Ĭ�Ϻ�ɫ
		tem.linecolor = LineColor[tem.linecolorindex];
		tem.backcolor = BackColor[tem.backcolorindex];
		tem.graphdata = GRAPH_DATA_YT_Create(tem.linecolor, 600, 0, 0);  //����YT���ݶ���
		GRAPH_AttachData(hItem, tem.graphdata);		                    //�����ݶ�����ӵ�GRAPH�ؼ���
		GRAPH_SetBorder(hItem, BORDER_LEFT, BORDER_TOP, BORDER_RIGHT, BORDER_BOTTOM);//���ñ߽�
		GRAPH_SetGridDistX(hItem, 50);		//����ˮƽ������
		GRAPH_SetGridDistY(hItem, 20);		//���ô�ֱ������
		GRAPH_SetGridVis(hItem, 1);			//��������ɼ�

		hScaleV = GRAPH_SCALE_Create(35, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 20); //���ƴ�ֱ�̶�
		GRAPH_SCALE_SetTextColor(hScaleV, GUI_YELLOW);
		GRAPH_AttachScale(hItem, hScaleV);   //���̶ȶ��󸽼ӵ�ͼ��С����
		GRAPH_SCALE_SetFactor(hScaleV, 0.5);  //���ÿ̶�ϵ��
		GRAPH_SCALE_SetOff(hScaleV, 100);    //��ֱ�̶������ƶ�100�����ص㣬������ֱ�̶Ȼ��и�ֵ

		hScaleH = GRAPH_SCALE_Create(230, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 50);//����ˮƽ�̶�
		GRAPH_SCALE_SetTextColor(hScaleH, GUI_DARKGREEN);
		GRAPH_AttachScale(hItem, hScaleH);   //���̶ȶ��󸽼ӵ�ͼ��С����
		GRAPH_SCALE_SetFactor(hScaleH, 0.1);  //���ÿ̶�ϵ��

		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id) {
		case ID_BUTTON_0: // Notifications sent by 'START'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				tem.temflag = 1;
				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_1: // Notifications sent by 'CANCLE'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				tem.temflag = 0;
				//hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
				//GRAPH_DetachData(hItem, tem.graphdata);//�ȷ�������
				//GRAPH_DATA_YT_Delete(tem.graphdata);	//ɾ�����������ݶ���
				//tem.graphdata = GRAPH_DATA_YT_Create(tem.linecolor, 600, 0, 0);//���´������ݶ���
				//GRAPH_AttachData(hItem, tem.graphdata);
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
		// USER END+
	case WM_DELETE:
		hItem = pMsg->hWin;
		tem.temflag = 0;
		GUI_EndDialog(hItem,0);
		break;
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
*       CreateDS18B20
*/
WM_HWIN CreateDS18B20(void) {
	WM_HWIN hWin, ClientWin;
	int Graph_xSize, Graph_ySize;
	volatile float temp=25.0f;
	DS18B20_Init();
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	ClientWin = WM_GetDialogItem(hWin, ID_GRAPH_0);
	Graph_xSize = WM_GetWindowSizeX(ClientWin);
	Graph_ySize = WM_GetWindowSizeY(ClientWin);
	tem.dataxsize = Graph_xSize - BORDER_LEFT - BORDER_RIGHT - 3;
	tem.dataysize = Graph_ySize - BORDER_TOP - BORDER_BOTTOM - 3;	
	GUI_Exec();
	
	while (1)
	{
		if (tem.temflag == 1)
		{
			temp = (float)DS18B20_Get_Temp() / 10.0f;
			GRAPH_DATA_YT_AddValue(tem.graphdata, (int)(temp / 0.5f) + 100);
		}
		GUI_Delay(100);
	}

	//return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
