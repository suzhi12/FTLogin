// LoginMain.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "LoginMain.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);                 //ʵ���������Ⱦ�����
	
	CLogin FTNN_LOGIN;
	FTNN_LOGIN.Create(NULL, _T("FTNN_LOGIN"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE, 0, 0, 657, 402);     //ע�ᴰ�� ע�ᳬ�� -ע�ᴰ����-��������-handlemessage��WM_CREATE��Ϣ����
	FTNN_LOGIN.CenterWindow();
	//FTNN_LOGIN.ShowModal();
	CPaintManagerUI::MessageLoop();                           //������Ϣѭ��


}



