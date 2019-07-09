/********************************************************************
		filename :D:\MyAppProject\���˼�����\����\source\CMultDText.cpp
    	description :�����ı����϶���
		created	by ������ 2013/4/1 21:13
    	updated	by ������ 2013/4/1 21:13
*********************************************************************/
#include "StdAfx.h"
#include "CMultDText.h"
#include "stringhelper.h"
#include "CArxHelper.h"
/*
 *�������ܣ������ı����ϣ���ƫ�������������������ڲ���ѡ�񼯵��½�ģʽ��
 *�������ڣ�2013/4/1 21:13
 *�������ڣ�2013/4/1 21:13
*/
CMultDText::CMultDText(const vector<string>& vecvalue,const AcGeVector3d offset)
{
	for(int i=0;i<vecvalue.size();i++)
	{
		AcDbText* pText;
		pText=new AcDbText();
		pText->setTextString(S2WS(vecvalue[i]).c_str());
		pText->setDatabaseDefaults();
		if(DocVars.docData().GetTextHeight()!=0)
		{
			pText->setHeight(DocVars.docData().GetTextHeight());
		}
		m_vecText.push_back(pText);
	}
	m_vecOffset.push_back(offset);
}
/*
 *�������ܣ������ı����ϣ����ı�ѡ�񼯹������������ڴ�ѡ�񼯵��½�ģʽ���µ��ı��������λ����Դ�ڸ�ѡ�񼯡�
 *�������ڣ�2013/4/1 21:17
 *�������ڣ�2013/4/1 21:17
*/
CMultDText::CMultDText(const vector<string>& vecvalue,const vector<AcDbObjectId>& vecid)
{
	AcGePoint3d lastPoint;
	for(int i=0;i<vecid.size();i++)
	{
		AcDbText* pSource;
		if(acdbOpenObject(pSource,vecid[i],AcDb::kForRead)==Acad::eOk)
		{
			AcDbText* pText=new AcDbText();
			m_vecText.push_back(pText);
			//�������ֵ�λ��
			pText->setDatabaseDefaults();
			//������ʽ����ȡ���ֱģʽ��ˮƽģʽ��������ӡ���ת
			pText->setTextStyle(pSource->textStyle());
			pText->setThickness(pSource->thickness());
			//���ֵĺ������ģʽ���������ģʽ�����ڴ����ã�����һ����Ҫ�о�������
			//pText->setVerticalMode(pSource->verticalMode());
			//pText->setHorizontalMode(pSource->horizontalMode());
			pText->setWidthFactor(pSource->widthFactor());
			pText->setRotation(pSource->rotation());
			//��������
			pText->setPropertiesFrom(pSource,false);
			//��������
			pText->setTextString(S2WS(vecvalue[i]).c_str());
			//���ָ߶�
			if(DocVars.docData().GetTextHeight()!=0)
			{
				pText->setHeight(DocVars.docData().GetTextHeight());
			}
			else
			{
				pText->setHeight(pSource->height());
			}
			//���ּ��
			if(i>0)m_vecOffset.push_back(pSource->position()-lastPoint);
			lastPoint=pSource->position();
			pSource->close();
		}
	}
}
/*
 *�������ܣ�����ʱ���m_vecText��ָ����ı�����AcDbText,��ֹ�ڴ�й¶��
 *�������ڣ�2013/4/1 21:19
 *�������ڣ�2013/4/1 21:19
*/
CMultDText::~CMultDText()
{
	clear();
}
/*
 *�������ܣ��ڴ�����������ա�
 *�������ڣ�2013/4/1 21:20
 *�������ڣ�2013/4/1 21:20
*/
void CMultDText::clear()
{
	for(int i=0;i<m_vecText.size();i++)
	{
		delete m_vecText[i];
	}
	m_vecText.clear();
	m_vecOffset.clear();
}
/*
 *�������ܣ���ʾ�����ͼ��
 *�������ڣ�2013/3/30 23:10
 *�������ڣ�2013/3/30 23:10
*/
#if _MSC_VER>1400
#pragma message("using subWorldDraw")
Adesk::Boolean CMultDText::subWorldDraw (AcGiWorldDraw* mode)
{
	for(int i=0;i<m_vecText.size();i++)
	{
		mode->geometry().draw(m_vecText[i]);
	}
	return AcDbEntity::subWorldDraw(mode);
}
#else
#pragma message("using worldDraw")
Adesk::Boolean CMultDText::worldDraw (AcGiWorldDraw* mode)
{
	for(int i=0;i<m_vecText.size();i++)
	{
		mode->geometry().draw(m_vecText[i]);
	}
	return AcDbEntity::worldDraw(mode);
}
#endif

/*
 *�������ܣ����û��㣬��һ���ı���λ��λ�ڻ��㣬�Ժ�����ָ���ƫ����������λ�á�
 *�������ڣ�2013/3/30 23:09
 *�������ڣ�2013/3/30 23:09
*/
void CMultDText::setBasePoint(AcGePoint3d basePoint)
{
	int offsetNum=m_vecOffset.size();
	AcGePoint3d lastPoint=basePoint;
	for(int i=0;i<m_vecText.size();i++)
	{
		AcGePoint3d pos=(i==0)?lastPoint:(lastPoint+m_vecOffset[(i-1)%offsetNum]);
		m_vecText[i]->setPosition(pos);
		lastPoint=pos;
	}
}
/*
 *�������ܣ����͵�dwg
 *�������ڣ�2013/3/30 23:08
 *�������ڣ�2013/3/30 23:08
*/
void CMultDText::appendToCurrentSpace()
{
	AcDbDatabase * pDb = acdbCurDwg();
	AcDbBlockTable * pBlockTable;
	pDb ->getBlockTable(pBlockTable, AcDb::kForRead);
	AcDbBlockTableRecord *pBlkRec;
	if (pDb ->tilemode())
	{
		pBlockTable ->getAt(ACDB_MODEL_SPACE, pBlkRec, AcDb::kForWrite);
	}
	else
	{
		pBlockTable ->getAt(ACDB_PAPER_SPACE, pBlkRec, AcDb::kForWrite);
	}
	pBlockTable ->close();
	for (int i = 0; i < m_vecText.size(); i++)
	{
		if (Acad::eOk == pBlkRec ->appendAcDbEntity(m_vecText[i]))
		{
			AcGePoint3d pt=m_vecText[i]->position();
			if(DocVars.docData().GetTextHeight()!=0)
			{
				m_vecText[i]->setHeight(DocVars.docData().GetTextHeight());
			}
			m_vecText[i] ->close();
		}
		else
		{
			delete m_vecText[i];
		}
	}
	pBlkRec ->close();
	m_vecText.clear();
	m_vecOffset.clear();
}