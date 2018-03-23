#include <UIlib.h>
#include <string>
#include <map>
#include "stdafx.h"

using namespace DuiLib;
#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif

//һЩͼƬ��
#define CLOSE_NORMAL L"E:\\project\\LoginMain\\res\\close.png"
#define CLOSE_HOT L"E:\\project\\LoginMain\\res\\close_h.png"
#define CLOSE_PUSH L"E:\\project\\LoginMain\\res\\close_p.png"
#define LOGIN_BANNER L"E:\\project\\LoginMain\\res\\Login_Banner.png"
#define WHITE_LOGIN L"E:\\project\\LoginMain\\res\\white.png"
#define LOGIN_BTN_NOR L"E:\\project\\LoginMain\\res\\Login_Btn_nor.png"
#define LOGIN_BTN_PUSH L"E:\\project\\LoginMain\\res\\Login_Btn_over.png"
#define CHECKED L"E:\\project\\LoginMain\\res\\checked.png"
#define UNCHECKED L"E:\\project\\LoginMain\\res\\unchecked.png"
#define MINIMIZE L"E:\\project\\LoginMain\\res\\minimize_h.png"
#define TOOLS_BTN_NORMAL L"E:\\project\\LoginMain\\res\\Tools.png"
#define TOOLS_BTN_PUSH L"E:\\project\\LoginMain\\res\\Tools_h.png"

#define COMBO_NOR L"E:\\project\\LoginMain\\res\\black_sanjiao.png"
#define COMBO_OVER L"E:\\project\\LoginMain\\res\\cheng_sanjiao.png"

#define LINE_NOR L"E:\\project\\LoginMain\\res\\blackline.png"
#define LINE_OVER L"E:\\project\\LoginMain\\res\\chengline.png"

#define LEFT_COMBO_NOR L"E:\\project\\LoginMain\\res\\left_black_sanjiao.png"
#define LEFT_COMBO_OVER L"E:\\project\\LoginMain\\res\\left_cheng_sanjiao.png"

//��������url
#define FORGET_PSW L"https://www.futu5.com/account/forgetpsw?url=12011&clienttype=10&clientver=3.49&clientpos=1"


//�˺����
class Configution
{
public:
	Configution();
	~Configution();

public:
	void SaveConfig(wstring account, wstring key);
	map<wstring, wstring> ReadConfig();

	std::wstring GetKeyid(std::wstring Account);

private:
	map<wstring, wstring> m_Account;
};

//CLogin
class CLogin : public WindowImplBase
{
public:
	CLogin();
	~CLogin();

	virtual CDuiString GetSkinFolder() { return _T("Res"); }
	virtual CDuiString GetSkinFile() { return _T("main.xml"); }
	virtual LPCTSTR GetWindowClassName() const { return _T("DUIMainFrame"); }
	virtual void    Notify(TNotifyUI& msg);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void InitWindow();
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void AddListElement();
public:
	//̫�෱���Ĵ����ؼ��Ĵ��룬�򵥷�װ��
	template <typename T>
	T* CreateDefBotton( CDuiString name, CDuiString Attribute, CDuiString BkImage = L"", CDuiString ToolTip = L"", CDuiString Text = L"")
	{
		T *Button = new T;
		Button->SetName(name.GetData());
		Button->SetAttribute(L"pos", Attribute.GetData());
		Button->SetFloat(true);
		if (BkImage.GetLength() != 0)
		{
			Button->SetBkImage(BkImage.GetData());
		}
		if (ToolTip.GetLength() != 0)
		{
			Button->SetToolTip(ToolTip.GetData());
		}
		if (Text.GetLength() != 0)
		{
			Button->SetText(Text.GetData());
		}

		m_hlt_bg->Add(Button);

		return Button;
	}
private:
	CRenderEngine* m_CRender;

	Configution* m_Config;

	CHorizontalLayoutUI *m_hlt_bg;

	bool m_status;

	//�����ֻ����ʱ�»��߱��ɫ����ֵ��true
	bool m_MouseLine1;
};



