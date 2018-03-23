#include <UIlib.h>
#include <string>
#include "stdafx.h"
#include "Login.h"

Configution::Configution(){}
Configution::~Configution(){}

void Configution::SaveConfig(std::wstring Account, std::wstring key)
{
	if (m_Account.count(Account) == 0)   //�˺Ų����ڣ�����
	{
		m_Account.insert(pair<std::wstring, std::wstring>(Account, key));
	}
	else
	{
		auto iter = m_Account.find(Account);
		iter->second = key;
	}
}

map<wstring, wstring> Configution::ReadConfig()
{
	return m_Account;
}

std::wstring Configution::GetKeyid(std::wstring Account)
{
	auto iter = m_Account.find(Account);
	if (iter == m_Account.end())
	{
		return L"";
	}
	else
	{
		return iter->second;
	}
}


CLogin::CLogin()
{
	m_CRender = new CRenderEngine;
	m_Config = new Configution;
	m_status = true;
	m_MouseLine1 = true;
}

CLogin::~CLogin()
{
	delete m_CRender;
	delete m_Config;
	m_CRender = nullptr;
	m_Config = nullptr;
}

//����ڴ����ƶ�����ͷ�ʱ�����WM_NCHITTEST��Ϣ��OnNcHitTest����һ��ö�٣�������ֵΪHTCAPTIONʱ������ִ���϶�����
LRESULT CLogin::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; 
	pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if ((pt.x >= rcClient.left) && (pt.x <= rcClient.right) && (pt.y >= rcClient.top) && (pt.y <= rcClient.bottom))
	{
		//����������ʱ�������϶�
		if (pt.x <= 375 && pt.x <= 402)
		{
			return HTCAPTION;
		}
		//������Ҳ������ ��Ҫ����ͼ�� ������
		/*else if (pt.x >= 375 && pt.y<= 20)
		{
			return HTCAPTION;
		}*/
	}
	return __super::OnNcHitTest(uMsg, wParam, lParam, bHandled);
}

LRESULT CLogin::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt;
	pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);

	//�����ֻ��ֶ�RECT="558,105,617,130"
	CButtonUI *Line1 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"line1"));
	CButtonUI *Line2 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"line2"));

	CEditUI *Account = static_cast<CEditUI*>(m_PaintManager.FindControl(L"accountedit"));
	CEditUI *KeyId = static_cast<CEditUI*>(m_PaintManager.FindControl(L"keyid"));

	RECT AccountPos = Account->GetPos();
	RECT KeyIdPos = KeyId->GetPos();
	if (pt.x >= 558 && pt.x <= 617 && pt.y>=105 && pt.y<=130 )
	{
		m_MouseLine1 = true;
		Line1->SetBkImage(LINE_OVER);
		Line2->SetBkImage(LINE_NOR);
	}
	else if (pt.x >= AccountPos.left && pt.x <= AccountPos.right && pt.y >= AccountPos.top && pt.y <= AccountPos.bottom)
	{
		Line1->SetBkImage(LINE_OVER);
		Line2->SetBkImage(LINE_NOR);
	}
	else if (pt.x >= KeyIdPos.left && pt.x <= KeyIdPos.right && pt.y >= KeyIdPos.top && pt.y <= KeyIdPos.bottom)
	{
		Line2->SetBkImage(LINE_OVER);
		Line1->SetBkImage(LINE_NOR);
	}
	else
	{
		Line1->SetBkImage(LINE_NOR);
		Line2->SetBkImage(LINE_NOR);
	}

	return __super::OnLButtonDown(uMsg, wParam, lParam, bHandled);
}

LRESULT CLogin::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt;
	pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);


	CButtonUI *Line1 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"line1"));
	CButtonUI *Line2 = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"line2"));
	CEditUI *Account = static_cast<CEditUI*>(m_PaintManager.FindControl(L"accountedit"));
	CEditUI *KeyId = static_cast<CEditUI*>(m_PaintManager.FindControl(L"keyid"));

	if (m_MouseLine1 == true)
	{
		Line1->SetBkImage(LINE_NOR);
	}
	return __super::OnLButtonUp(uMsg, wParam, lParam, bHandled);
}


//����CListLabelElementUI�ؼ�
void CLogin::AddListElement()
{
	CComboUI *Account = static_cast<CComboUI*>(m_PaintManager.FindControl(L"accountcombo"));

	CEditUI *AccountEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(L"accountedit"));
	CEditUI *KeyIdEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(L"keyid"));

	std::wstring TextAccount = AccountEdit->GetText();
	std::wstring TextKeyId = KeyIdEdit->GetText();

	m_Config->SaveConfig(TextAccount, TextKeyId);

	CListLabelElementUI *List = new CListLabelElementUI;
	List->SetText(TextAccount.c_str());
	List->SetFixedWidth(197);
	List->SetName(L"stand");
	List->Select();
	Account->Add(List);
}

void CLogin::Notify(TNotifyUI& msg)
{
	//�رպ���С��
	if (msg.sType == L"click") 
	{
		if (msg.pSender->GetName() == L"closebtn")
		{
			PostQuitMessage(0); 
		}
		else if (msg.pSender->GetName() == L"minbtn")
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		//������
		else if (msg.pSender->GetName() == L"forgetkey")
		{
			ShellExecute(NULL, L"open", msg.pSender->GetUserData().GetData(), NULL, NULL, SW_SHOWNA);
		}
		//��¼�����Ҳ� �����ֻ�------
		else if (msg.pSender->GetName() == L"selecttext")
		{
			CTextUI *SelectText = static_cast<CTextUI*>(m_PaintManager.FindControl(L"selecttext"));
			if (m_status == true)
			{
				m_status = false;
				SelectText->SetText(L"�˺ŵ�½");
				SelectText->SetFocus();
				CComboUI *AccountComboOld = static_cast<CComboUI*>(m_PaintManager.FindControl(L"accountcombo"));
				CEditUI *AccountEditOld = static_cast<CEditUI*>(m_PaintManager.FindControl(L"accountedit"));
				m_hlt_bg->Remove(AccountComboOld, true);
				m_hlt_bg->Remove(AccountEditOld, true);

				//����µĿؼ�
				//�Ҳ��Combo
				CComboUI *RightAccountComboNew = CreateDefBotton<CComboUI>(L"rightaccountcombo", L"400,100,557,130");
				RightAccountComboNew->SetAttribute(_T("normalimage"), COMBO_NOR);
				RightAccountComboNew->SetAttribute(_T("hotimage"), COMBO_OVER);
				RightAccountComboNew->SetAttribute(_T("pushedimage"), COMBO_OVER);

				//����Combo
				CComboUI *LeftAccountComboNew = CreateDefBotton<CComboUI>(L"leftaccountcombo", L"400,100,430,130");
				LeftAccountComboNew->SetAttribute(_T("normalimage"), LEFT_COMBO_NOR);
				LeftAccountComboNew->SetAttribute(_T("hotimage"), LEFT_COMBO_OVER);
				LeftAccountComboNew->SetAttribute(_T("pushedimage"), LEFT_COMBO_OVER);

				CEditUI* pAccountEdit = CreateDefBotton<CEditUI>(L"accountedit", L"431,101,536,129", L"", L"", L"�й�����ֻ���");
				pAccountEdit->SetMaxChar(25);

			}
			else
			{
				m_status = true;
				SelectText->SetText(L"�����ֻ�");
				CComboUI *RightAccountComboOld = static_cast<CComboUI*>(m_PaintManager.FindControl(L"rightaccountcombo"));
				CComboUI *LeftAccountComboOld = static_cast<CComboUI*>(m_PaintManager.FindControl(L"leftaccountcombo"));
				CEditUI *AccountEditOld = static_cast<CEditUI*>(m_PaintManager.FindControl(L"accountedit"));

				m_hlt_bg->Remove(RightAccountComboOld, true);
				m_hlt_bg->Remove(LeftAccountComboOld, true);
				m_hlt_bg->Remove(AccountEditOld, true);

				CComboUI *AccountComboNew = CreateDefBotton<CComboUI>(L"accountcombo", L"400,100,557,130");
				AccountComboNew->SetAttribute(_T("normalimage"), COMBO_NOR);
				AccountComboNew->SetAttribute(_T("hotimage"), COMBO_OVER);
				AccountComboNew->SetAttribute(_T("pushedimage"), COMBO_OVER);


				CEditUI* AccountEditNew = CreateDefBotton<CEditUI>(L"accountedit", L"401,101,536,129", L"", L"", L"ţţ��/��½�ֻ���/����");
				AccountEditNew->SetMaxChar(25);
			}
		}
	}
	//�����¼�����
	else if (msg.sType == L"setfocus")
	{
		//��ý�������Edit
		if (msg.pSender->GetName() == L"accountedit")
		{
			CEditUI *FTNNId = static_cast<CEditUI*>(m_PaintManager.FindControl(L"accountedit"));
			FTNNId->SetText(L"");
			FTNNId = nullptr;
		}
		else if (msg.pSender->GetName() == L"keyid")
		{
			CEditUI *KeyId = static_cast<CEditUI*>(m_PaintManager.FindControl(L"keyid"));
			KeyId->SetText(L"");
			KeyId = nullptr;
		}
		//����Զ���½ͬʱ��ѡ��ס����
		else if (msg.pSender->GetName() == L"autologin")
		{
			CCheckBoxUI* RemKey = static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(L"remkey"));
			RemKey->SetCheck(false);
			RemKey = nullptr;
		}
		//�����������򱣴�����
		else if (msg.pSender->GetName() == L"remkey")
		{
			AddListElement();
		}
	}
	//if (msg.sType == L"dropdown")   //bug stand ������
	if (msg.pSender->GetName() == L"stand")
	{
		//MessageBoxW(m_hWnd, msg.sType, msg.sType,NULL);
		CEditUI *FTNNId = static_cast<CEditUI*>(m_PaintManager.FindControl(L"accountedit"));
		CEditUI *KeyId = static_cast<CEditUI*>(m_PaintManager.FindControl(L"keyid"));

		std::wstring TextAccount = msg.pSender->GetText();
		std::wstring TextKeyId = m_Config->GetKeyid(TextAccount);
		FTNNId->SetText(TextAccount.c_str());
		KeyId->SetText(TextKeyId.c_str());
	}

	//�˺ſ�������Ϊ��ʱ�Ļָ�ԭ״
	if (msg.pSender->GetName() == L"accountedit")
	{
		CEditUI *KeyId = static_cast<CEditUI*>(m_PaintManager.FindControl(L"keyid"));
		
		if (KeyId->GetText() == L"")
		{
			KeyId->SetText(L"��¼����");
		}
		KeyId = nullptr;
	}
	else if (msg.pSender->GetName() == L"keyid")
	{
		CEditUI *FTNNId = static_cast<CEditUI*>(m_PaintManager.FindControl(L"accountedit"));

		if (FTNNId->GetText() == L"")
		{
			FTNNId->SetText(L"ţţ��/��½�ֻ���/����");
		}
		FTNNId = nullptr;
	}
}



void CLogin::InitWindow()
{
	m_hlt_bg = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(L"hlt_bg"));
	//���ţţͼƬ����
	CControlUI *LeftButton = CreateDefBotton<CControlUI>(L"leftbtn", L"0,0,375,402", LOGIN_BANNER);

	//�Ҳ�հ�ͼƬ����
	CControlUI *RightButton = CreateDefBotton<CControlUI>(L"rightbtn", L"375,0,657,402", WHITE_LOGIN);

	//�رհ�ť
	CButtonUI *CloseButton = CreateDefBotton<CButtonUI>(L"closebtn", L"627,0,657,20", L"", L"close");
	CloseButton->SetAttribute(L"normalimage", CLOSE_NORMAL);
	CloseButton->SetAttribute(L"hotimage", CLOSE_HOT);
	CloseButton->SetAttribute(L"pushedimage", CLOSE_PUSH);

	//��С����ť
	CButtonUI *MinButton = CreateDefBotton<CButtonUI>(L"minbtn", L"597,0,627,20", MINIMIZE, L"minimize");

	//���ð�ť
	CButtonUI *SettingButton = CreateDefBotton<CButtonUI>( L"settingbtn", L"567,0,597,20", L"", L"settingbutton");
	SettingButton->SetAttribute(L"normalimage", TOOLS_BTN_NORMAL);
	SettingButton->SetAttribute(L"hotimage", TOOLS_BTN_PUSH);
	SettingButton->SetAttribute(L"pushedimage", TOOLS_BTN_PUSH);

	
	//��¼��;ţţ�ֶ�
	CTextUI *LoginText = CreateDefBotton<CTextUI>(L"loginFTNN", L"400,40,500,70", L"",L"", L"��¼��;ţţ");
	LoginText->SetFont(1);

	//-----------------------------------��¼�����˺���-------------------------------------------------------------------------

	CComboUI *AccountCombo = CreateDefBotton<CComboUI>( L"accountcombo", L"400,100,557,130");
	AccountCombo->SetAttribute(_T("normalimage"), COMBO_NOR);
	AccountCombo->SetAttribute(_T("hotimage"), COMBO_OVER);
	AccountCombo->SetAttribute(_T("pushedimage"), COMBO_OVER);
	

	CEditUI* pAccountEdit = CreateDefBotton<CEditUI>( L"accountedit", L"401,101,536,129", L"", L"", L"ţţ��/��½�ֻ���/����");
	pAccountEdit->SetMaxChar(25);

	//�����ֻ�
	CButtonUI *SelectText = CreateDefBotton<CButtonUI>(L"selecttext", L"558,105,617,130", L"", L"", L"�����ֻ�");
	SelectText->SetTextColor(0x1E90FF);
	
	CButtonUI* line1 = CreateDefBotton<CButtonUI>(L"line1", L"400,129,617,133", LINE_NOR);
	
	//------------------------------------------------------------------------------------------------------------
	

	//-----------------------------------��¼����������-------------------------------------------------------------------------
	//��¼����
	CEditUI *KeyId = CreateDefBotton<CEditUI>(L"keyid", L"400,134,627,164", L"", L"", L"��¼����");
	KeyId->SetMaxChar(20);

	CButtonUI* line2 = CreateDefBotton<CButtonUI>(L"line2", L"400,164,617,168", LINE_NOR);
	//------------------------------------------------------------------------------------------------------------

	//��ס����===begin
	CCheckBoxUI * RemKey = CreateDefBotton<CCheckBoxUI>(L"remkey", L"400,170,420,190");
	RemKey->SetAttribute(_T("normalimage"), CHECKED);
	RemKey->SetAttribute(_T("selectedimage"), UNCHECKED);
	RemKey->SetCheck(true);

	CTextUI *RemKeyText = CreateDefBotton<CTextUI>(L"remkeytext", L"420,170,480,190", L"", L"", L"��ס����");
	//hlt_bg->Add(RemKeyText); ��Ҫ�ظ����븸���棬CreateDefBotton�Ѿ�ʵ��
	//===========end

	//�Զ���½begin
	CCheckBoxUI * AutoLogin = CreateDefBotton<CCheckBoxUI>( L"autologin", L"490,170,510,190");
	AutoLogin->SetAttribute(_T("normalimage"), CHECKED);
	AutoLogin->SetAttribute(_T("selectedimage"), UNCHECKED);
	AutoLogin->SetCheck(true);

	CTextUI *AutoLoginText = CreateDefBotton<CTextUI>(L"autologintext", L"510,170,570,190", L"", L"", L"�Զ���½");
	//=========end

	//�������� 
	CButtonUI *ForgetKeyText = CreateDefBotton<CButtonUI>(L"forgetkey", L"570,170,630,190", L"", L"", L"��������");
	ForgetKeyText->SetUserData(FORGET_PSW);
	ForgetKeyText->SetTextColor(0x1E90FF);

    //������½�ؼ�  
	CButtonUI *LoginImmediately = CreateDefBotton<CButtonUI>(L"loginimmedi", L"400,200,627,230", L"", L"", L"������½");
	LoginImmediately->SetAttribute(_T("normalimage"), LOGIN_BTN_NOR);
	LoginImmediately->SetAttribute(_T("hotimage"), LOGIN_BTN_PUSH);
	LoginImmediately->SetAttribute(_T("pushedimage"), LOGIN_BTN_NOR);

	//ע��ţţ�˺� 
	CTextUI *RegisterId = CreateDefBotton<CTextUI>(L"registerid", L"430,300,510,320", L"", L"", L"ע��ţţ�˺�");
	RegisterId->SetTextColor(0x1E90FF);

	//text���� ������ʽ��¼ 
	CTextUI *OtherLogin = CreateDefBotton<CTextUI>(L"otherlogin", L"510,300,610,320", L"", L"", L"�� ������ʽ��¼");
	OtherLogin->SetTextColor(0xFF000000);
	OtherLogin->SetFont(2);

	//qq ΢�� ΢��ͼ��
	//�����������Ȳ�д



	

	ShowWindow(true);
}

LRESULT CLogin::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;

	return __super::HandleMessage(uMsg, wParam, lParam);
}