/*======================================================================
//        filename :acrxEntryPoint.cpp
//        description :�������
//        created by ������   2012-11-10
//        updated by ������   2012-11-10		
//======================================================================*/
#include "StdAfx.h"
#include "resource.h"
#define szRDS _RXST("Bat")
void MyAppRun()
{
	acedCommand(RTSTR, _T("bat_uc"), 0);
}
//----- ObjectARX EntryPoint
class CUltracalculatorApp : public AcRxArxApp 
{
public:
	//���캯��
	CUltracalculatorApp () : AcRxArxApp () {}
	//��д��ʼ����Ϣ������
	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) 
	{
		//���û���ĳ�ʼ����Ϣ����
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt);
		//����ʱ��ʾ�汾����ݼ�
		AcadAppInfo info;
		info.setAppName (_T("Ultracalculator"));   
		if( Acad::eOk == info.readFromRegistry () )
		{
			const TCHAR* desc=info.appDesc();
			int len=_tcslen(desc);
			TCHAR cmds[3]=_T("cc");
			cmds[0]=desc[len-2];
			cmds[1]=desc[len-1];
			acutPrintf(desc);
			acutPrintf(_T("\n"));
			AcEdCommandStack::cast(acrxSysRegistry()->at(ACRX_COMMAND_DOCK))->addCommand(_T("BATTOOL"), _T("ULTRACALCULATOR"), cmds, ACRX_CMD_TRANSPARENT, MyAppRun);
		}
		//����
		return (retCode) ;
	}
	//��дж����Ϣ������
	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) 
	{
		//���û����ж����Ϣ����
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;
		//��ʾж�سɹ�
		acutPrintf(_T("\n���˼�����ж�سɹ���"));
		//����
		return (retCode) ;
	}
	//ע�����
	virtual void RegisterServerComponents () {}
} ;
IMPLEMENT_ARX_ENTRYPOINT(CUltracalculatorApp)