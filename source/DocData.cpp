/********************************************************************
		filename :DocData.cpp
    	description :�ض����ĵ������ݴ洢��
		created	by ������ 2013/3/30 19:10
    	updated	by ������ 2013/3/30 19:10
*********************************************************************/
#include "StdAfx.h"
#include "stringhelper.h"
AcApDataManager<CDocData> DocVars ;
/*
 *�������ܣ����캯��������Ĭ��ֵ
 *�������ڣ�2013/3/30 19:14
 *�������ڣ�2013/3/30 19:14
*/
CDocData::CDocData ()
{
	m_nTextScale=1;
	m_nTextSortMode=2;
	m_nTextOutMode=1;
	m_nIsExpand=0;
	m_fTextHeight=0;
}

/*
 *�������ܣ��������캯��
 *�������ڣ�2013/3/30 19:18
 *�������ڣ�2013/3/30 19:18
*/
CDocData::CDocData (const CDocData &data)
{
	m_nTextScale=1;
	m_nTextSortMode=2;
	m_nTextOutMode=1;
	m_nIsExpand=0;
	m_fTextHeight=0;
}

/*
 *�������ܣ���������
 *�������ڣ�2013/3/30 19:19
 *�������ڣ�2013/3/30 19:19
*/
CDocData::~CDocData () {
}
/*
 *�������ܣ���ӱ��ʽ���б�
 *�������ڣ�2013-03-22
 *�������ڣ�2013-03-22
*/
void CDocData::SaveExpression(string expression)
{
	if(m_lstExpression.size()>0 && m_lstExpression.back()==expression)
		return;
	m_lstExpression.push_back(expression);
}
/*
 *�������ܣ��õ����һ�����ʽ
 *�������ڣ�2013-03-22
 *�������ڣ�2013-03-22
*/
string CDocData::GetLastExpression()
{
	if(m_lstExpression.size()==0)
		return "";
	return m_lstExpression.back();
}
/*
 *�������ܣ��õ����ģʽ
 *�������ڣ�2013/3/30 19:30
 *�������ڣ�2013/3/30 19:30
*/
int CDocData::GetOutMode()
{
	return m_nTextOutMode;
}
/*
 *�������ܣ��õ�����ģʽ
 *�������ڣ�2013/3/30 19:29
 *�������ڣ�2013/3/30 19:29
*/
int CDocData::GetSortMode()
{
	return m_nTextSortMode;
}
/*
 *�������ܣ��õ�����С��λ��
 *�������ڣ�2013/3/30 19:29
 *�������ڣ�2013/3/30 19:29
*/
int CDocData::GetScale()
{
	return m_nTextScale;
}
/*
 *�������ܣ��������ģʽ
 *�������ڣ�2013/3/30 19:27
 *�������ڣ�2013/3/30 19:27
*/
void CDocData::SetOutMode(int mode)
{
	m_nTextOutMode=mode;
}
/*
 *�������ܣ���������ģʽ
 *�������ڣ�2013/3/30 19:26
 *�������ڣ�2013/3/30 19:26
*/
void CDocData::SetSortMode(int mode)
{
	m_nTextSortMode=mode;
}
/*
 *�������ܣ����ñ���С��λ��
 *�������ڣ�2013/3/30 19:26
 *�������ڣ�2013/3/30 19:26
*/
void CDocData::SetScale(int scale)
{
	m_nTextScale=scale;
}
/*
 *�������ܣ����õ�ǰ���ָ߶�
 *�������ڣ�2013/3/30 19:25
 *�������ڣ�2013/3/30 19:25
*/
void CDocData::SetTextHeight(double height)
{
	m_fTextHeight=height;
}
/*
 *�������ܣ��������ָ߶�
 *�������ڣ�2013/3/30 21:23
 *�������ڣ�2013/3/30 21:23
*/
void CDocData::SetTextHeight(string height)
{
	m_fTextHeight=StringHelper::toDouble(height);
}
/*
 *�������ܣ��õ����ָ߶ȵ��ַ�����ʾ
 *�������ڣ�2013/3/30 21:54
 *�������ڣ�2013/3/30 21:54
*/
string CDocData::GetTextHeightStr()
{
	return StringHelper::toString(m_fTextHeight);
}
/*
 *�������ܣ��õ����ָ߶�
 *�������ڣ�2013/3/30 21:55
 *�������ڣ�2013/3/30 21:55
*/
double CDocData::GetTextHeight()
{
	return m_fTextHeight;
}