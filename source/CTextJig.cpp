#pragma once
#include "StdAfx.h"
#include "CArxHelper.h"
#include "stringhelper.h"
/*
 *�������ܣ�jig�๹�캯��
 *�������ڣ�2013-03-25
 *�������ڣ�2013-03-25
*/
CTextValueJig::CTextValueJig()
{ }
/*
 *�������ܣ���ʼ�϶�,�����ı�ֱ���϶���
 *�������ڣ�2013-03-25
 *�������ڣ�2013-03-25
*/
void CTextValueJig::doIt(string text)
{
#ifdef _UNICODE
	vector<string> vecvalue;
	vecvalue.push_back(text);
	m_pEntity=new CMultDText(vecvalue,AcGeVector3d(0,0,0));
	m_basepoint=m_startpoint=AcGePoint3d(0,0,0);
	setDispPrompt(_T("ָ����: "));
	if ( AcEdJig::kNormal == drag() )
	{
		m_pEntity ->appendToCurrentSpace();
	}
	else m_pEntity->clear();
	delete m_pEntity;
#endif
}
/*
 *�������ܣ���ʼ�϶�,����ѡ���һ���ı���Ϊģ�塣
 *�������ڣ�2013-03-25
 *�������ڣ�2013-03-25
*/
void CTextValueJig::doIt(const vector<AcDbObjectId>& vecid, const vector<string>& vecvalue)
{
	if(vecid.size()==0)return;
	CDText dtext=CArxHelper::GetEntityByObjectId(vecid[0]);
	m_basepoint=AcGePoint3d(dtext.x,dtext.y,dtext.z);
	ads_point ptResult;
	if(RTNORM==acedGetPoint(NULL,_T("\nָ������: "),ptResult))
	{
		m_pEntity=new CMultDText(vecvalue,vecid);
		m_startpoint.x=ptResult[0];
		m_startpoint.y=ptResult[1];
		m_startpoint.z=ptResult[2];
		setDispPrompt(_T("ָ���ڶ�����: "));
		if ( AcEdJig::kNormal == drag() )
		{	
			m_pEntity ->appendToCurrentSpace();
		}
		else m_pEntity->clear();
		delete m_pEntity;
		m_pEntity=NULL;
	}
}
/*
 *�������ܣ���ʼ�϶�����offset��Ϊ���
 *�������ڣ�2013-03-25
 *�������ڣ�2013-03-25
*/
void CTextValueJig::doIt(AcGeVector3d offset, const vector<string>& vecvalue)
{
	m_pEntity=new CMultDText(vecvalue,offset);
	m_basepoint=m_startpoint=AcGePoint3d(0,0,0);
	setDispPrompt(_T("ָ����: "));
	if ( AcEdJig::kNormal == drag() )
	{	
		m_pEntity ->appendToCurrentSpace();
	}
	else m_pEntity->clear();
	delete m_pEntity;
	m_pEntity=NULL;
}
/*
 *�������ܣ���дsampler���������ڲɼ�������
 *�������ڣ�2012-11-13
 *�������ڣ�2013-03-24
*/
AcEdJig::DragStatus	CTextValueJig::sampler()
{
	setUserInputControls((UserInputControls)
		(AcEdJig::kAccept3dCoordinates
		| AcEdJig::kNoNegativeResponseAccepted
		| AcEdJig::kNoZeroResponseAccepted));

	static AcGePoint3d dTempPoint;
	DragStatus stat = acquirePoint(m_endpoint);
	if (dTempPoint != m_endpoint)
	{
		dTempPoint = m_endpoint;
	}
	else if (stat == AcEdJig::kNormal)
	{
		return AcEdJig::kNoChange;
	}
	return stat;
}
/*
 *�������ܣ���дupdate����������ʵʱ���¡�
 *�������ڣ�2012-11-13
 *�������ڣ�2013-03-25
*/
Adesk::Boolean CTextValueJig::update()
{
	m_pEntity->setBasePoint(m_basepoint+(m_endpoint-m_startpoint));
	return Adesk::kTrue;
}
/*
 *�������ܣ���дentity����,�����϶�������ĸ��¡�
 *�������ڣ�2012-11-13
 *�������ڣ�2012-11-13
*/
AcDbEntity*	CTextValueJig::entity() const
{
	m_pEntity->setBasePoint(m_basepoint+(m_endpoint-m_startpoint));
	return m_pEntity;
}
