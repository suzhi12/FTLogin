// LoginMain.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "LoginMain.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);                 //实例句柄与渲染类关联
	
	CLogin FTNN_LOGIN;
	FTNN_LOGIN.Create(NULL, _T("FTNN_LOGIN"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE, 0, 0, 657, 402);     //注册窗口 注册超类 -注册窗口类-创建窗口-handlemessage（WM_CREATE消息处理）
	FTNN_LOGIN.CenterWindow();
	//FTNN_LOGIN.ShowModal();
	CPaintManagerUI::MessageLoop();                           //处理消息循环


}



