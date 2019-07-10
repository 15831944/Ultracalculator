/*======================================================================
//        filename :Maindlg.h
//        description :������Ի����ඨ��
//        created by ������   2012-11-10
//        updated by ������   2013-03-22			
//======================================================================*/
#pragma once
#include "StdAfx.h"
#include "acui.h"
#include "afxwin.h"
#include "CArxHelper.h"
#include "Express.h"
#include "stringhelper.h"
#include <string>
class CmdNode
{
	int ID;
	string Text;
	string Express;//���ʽ
	int TextOutMode;//�������ģʽ��0-�½���1-�޸ģ�2-�޸��Լ�
	int TextSortMode;//��������ģʽ��0-X���꣬1-Y���꣬2-�Զ��ж�
	int TextScale;//С��λ��
	double TextHeight;//���ָ߶�
};
class CMaindlg : public CAcUiDialog 
{
//��Ӷ�̬ʶ����Ϣӳ���
	DECLARE_DYNAMIC (CMaindlg)
	DECLARE_MESSAGE_MAP()
public:
	CMaindlg (CWnd *pParent =NULL, HINSTANCE hInstance =NULL) ;
	enum { IDD = IDD_MAINDLG,MAX=255,MAXSELECT=1000,MAXEXPRESSLENGTH=1024} ;
private:
	long m_ZKHeight;//չ���߶�
	bool m_ZKflag;// չ�����
	CEdit m_Express;// ���ʽ�����
	CEdit m_TextHeight;// ���ָ߶�
	CFont m_EditFont;// ���ʽ���������
	CComboBox m_dotBox;// С����λ��
	StringT m_str;// ���ʽ�ı�
private:
	string toString(double);//������תΪ�ı�
	string toString(variant);//������תΪ�ı�
	void DTextSort(vector<CDText>&);//�ı�����
	void DTextNew(vector<string>&);//�½��ı�
	void OutputExpressionValue(string);
	void Command_GetValue();
	bool Js();
//������Ϣ����
protected:
	virtual void DoDataExchange (CDataExchange *pDX) ;
	virtual BOOL OnInitDialog();
	virtual BOOL FindContextHelpFullPath(LPCTSTR fileName, CString& fullPath){return NULL;};
	afx_msg LRESULT OnAcadKeepFocus (WPARAM, LPARAM) ;
	afx_msg void OnBnClickedButtonZk();
	afx_msg void OnBnClickedButtonJs();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeExpression();
	afx_msg void OnEnChangeTextHeight();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedRadio(UINT);
	afx_msg void OnBnClickedButton(UINT);
//�������
public:
	static void CMaindlg::BAT_UC_main(void)
	{
		CMaindlg dlg;
		dlg.DoModal();
	}
	static void GetConfig();
private:
	static int m_config[1];//������Ϣ
	static vector<CmdNode>* m_pCmdNode;
} ;
//��ʼ����̬��Ա
//[0]-�Ƿ�չ��
int CMaindlg::m_config[1]={1};
//����ΪAutoCAD������
ACED_ARXCOMMAND_ENTRY_AUTO(CMaindlg, BAT_UC, _main, bat_uc, ACRX_CMD_TRANSPARENT, NULL)
