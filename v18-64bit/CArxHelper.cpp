#include "StdAfx.h"
#include "CArxHelper.h"
#include "stringhelper.h"
#include "Express.h"
#include "Except.h"
#include "CmdHelper.h"
/*
 *�������ܣ�����id�õ�����
 *�������ڣ�2012-11-12
 *�������ڣ�2012-11-12
*/
CDText CArxHelper::GetEntityByObjectId(AcDbObjectId id)
{
	CDText ret;
	AcDbText* pText;
	//ͨ��id�򿪶��󲢻�ö���ָ��
	if(acdbOpenObject(pText,id,AcDb::kForRead)==Acad::eOk)
	{
		ret.x=pText->position().x;
		ret.y=pText->position().y;
		ret.z=pText->position().z;
		ret.id=id;
		ret.text=WS2S(TString(pText->textString()));
		pText->close();
	}
	return ret;
}
/*
 *�������ܣ�����id�еõ�������
 *�������ڣ�2012-11-12
 *�������ڣ�2012-11-12
*/
vector<CDText> CArxHelper::GetEntityByObjectId(vector<AcDbObjectId> ids)
{
	vector<CDText> ret;
	for(int i=0;i<ids.size();i++)
	{
		ret.push_back(GetEntityByObjectId(ids[i]));
	}
	return ret;
}
/*
 *�������ܣ������ı����󵽵�ǰdwg
 *�������ڣ�2012-11-12
 *�������ڣ�2012-11-12
*/
AcDbObjectId CArxHelper::Draw(CDText entity)
{
	AcDbObjectId ret;
	//�򿪵�ǰ���ݿ��еķ��ű�BlockTable
	AcDbBlockTable *pbt;
	acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pbt,AcDb::kForWrite);
	//��BlockTable��¼
	AcDbBlockTableRecord *pbtr;
	pbt->getAt(ACDB_MODEL_SPACE,pbtr,AcDb::kForWrite);
	AcGePoint3d pt(entity.x,entity.y,entity.z);
	AcDbText *pText=new AcDbText(pt,S2WS(entity.text).c_str());
	pbtr->appendAcDbEntity(ret,pText);
	pText->close();
	//�رտ��
	pbtr->close();
	pbt->close();
	return ret;
}
/*
 *�������ܣ������ı������е���ǰdwg
 *�������ڣ�2012-11-12
 *�������ڣ�2012-11-12
*/
vector<AcDbObjectId> CArxHelper::Draw(vector<CDText> entities)
{
	vector<AcDbObjectId> ret;
	for(int i=0;i<entities.size();i++)
	{
		ret.push_back(Draw(entities[i]));
	}
	return ret;
}
/*
 *�������ܣ�ʰȡ��
 *�������ڣ�2012-11-12
 *�������ڣ�2012-11-13
*/
bool CArxHelper::PickPoint(AcGePoint3d& pt,string msg)
{
	return acedGetPoint(NULL,S2WS(msg).c_str(),asDblArray(pt))==RTNORM?true:false;
}
/*
 *�������ܣ�����ʽ��ȡ�ı������id
 *�������ڣ�2012-11-12
 *�������ڣ�2012-11-12
*/
vector<AcDbObjectId> CArxHelper::SelectAcDbObjects(struct resbuf* eb)
{
	vector<AcDbObjectId> ret;
	ads_name ssname;
	//���ѡ��
	long length=0;
	if(acedSSGet(NULL,NULL,NULL,eb,ssname)==RTNORM && acedSSLength(ssname,&length)==RTNORM)
	{
		AcDbObjectId id=AcDbObjectId::kNull;
		ads_name ent;
		for(int i=0;i<length;i++)
		{
			//���ѡ��ssname�е�j�������ads_name
			if(acedSSName(ssname,i,ent)==RTNORM && acdbGetObjectId(id,ent)==Acad::eOk)
			{
				ret.push_back(id);
			}
		}
	}
	acedSSFree(ssname);
	return ret;
}
/*
 *�������ܣ���ʽ��
 *�������ڣ�2012-11-12
 *�������ڣ�2012-11-12
*/
void CArxHelper::Format(AcDbObjectId source,AcDbObjectId dest)
{
	AcDbText* pSource,*pDest;
	//ͨ��id�򿪶��󲢻�ö���ָ��
	if(acdbOpenObject(pSource,source,AcDb::kForRead)==Acad::eOk && 
		acdbOpenObject(pDest,dest,AcDb::kForWrite)==Acad::eOk)
	{
		pDest->setHeight(pSource->height());
		pDest->setTextStyle(pSource->textStyle());
	}
	pSource->close();
	pDest->close();
}
/*
 *�������ܣ���ʽ��
 *�������ڣ�2012-11-12
 *�������ڣ�2012-11-12
*/
void CArxHelper::Format(vector<AcDbObjectId> source,vector<AcDbObjectId> dest)
{
	for(int i=0;i<source.size();i++)Format(source[i],dest[i]);
}
/*
 *�������ܣ���cad������������ʾ��Ϣ
 *�������ڣ�2012-11-12
 *�������ڣ�2012-11-12
*/
void CArxHelper::ShowMessage(string msg,string name)
{
	if(!msg.empty()&&!name.empty())
	{
		msg.replace(msg.find("%s"),2,name);
		acedPrompt(S2WS(msg).c_str());
	}
}
/*
 *�������ܣ���cad������������ʾ��Ϣ
 *�������ڣ�2012-11-12
 *�������ڣ�2012-11-12
*/
void CArxHelper::ShowMessage(string msg)
{
	if(!msg.empty())
		acedPrompt(S2WS(msg).c_str());
}
/*
 *�������ܣ�ucs��wcs��ת��
 *�������ڣ�2012-11-13
 *�������ڣ�2012-11-13
*/
AcGePoint3d CArxHelper::ucs2wcs(const AcGePoint3d& ucsPt)
{
	AcGePoint3d ret;
	struct resbuf rbFrom, rbTo;
	rbFrom.restype = RTSHORT;
	rbFrom.resval.rint = 1; // from UCS
	rbTo.restype = RTSHORT;
	rbTo.resval.rint = 0; // to WCS
	acedTrans(asDblArray(ucsPt), &rbFrom, &rbTo,
		Adesk::kFalse, asDblArray(ret));//Adesk::kFalse��ʾ�ǵ㻹������
	return ret;
}
/*
 *�������ܣ�wcs��ucs��ת��
 *�������ڣ�2012-11-13
 *�������ڣ�2012-11-13
*/
AcGePoint3d CArxHelper::wcs2ucs(const AcGePoint3d& wcsPt)
{
	AcGePoint3d ret;
	struct resbuf rbFrom, rbTo;
	rbFrom.restype = RTSHORT;
	rbFrom.resval.rint =0; // from WCS
	rbTo.restype = RTSHORT;
	rbTo.resval.rint = 1; // to UCS
	acedTrans(asDblArray(wcsPt), &rbFrom, &rbTo,
		Adesk::kFalse, asDblArray(ret));//Adesk::kFalse��ʾ�ǵ㻹������
	return ret;
}
/*
 *�������ܣ����õ����ı�������
 *�������ڣ�2013-03-22
 *�������ڣ�2013-03-22
*/
void CArxHelper::SetDTextContent(AcDbObjectId id,string content)
{
	AcDbText* pText;
	//ͨ��id�򿪶��󲢻�ö���ָ��
	if(acdbOpenObject(pText,id,AcDb::kForWrite)==Acad::eOk)
	{
		pText->setTextString(S2WS(content).c_str());
		pText->close();
	}
}
vector<double> CArxHelper::GetDouble(string msg,int num)
{
	vector<double> ret;
	ads_real value;
	for(int i=0;i<num;i++)
	{
		if(RTNORM==acedGetReal(S2WS(msg).c_str(),&value))
		{
			ret.push_back(value);
		}
	}
	return ret;
}
bool CArxHelper::SetBlockPr(AcDbObjectId id,string tag,string text)
{
	AcDbObjectIterator* pAttrIter = NULL;
	AcDbEntity* pAEnt = NULL;
	AcDbEntity* pEnt = NULL;
	acdbOpenAcDbEntity(pEnt,id,AcDb::kForRead);
	AcDbBlockReference* pBlkRef = AcDbBlockReference::cast(pEnt);
	//������
	pAttrIter = pBlkRef->attributeIterator();

	if (pAttrIter != NULL)
	{
		for (pAttrIter->start();!pAttrIter->done();pAttrIter->step())
		{
			if (Acad::eOk == acdbOpenAcDbEntity(pAEnt,pAttrIter->objectId(),AcDb::kForRead))
			{
				AcDbAttribute* pAttrib = AcDbAttribute::cast(pAEnt);
				if (pAttrib != NULL )
				{
					StringT str=TString(pAttrib->tag());
					if(str==S2WS(tag))
					{
						pAttrib->upgradeOpen();
						pAttrib->setTextString(S2WS(text).c_str());
						pAttrib->downgradeOpen();
					}
				}
				pAEnt->close();
			}
		}
		delete pAttrIter;
	}
	pEnt->close();
	return true;
}