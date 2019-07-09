/********************************************************************
		filename :CmdHandler.cpp
    	description :�������
		created	by ������ 2013/03/27 9:57
    	updated	by ������ 2013/03/27 10:03
*********************************************************************/
#include "StdAfx.h"
#include "CmdHelper.h"
#include "CmdHandler.h"
#include "CEntitySelector.h"
//#include "stringhelper.h"
#include <algorithm>
/*
 *�������ܣ����캯��
 *�������ڣ�2013/03/27 9:28
 *�������ڣ�2013/03/27 9:31
*/
CmdHandler::CmdHandler()
{
	CmdHelper::Initialize(m_mapfunc);
}
/*
 *�������ܣ�������ʽ
 *�������ڣ�2013/03/27 9:58
 *�������ڣ�2013/4/9 23:01
*/
void CmdHandler::run(string express)
{
	if(express.empty())return;
	ExpressionCalculator calc;
	vector<string> vecvar;
	//����һ����־��������¼�Ƿ�����ű���i��
	bool hasIndexVar=false;
	//���벢�������ʽ��
	calc.input(express);
	//�õ����ʽ�е�δ֪�����ŵ���ʱ�������档
	vector<string> temp=calc.getUnknowVar();
	//����δ֪�����еġ�i����
	for(int i=0;i<temp.size();i++)
	{
		if(temp[i]!="i")
		{
			vecvar.push_back(temp[i]);
		}
		else hasIndexVar=true;
	}
	//���û��δ֪������
	if(vecvar.size()==0)
	{
		//���ģʽΪ�½�
		if(GetOutMode()==0)
		{
			if(hasIndexVar)calc.setVarValue("i",0);
			string text=toString(calc.get());
			CTextValueJig* jig=new CTextValueJig();
			jig->doIt(text);
			delete jig;
			return;
		}
		//���ģʽΪ�޸Ļ��Զ�
		else
		{
			CArxHelper::ShowMessage("ѡ��Ҫ�޸ĵ��ı�����:");
			vector<CDText> selected=CEntitySelector::GetDText();
			DTextSort(selected);
			for (int i=0;i<selected.size();i++)
			{
				if(hasIndexVar)calc.setVarValue("i",i);
				//CArxHelper::SetDTextContent(selected[i].id,toString(calc.get()));
				selected[i].text=toString(calc.get());
				selected[i].Update();
			}
			return;
		}
	}
	else
	{
		int minlen=MAXSELECT;
		vector<string> vecvalue;
		map<string,vector<CDText> > maptext;
		//��CAD��ѡ�����ı�����
		for(int i=0;i<vecvar.size();i++)
		{
			string name=vecvar[i];
			CArxHelper::ShowMessage("��ѡ�����%s��ֵ��",name);
			vector<CDText> vec=CEntitySelector::GetDText();
			if(vec.size()==0)
			{
				CArxHelper::ShowMessage("Ϊ����%s��ֵʧ�ܡ�\n",name);
				return;
			}
			//��¼��С����
			if(i==0)minlen=vec.size();
			//�������С���Ȳ����򱨴�
			if(vec.size()!=minlen)
			{
				CArxHelper::ShowMessage("����%s���Ȳ�ƥ�䡣\n",name);
				return;
			}
			//����
			DTextSort(vec);
			//����
			maptext.insert(pair<string,vector<CDText> >(name,vec));
		}
		//ѭ��������ʽ��ֵ
		for(int i=0;i<minlen;i++)
		{
			//����б���i�������ñ���i��ֵ��
			if(hasIndexVar)calc.setVarValue("i",i);
			//��������������ֵ��
			for(int j=0;j<vecvar.size();j++)
			{
				string name=vecvar[j];
				//calc.setVarValue(name,StringHelper::parseDouble(maptext[name][i].text));
				calc.setVarValue(name,maptext[name][i].text);
			}
			//����������ֵ�����С�
			vecvalue.push_back(toString(calc.get()));
		}
		//������ģʽΪ�޸��ı�
		if(GetOutMode()==1)
		{
			vector<CDText> vecSelectedDText=CEntitySelector::GetDText();
			DTextSort(vecSelectedDText);
			//��������������ĳ�����ѡ���Ҫ�޸ĵ��ı�������ƥ�䣬Ҫ��ʾ�û���2013-05-07�޸�
			if(vecSelectedDText.size()!=vecvalue.size())
			{
				CArxHelper::ShowMessage("ע�⣺ѡ���Ҫ�޸ĵ��ı����������������������ƥ��ġ�\n");
			}
			for(int i=0;i<vecSelectedDText.size();i++)
			{
				//CArxHelper::SetDTextContent(vecSelectedDText[i].id,vecvalue[i%vecvalue.size()]);
				vecSelectedDText[i].text=vecvalue[i%vecvalue.size()];
				vecSelectedDText[i].Update();
			}
			return;
		}
		//������ģʽΪ�½�
		else
		{
			//Ϊ���һ��������ѡ����ı�
			vector<AcDbObjectId> veclastids;
			vector<CDText> veclast=maptext[vecvar[vecvar.size()-1]];
			for(int i=0;i<minlen;i++)
			{
				veclastids.push_back(veclast[i].id);
			}
			//�½��ı�
			if(GetOutMode()==0)
			{
				CTextValueJig* jig=new CTextValueJig();
				jig->doIt(veclastids,vecvalue);
				delete jig;
			}
			//�Զ��޸�
			else if(GetOutMode()==2)
			{
				for(int i=0;i<veclast.size();i++)
				{
					veclast[i].text=vecvalue[i];
					veclast[i].Update();
				}
			}
		}
	}
}
/*
 *�������ܣ������������ֵ��ʾ�Ƿ�Ҫ�رնԻ���
 *�������ڣ�2013/03/27 10:36
 *�������ڣ�2013/4/9 23:01
*/
void CmdHandler::parse(string express)
{
	if(m_mapfunc.find(express)!=m_mapfunc.end())
	{
		m_mapfunc[express]();
	}
	else
	{
		//���ģʽΪ�½�
		if(GetOutMode()==CDocData::NEW)
		{
			CTextValueJig* jig=new CTextValueJig();
			jig->doIt(express);
			delete jig;
		}
		//���ģʽΪ�޸Ļ��Զ�
		else
		{
			CArxHelper::ShowMessage("ѡ��Ҫ�޸ĵ��ı�����:");
			vector<CDText> selected=CEntitySelector::GetDText();
			if(selected.size()>0)
			{
				DTextSort(selected);
				for (int i=0;i<selected.size();i++)
				{
					selected[i].text=express;
					selected[i].Update();
				}
			}
		}
	}
}
/*
 *�������ܣ��õ���ǰ�ĵ������ģʽ��
 *�������ڣ�2013/03/27 9:58
 *�������ڣ�2013/03/27 9:58
*/
int CmdHandler::GetOutMode()
{
	return DocVars.docData().GetOutMode();
}
/*
 *�������ܣ��õ���ǰ�ĵ�������ģʽ��
 *�������ڣ�2013/03/27 9:59
 *�������ڣ�2013/03/27 9:59
*/
int CmdHandler::GetSortMode()
{
	return DocVars.docData().GetSortMode();
}
/*
 *�������ܣ�����С��λ����doubleתΪstring��
 *�������ڣ�2013/03/27 9:59
 *�������ڣ�2013/03/27 9:59
*/
string CmdHandler::toString(double value)
{
	return CmdHelper::toString(value);
}
/*
 *�������ܣ�����С��λ����variantתΪstring��
 *�������ڣ�2013/03/27 10:00
 *�������ڣ�2013/03/27 10:00
*/
string CmdHandler::toString(variant value)
{
	return CmdHelper::toString(value);
}
/*
 *�������ܣ����ݵ�ǰ�ĵ�������ģʽ����������
 *�������ڣ�2013/03/27 10:00
 *�������ڣ�2013/05/07 18:26
*/
void CmdHandler::DTextSort(vector<CDText>& vec)
{
	CmdHelper::EntitySort(vec);
}

