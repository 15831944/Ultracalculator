/********************************************************************
		filename :G:\���˼�����\source\Maindlg.cpp
    	description :���Ի��������ʵ��
		created	by ������ 2013/03/27 9:51
    	updated	by ������ 2013/03/27 9:51
*********************************************************************/
#include "StdAfx.h"
#include "resource.h"
#include "Maindlg.h"
#include "Express.h"
#include "Except.h"
#include "CArxHelper.h"
#include "stringhelper.h"
#include "CmdHandler.h"
#include "CmdHelper.h"

IMPLEMENT_DYNAMIC (CMaindlg, CAcUiDialog)
BEGIN_MESSAGE_MAP(CMaindlg, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_BN_CLICKED(IDC_BUTTON_ZK, &CMaindlg::OnBnClickedButtonZk)
	ON_BN_CLICKED(IDC_BUTTON_JS, &CMaindlg::OnBnClickedButtonJs)
	ON_BN_CLICKED(IDOK, &CMaindlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CMaindlg::OnEnChangeExpression)
	ON_EN_CHANGE(IDC_EDIT_HEIGHT, &CMaindlg::OnEnChangeTextHeight)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMaindlg::OnCbnSelchangeCombo1)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_RADIO1,IDC_RADIO6,&CMaindlg::OnBnClickedRadio)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_BUTTON1,IDC_BUTTON19,&CMaindlg::OnBnClickedButton)
END_MESSAGE_MAP()

CMaindlg::CMaindlg (CWnd *pParent, HINSTANCE hInstance) 
	: CAcUiDialog (CMaindlg::IDD, pParent, hInstance)
{
}

void CMaindlg::DoDataExchange (CDataExchange *pDX) 
{
	CAcUiDialog::DoDataExchange (pDX) ;
	DDX_Control(pDX, IDC_EDIT1, m_Express);
	DDX_Control(pDX, IDC_EDIT_HEIGHT, m_TextHeight);
	DDX_Control(pDX, IDC_COMBO1, m_dotBox);
}

LRESULT CMaindlg::OnAcadKeepFocus (WPARAM, LPARAM) 
{
	return (TRUE) ;
}
/*
 *�������ܣ���ʼ����������
 *�������ڣ�2012-11-12
 *�������ڣ�2012-12-04
*/
BOOL CMaindlg::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	m_ZKflag=true;
	CString str;
	for (int i=0;i < 6;i++)
	{
		str.Format(_T("%d"), i);
		m_dotBox.AddString( str );
	}
	m_dotBox.SetCurSel(DocVars.docData().GetScale());
	switch(DocVars.docData().GetOutMode())
	{
	case CDocData::NEW:
		CWnd::CheckRadioButton(IDC_RADIO1,IDC_RADIO3,IDC_RADIO1); break;
	case CDocData::MODIFY:
		CWnd::CheckRadioButton(IDC_RADIO1,IDC_RADIO3,IDC_RADIO2); break;
	case CDocData::AUTO:
		CWnd::CheckRadioButton(IDC_RADIO1,IDC_RADIO3,IDC_RADIO3); break;
	}
	switch(DocVars.docData().GetSortMode())
	{
	case CDocData::XX:
		CWnd::CheckRadioButton(IDC_RADIO4,IDC_RADIO6,IDC_RADIO4); break;
	case CDocData::YY:
		CWnd::CheckRadioButton(IDC_RADIO4,IDC_RADIO6,IDC_RADIO5); break;
	case CDocData::XY:
		CWnd::CheckRadioButton(IDC_RADIO4,IDC_RADIO6,IDC_RADIO6); break;
	}
	if(0==m_config[0])this->OnBnClickedButtonZk();
	//���ñ��ʽ�༭�������
	CFont* ptf=m_Express.GetFont();
	LOGFONT lf;
	ptf->GetLogFont(&lf);
	lf.lfHeight=lf.lfHeight*1.5;
	m_EditFont.CreateFontIndirect(&lf);
	m_Express.SetFont(&m_EditFont);
	//�����ִ�ֱ����
	/*CRect rc;
	m_Express.GetClientRect(&rc);
	CDC* pDC=m_Express.GetDC(); 
	CSize sz=pDC->GetTextExtent("123456789");
	m_rect=CRect(0,0,rc.Width(),sz.cy); 
	m_rect.OffsetRect(rc.CenterPoint()-m_rect.CenterPoint());
	m_Express.SetRect(&m_rect);*/
	//�����ָ�
	m_TextHeight.SetWindowText(S2WS(DocVars.docData().GetTextHeightStr()).c_str());
	//���ϴ�������ʾ�ڱ༭����
	string lastexpression=DocVars.docData().GetLastExpression();
	if(lastexpression!="")
		m_Express.SetWindowText(S2WS(lastexpression).c_str());
	int length=m_Express.LineLength();
	m_Express.SetSel(length,-1);
	m_Express.SetFocus();
	return FALSE;
}
/*
 *�������ܣ��������㰴ť������=������
 *�������ڣ�2012-11-12
 *�������ڣ�2013/03/27 11:16
*/
bool CMaindlg::Js()
{
	TCHAR str[MAXEXPRESSLENGTH];
	m_Express.GetWindowText(str,MAXEXPRESSLENGTH);
	m_str=TString(str);
	string express=WS2S(m_str);
	if(express.empty())return false;
	try
	{
		CmdHandler cmdhandler;
		//����Ǳ��ʽ
		if(express.length()>1&&express[0]=='='&&express[1]!='=')
		{
			cmdhandler.run(express);
		}
		//���������
		else
		{
			if(express.length()>1&&express[0]=='='&&express[1]=='=')
				express.erase(express.begin());
			cmdhandler.parse(express);
		}
		//������ʽ���Ա��´���ʾ2013-03-22
		DocVars.docData().SaveExpression(express);
	}
	catch (ExpressionExcept& error)
	{
		CArxHelper::ShowMessage(error.what());
		return false;
	}
	return true;
}
/*
 *�������ܣ��������㰴ť������=������
 *�������ڣ�2012-11-12
 *�������ڣ�2013/03/27 11:16
*/
void CMaindlg::OnBnClickedButtonJs()
{
	TCHAR str[MAXEXPRESSLENGTH];
	m_Express.GetWindowText(str,MAXEXPRESSLENGTH);
	m_str=TString(str);
	string express=WS2S(m_str);
	if(express.empty())return;
	
	try
	{
		CmdHandler cmdhandler;
		//����Ǳ��ʽ
		if(express.length()>1&&express[0]=='='&&express[1]!='=')
		{
			//cmdhandler.run(express);
			ExpressionCalculator calc;
			//���벢�������ʽ��
			calc.input(express);
			//�õ����ʽ�е�δ֪�����ŵ���ʱ�������档
			if(calc.getUnknowVar().size()==0)
			{
				string result="="+ExpressionCalculator::toString(calc.get());
				//������ʽ���Ա��´���ʾ2013-05-10
				DocVars.docData().SaveExpression(express);
				StringT wstr=S2WS(result);
				m_Express.SetWindowText(wstr.c_str());
				if(wstr.size()>0)
					m_Express.SetSel(wstr.size(),wstr.size(),0);
			}
			else
			{
				this->BeginEditorCommand();
				if(Js())this->OnOK();
				else this->CancelEditorCommand();
			}
		}
		//���������
		else
		{
			this->BeginEditorCommand();
			if(Js())this->OnOK();
			else this->CancelEditorCommand();
		}
	}
	catch (ExpressionExcept& error)
	{
		CArxHelper::ShowMessage(error.what());
	}
}
/*
 *�������ܣ�����չ�����ý��水ť���¼�
 *�������ڣ�2012-11-12
 *�������ڣ�2013/3/30 20:10
*/
void CMaindlg::OnBnClickedButtonZk()
{
	//����չ���߶�
	RECT lpRect;
	this->GetWindowRect(&lpRect);
	long width=lpRect.right-lpRect.left;
	long hight=lpRect.bottom-lpRect.top;
	if(m_ZKflag)
	{
		CRect rect;
		this->GetDlgItem(IDC_STATIC_KEY)->GetWindowRect(&rect);
		m_ZKHeight=lpRect.bottom-rect.bottom;
		this->MoveWindow(lpRect.left,lpRect.top,width,hight-m_ZKHeight);
		m_config[0]=0;
		m_ZKflag=FALSE;
	}
	else
	{
		this->MoveWindow(lpRect.left,lpRect.top,width,hight+m_ZKHeight);
		m_config[0]=1;
		m_ZKflag=TRUE;
	}
}
/*
 *�������ܣ�������ʽ�༭�����ݱ仯�¼�
 *�������ڣ�2013/03/27 11:16
 *�������ڣ�2013/05/07 19:17
*/
void CMaindlg::OnEnChangeExpression()
{
	TCHAR str[MAXEXPRESSLENGTH]; 
	m_Express.GetWindowText(str,MAXEXPRESSLENGTH);
	m_str=TString(str);
	int length=m_str.size();
	if(length==0)return;
	if(_T(' ')==m_str[length-1])
	{
		m_str.erase(length-1);
		m_Express.SetWindowText(m_str.c_str());
		this->BeginEditorCommand();
		if(Js())this->OnOK();
		else this->CancelEditorCommand();
	}
}
/*
 *�������ܣ��������ָ߶ȱ༭�����ݷ����仯�¼�
 *�������ڣ�2013/3/30 20:51
 *�������ڣ�2013/3/30 20:51
*/
void CMaindlg::OnEnChangeTextHeight()
{
	TCHAR str[MAX];
	m_TextHeight.GetWindowText(str,MAX);
	string strHeight=WS2S(TString(str));
	DocVars.docData().SetTextHeight(strHeight);
}
/*
 *�������ܣ��������ģʽ������ģʽ�ĵ�ѡ��ť�¼�
 *�������ڣ�2013/03/27 11:17
 *�������ڣ�2013/3/30 19:56
*/
void CMaindlg::OnBnClickedRadio(UINT id)
{
	switch(id)
	{
	case IDC_RADIO1:
	case IDC_RADIO2:
	case IDC_RADIO3:
		DocVars.docData().SetOutMode(id-IDC_RADIO1);break;
	case IDC_RADIO4:
	case IDC_RADIO5:
	case IDC_RADIO6:
		DocVars.docData().SetSortMode(id-IDC_RADIO4);break;
	}
}
/*
 *�������ܣ�����С��λ��������ѡ���¼�
 *�������ڣ�2013/03/27 11:17
 *�������ڣ�2013/03/27 11:17
*/
void CMaindlg::OnCbnSelchangeCombo1()
{
	DocVars.docData().SetScale(m_dotBox.GetCurSel());
}
/*
 *�������ܣ������û�ѡ��������ʽ
 *�������ڣ�2012-11-10
 *�������ڣ�2012-11-10
*/
void CMaindlg::OnBnClickedButton(UINT id)
{
	vector<CDText> vecDText;
	switch(id)
	{
	case IDC_BUTTON1:
		DocVars.docData().SetScale(2);
		m_dotBox.SetCurSel(DocVars.docData().GetScale());
		m_Express.SetWindowText(_T("=a*b/100"));break;
	case IDC_BUTTON2:
		DocVars.docData().SetScale(1);
		m_dotBox.SetCurSel(DocVars.docData().GetScale());
		m_Express.SetWindowText(_T("=kg(a)*b"));break;
	case IDC_BUTTON3:
		m_Express.SetWindowText(_T("ssum"));break;
	case IDC_BUTTON4:
		m_Express.SetWindowText(_T("sum"));break;
	case IDC_BUTTON5:
		m_Express.SetWindowText(_T("ssl"));break;
	case IDC_BUTTON6:
		m_Express.SetWindowText(_T("=substitute(a,\"&\",\"^\")"));break;
	case IDC_BUTTON7:
		m_Express.SetWindowText(_T("al"));break;
	case IDC_BUTTON8:
		m_Express.SetWindowText(_T("dc"));break;
	case IDC_BUTTON9:
		m_Express.SetWindowText(_T("gn"));break;
	case IDC_BUTTON10:
		m_Express.SetWindowText(_T("stb"));break;
	case IDC_BUTTON11:
		m_Express.SetWindowText(_T("sdos"));break;
	case IDC_BUTTON12:
		m_Express.SetWindowText(_T("sdot"));break;
	case IDC_BUTTON13:
		m_Express.SetWindowText(_T(""));break;
	case IDC_BUTTON14:
		m_Express.SetWindowText(_T("spl"));
		break;
	case IDC_BUTTON15:
		m_Express.SetWindowText(_T("splt"));break;
	case IDC_BUTTON16:
		m_Express.SetWindowText(_T("spld"));break;
	case IDC_BUTTON17:
		m_Express.SetWindowText(_T("splb"));break;
	case IDC_BUTTON18:
		m_Express.SetWindowText(_T("gll"));break;
	case IDC_BUTTON19:
		Command_GetValue();break;
	}
	int length=m_Express.LineLength();
	m_Express.SetSel(length,-1);
	m_Express.SetFocus();
}
/*
	*�������ܣ�ȡ����ֱ�ߵĳ��Ⱥ�
	*�������ڣ�2013-05-09
	*�������ڣ�2013-05-09
*/
void CMaindlg::Command_GetValue()
{
	//CArxEntity::ShowMessage("Command_GetSumLineLen");
	this->BeginEditorCommand();
	//struct resbuf buf=*acutBuildList(RTDXF0,L"TEXT",RTDXF0,L"LINE",RTNONE); 
	vector<AcDbObjectId> ids=CArxHelper::SelectAcDbObjects(acutBuildList(RTDXF0,_T("LINE"),RTNONE));
	if(ids.size()>0)
	{
		AcDbEntity* pEntity;
		if(acdbOpenObject(pEntity,ids[0],AcDb::kForRead)==Acad::eOk)
		{
			if(pEntity->isKindOf(AcDbLine::desc()))
			{
				AcGeVector3d v=((AcDbLine*)pEntity)->startPoint()-((AcDbLine*)pEntity)->endPoint();
				StringT wstr=S2WS("="+CmdHelper::toString(v.length()));
				m_Express.SetWindowText(wstr.c_str());
				m_Express.SetSel(wstr.size());
			}
			else if(pEntity->isKindOf(AcDbText::desc()))
			{
				string text=WS2S(TString(((AcDbText*)pEntity)->textString()));
				StringT wstr=S2WS(StringHelper::parseDouble(text));
				m_Express.SetWindowText(wstr.c_str());
				m_Express.SetSel(wstr.size());
			}
		}
	}
	this->CompleteEditorCommand();
}
/*
 *�������ܣ�����ȷ����ť
 *�������ڣ�2012-11-10
 *�������ڣ�2012-11-10
*/
void CMaindlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//TCHAR str[_MAX_PATH];
	//::GetModuleFileNameW(_hdllInstance,str,_MAX_PATH);
	////::MessageBox((HWND)m_hInstance,str,NULL,NULL);
	//int i,p;
	//for(i=0;i<wcslen(str);i++)
	//{
	//	if(_T('\\')==str[i])
	//	{
	//		p=i;
	//	}
	//}
	//str[p]=0;
	//wcscat(str,_T("\\���˼�����v2.1.CHM"));
	//if(ERROR_FILE_NOT_FOUND==(long)::ShellExecute(NULL,_T("open"),str,NULL,NULL,SW_SHOWNORMAL))
	//{
	//	if(IDYES==::MessageBox(NULL,_T("û���ҵ������ļ����Ƿ����أ�ѡ������ʾ���װ���"),_T("��ʾ"),MB_YESNO))
	//	{
	//		::ShellExecute(NULL,_T("open"),_T("http://e.ys168.com/?netbat"),NULL,NULL,SW_MAXIMIZE);
	//	}
	//	else
	//	{
	//		CString helpstring;
	//		helpstring.LoadStringW(IDS_CONTECT);
	//		acedPrompt(helpstring.GetBuffer());
	//		helpstring.LoadStringW(IDS_HELP);
	//		acedPrompt(helpstring.GetBuffer());
	//		helpstring.LoadStringW(IDS_HELP_FUNCTION);
	//		acedPrompt(helpstring.GetBuffer());
	//		helpstring.LoadStringW(IDS_HELP_USAGE);
	//		acedPrompt(helpstring.GetBuffer());
	//		this->OnOK();
	//		acedCommand(RTSTR,L"textscr",RTNONE);
	//	}
	//}
}
//BOOL CMaindlg::FindContextHelpFullPath (LPCTSTR fileName, CString& fullPath)
//{
//	return NULL;
//}