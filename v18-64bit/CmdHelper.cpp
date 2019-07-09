/********************************************************************
		filename :G:\���˼�����\source\BAT_UC.cpp
    	description :���ֿ�������ʵ��
		created	by ������ 2013/03/27 11:10
    	updated	by ������ 2013/4/9 23:28
*********************************************************************/
#include "StdAfx.h"
#include "CmdHelper.h"
#include "Except.h"
#include "CArxHelper.h"
#include "stringhelper.h"
#include "CEntitySelector.h"
#include <algorithm>
#include "function.h"
/*
 *�������ܣ��õ���ǰ�ĵ������ģʽ��
 *�������ڣ�2013/03/27 9:58
 *�������ڣ�2013/03/27 9:58
*/
int CmdHelper::GetOutMode()
{
	return DocVars.docData().GetOutMode();
}
/*
 *�������ܣ��õ���ǰ�ĵ�������ģʽ��
 *�������ڣ�2013/03/27 9:59
 *�������ڣ�2013/03/27 9:59
*/
int CmdHelper::GetSortMode()
{
	return DocVars.docData().GetSortMode();
}
/*
 *�������ܣ�����С��λ����doubleתΪstring��
 *�������ڣ�2013/03/27 9:59
 *�������ڣ�2013/03/27 9:59
*/
string CmdHelper::toString(double value)
{
	if(value>1e100)return "Error";
	char num[20];
	sprintf(num,"%%.%dlf",DocVars.docData().GetScale());
	char str[MAX];
	sprintf(str,num,value+0.0000000000005);
	return string(str);
}
/*
 *�������ܣ��ַ���ת��Ϊʵ��
 *�������ڣ�2013/3/30 21:25
 *�������ڣ�2013/3/30 21:25
*/
double CmdHelper::toDouble(const string& str)
{
	return func::toDouble(str);
}
/*
 *�������ܣ�����С��λ����variantתΪstring��
 *�������ڣ�2013/03/27 10:00
 *�������ڣ�2013/03/27 10:00
*/
string CmdHelper::toString(variant value)
{
	//������������ַ���
	if(value.isString())
	{
		return ((string)value);
	}
	//�������������ֵ
	else
	{
		return toString((double)value);
	}
}
bool CmdHelper::EntitySort(vector<CLine>& vec)
{
	if(vec.size()<=0)return false;
	bool sortX=true;
	switch(GetSortMode())
	{
		//��X��������
	case 0:
		sort(vec.begin(),vec.end(),sort_x);
		break;
		//��Y��������
	case 1:
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		break;
		//�Զ��ж�����
	case 2:
		sort(vec.begin(),vec.end(),sort_x);
		double lx=vec.front().x-vec.back().x;
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		double ly=vec.front().y-vec.back().y;
		if(abs(lx)>abs(ly))
		{
			sort(vec.begin(),vec.end(),sort_x);
			sortX=true;
		}
		break;
	}
	return sortX;
}
bool CmdHelper::EntitySort(vector<CDText>& vec)
{
	if(vec.size()<=0)return false;
	bool sortX=true;
	switch(GetSortMode())
	{
		//��X��������
	case 0:
		sort(vec.begin(),vec.end(),sort_x);
		break;
		//��Y��������
	case 1:
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		break;
		//�Զ��ж�����
	case 2:
		sort(vec.begin(),vec.end(),sort_x);
		double lx=vec.front().x-vec.back().x;
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		double ly=vec.front().y-vec.back().y;
		if(abs(lx)>abs(ly))
		{
			sort(vec.begin(),vec.end(),sort_x);
			sortX=true;
		}
		break;
	}
	return sortX;
}
bool CmdHelper::EntitySort(vector<CDot>& vec)
{
	if(vec.size()<=0)return false;
	bool sortX=true;
	switch(GetSortMode())
	{
		//��X��������
	case 0:
		sort(vec.begin(),vec.end(),sort_x);
		break;
		//��Y��������
	case 1:
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		break;
		//�Զ��ж�����
	case 2:
		sort(vec.begin(),vec.end(),sort_x);
		double lx=vec.front().x-vec.back().x;
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		double ly=vec.front().y-vec.back().y;
		if(abs(lx)>abs(ly))
		{
			sort(vec.begin(),vec.end(),sort_x);
			sortX=true;
		}
		break;
	}
	return sortX;
}
bool CmdHelper::EntitySort(vector<CBlock>& vec)
{
	if(vec.size()<=0)return false;
	bool sortX=true;
	switch(GetSortMode())
	{
		//��X��������
	case 0:
		sort(vec.begin(),vec.end(),sort_x);
		break;
		//��Y��������
	case 1:
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		break;
		//�Զ��ж�����
	case 2:
		sort(vec.begin(),vec.end(),sort_x);
		double lx=vec.front().x-vec.back().x;
		sort(vec.begin(),vec.end(),sort_y);
		sortX=false;
		double ly=vec.front().y-vec.back().y;
		if(abs(lx)>abs(ly))
		{
			sort(vec.begin(),vec.end(),sort_x);
			sortX=true;
		}
		break;
	}
	return sortX;
}
/*
 *�������ܣ�����ı�
 *�������ڣ�2013/4/9 23:48
 *�������ڣ�2013/4/9 23:48
*/
void CmdHelper::DTextOut(string express)
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
		EntitySort(selected);
		for (int i=0;i<selected.size();i++)
		{
			//CArxHelper::SetDTextContent(selected[i].id,express);
			selected[i].text=express;
			selected[i].Update();
		}
	}
}
/*
	*�������ܣ��������
	*�������ڣ�2013-03-22
	*�������ڣ�2013-03-22
*/
void CmdHelper::BAT_UC_Sum()
{
	CArxHelper::ShowMessage("\n��������������ѡ��һ���ı�:");
	vector<CDText> vecDText=CEntitySelector::GetDText();
	if(vecDText.size()>0)
	{
		double ret=0;
		for(int i=0;i<vecDText.size();i++)
		{
			double result=0;
			try
			{
				result=toDouble(vecDText[i].text);
				ret+=result;
			}
			catch(ExpressionExcept& error)
			{
				CArxHelper::ShowMessage(vecDText[i].text+error.what());
			}
		}
		DTextOut(toString(ret));
	}
}
/*
	*�������ܣ������������
	*�������ڣ�2013-03-22
	*�������ڣ�2013-03-22
*/
void CmdHelper::BAT_UC_SSum()
{
	CArxHelper::ShowMessage("\n�����÷�����������ѡ�������飺");
	vector<CDText> vecIndex=CEntitySelector::GetDText();
	if(vecIndex.size()==0)
	{
		CArxHelper::ShowMessage("�����鲻��Ϊ�ա�");
		return;
	}
	EntitySort(vecIndex);
	CArxHelper::ShowMessage("ѡ�������飺\n");
	vector<CDText> vecValue=CEntitySelector::GetDText();
	if(vecValue.size()!=vecIndex.size())
	{
		CArxHelper::ShowMessage("���������ݸ�����ƥ�䡣");
		return;
	}
	EntitySort(vecValue);
	//�������
	map<string,double> summap;
	for (int i=0;i<vecIndex.size();i++)
	{
		if(summap.find(vecIndex[i].text)!=summap.end())continue;
		double sum=0;
		for (int j=i;j<vecIndex.size();j++)
		{
			if(vecIndex[i].text==vecIndex[j].text)
			{
				try
				{
					sum+=toDouble(StringHelper::parseDouble(vecValue[j].text));
				}
				catch(ExpressionExcept error)
				{
					CArxHelper::ShowMessage(error.what());
				}
			}
		}
		summap.insert(pair<string,double>(vecIndex[i].text,sum));
	}
	vector<AcDbObjectId> vecIds;
	//���
	vector<string> vecvalue;
	map<string,double>::iterator iter;
	for(iter=summap.begin();iter!=summap.end();++iter)
	{
		vecvalue.insert(vecvalue.begin(),1,iter->first+":"+toString(iter->second));
		//�ҵ�������Ӧ��objectid
		for (int i=0;i<vecIndex.size();i++)
		{
			if(vecIndex[i].text==iter->first)
			{
				vecIds.push_back(vecValue[i].id);
				break;
			}
		}
	}
	vector<string> vecsteelvalue[4];
	for(int i=0;i<vecvalue.size();i++)
	{
		if(vecvalue[i][0]=='$')
		{
			vecsteelvalue[0].push_back(vecvalue[i]);
		}
		else if(vecvalue[i][0]=='&')
		{
			vecsteelvalue[1].push_back(vecvalue[i]);
		}
		else if(vecvalue[i][0]=='^')
		{
			vecsteelvalue[2].push_back(vecvalue[i]);
		}
		else
		{
			vecsteelvalue[3].push_back(vecvalue[i]);
		}
	}
	vecvalue.clear();
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<vecsteelvalue[i].size();j++)
		{
			vecvalue.push_back(vecsteelvalue[i][j]);
		}
	}
	if(GetOutMode()==CDocData::NEW)
	{
		CTextValueJig* jig=new CTextValueJig();
		jig->doIt(vecIds,vecvalue);
		delete jig;
	}
	else
	{
		CArxHelper::ShowMessage("ѡ��Ҫ�޸ĵ��ı�����:");
		vector<CDText> selected=CEntitySelector::GetDText();
		EntitySort(selected);
		//ѡ����ı��պ�ƥ��
		if(selected.size()==vecvalue.size())
		{
			for (int i=0;i<selected.size();i++)
			{
				selected[i].text=vecvalue[i];
				selected[i].Update();
			}
		}
		//ѡ����ı��պ���2��
		else if(selected.size()==2*vecvalue.size())
		{
			for (int i=0;i<vecvalue.size();i++)
			{
				vector<string> vecstr=StringHelper::split(vecvalue[i],':');
				selected[2*i].text=vecstr[0]+":";
				selected[2*i].Update();
				selected[2*i+1].text=vecstr[1];
				selected[2*i+1].Update();
			}
		}
		else
		{
			CArxHelper::ShowMessage("Ҫ�޸ĵ��ı�������ƥ�䡣");
		}
	}
}
/*
	*�������ܣ����ֱ������
	*�������ڣ�2013-07-01
	*�������ڣ�2013-07-01
*/
void CmdHelper::BAT_UC_STable()
{
	try
	{
		ExpressionCalculator calc;
		CArxHelper::ShowMessage("\n���������������������ѡ��ֽ�ֱ����");
		vector<CDText> vecRadius=CEntitySelector::GetDText();
		if(vecRadius.size()>0)
		{
			EntitySort(vecRadius);
			CArxHelper::ShowMessage("��ѡ�񵥸�����");
			vector<CDText> vecLen=CEntitySelector::GetDText();
			if(vecLen.size()==vecRadius.size())
			{
				EntitySort(vecLen);
				CArxHelper::ShowMessage("��ѡ�������");
				vector<CDText> vecNum=CEntitySelector::GetDText();
				if(vecNum.size()==vecRadius.size())
				{
					EntitySort(vecNum);
					CArxHelper::ShowMessage("��ѡ�񹲳���");
					vector<CDText> vecSumLen=CEntitySelector::GetDText();
					if(vecSumLen.size()==vecRadius.size())
					{
						EntitySort(vecSumLen);
						calc.input("a*b/1000");
						DocVars.docData().SetScale(2);
						for(int i=0;i<vecRadius.size();i++)
						{
							calc.setVarValue("a",StringHelper::parseDouble(vecLen[i].text));
							calc.setVarValue("b",StringHelper::parseDouble(vecNum[i].text));

							vecSumLen[i].text=toString(calc.get());
							vecSumLen[i].Update();
						}
					}
					else return;
					//���㹲��
					CArxHelper::ShowMessage("��ѡ�����У�");
					vector<CDText> vecSumWet=CEntitySelector::GetDText();
					if(vecSumWet.size()==vecRadius.size())
					{
						EntitySort(vecSumWet);
						calc.input("kg(r)*a");
						DocVars.docData().SetScale(1);
						for(int i=0;i<vecRadius.size();i++)
						{
							calc.setVarValue("a",StringHelper::parseDouble(vecSumLen[i].text));
							calc.setVarValue("r",StringHelper::parseDouble(vecRadius[i].text));
							vecSumWet[i].text=toString(calc.get());
							vecSumWet[i].Update();
						}
					}
					else return;
					//����������
					map<string,double> summap;
					for (int i=0;i<vecRadius.size();i++)
					{
						if(summap.find(vecRadius[i].text)!=summap.end())continue;
						double sum=0;
						for (int j=i;j<vecRadius.size();j++)
						{
							if(vecRadius[i].text==vecRadius[j].text)
							{
								sum+=toDouble(StringHelper::parseDouble(vecSumWet[j].text));
							}
						}
						summap.insert(pair<string,double>(vecRadius[i].text,sum));
					}
					
					//������
					CArxHelper::ShowMessage("��ѡ��ϼ��У�");
					vector<CDText> vecSSum=CEntitySelector::GetDText();
					EntitySort(vecSSum);
					DocVars.docData().SetScale(0);
					vector<string> vecvalue;
					if(vecSSum.size()==summap.size())
					{
						map<string,double>::iterator iter;
						for(iter=summap.begin();iter!=summap.end();++iter)
						{
							vecvalue.push_back(iter->first+":"+toString(iter->second));
						}
					}
					else if(vecSSum.size()==2*summap.size())
					{
						map<string,double>::iterator iter;
						for(iter=summap.begin();iter!=summap.end();++iter)
						{
							vecvalue.push_back(iter->first+":");
							vecvalue.push_back(toString(iter->second));
						}
					}
					else return;
					for(int i=0;i<vecSSum.size();i++)
					{
						vecSSum[i].text=vecvalue[i];
						vecSSum[i].Update();
					}
				}
			}
		}
	}
	catch(ExpressionExcept error)
	{
		CArxHelper::ShowMessage(error.what());
	}
}
/*
	*�������ܣ�����С��λ����
	*�������ڣ�2013-03-22
	*�������ڣ�2013-03-22
*/
void CmdHelper::BAT_UC_SDot()
{
	CArxHelper::ShowMessage("\n����������С��λ�������ѡ��һ���ı�:");
	vector<CDText> vecDText=CEntitySelector::GetDText();
	for (int i=0;i<vecDText.size();i++)
	{
		if(StringHelper::isDouble(vecDText[i].text))
		{
			double value=toDouble(StringHelper::parseDouble(vecDText[i].text));
			string result=toString(value);
			vecDText[i].text=result;
			vecDText[i].Update();
		}
	}
}
/*
	*�������ܣ�����Сԭ��Ĵ�С
	*�������ڣ�2013-06-15
	*�������ڣ�2013-06-15
*/
void CmdHelper::BAT_UC_SDotSize()
{
	CArxHelper::ShowMessage("\n���������øֽ�СԲ��뾶�����ѡ��һ��СԲ��:");
	vector<CDot> vecDText=CEntitySelector::GetDot();
	if(vecDText.size()>0)
	{
		vector<double> vecRadius=CArxHelper::GetDouble("\n������СԲ���⾶��",1);
		if(vecRadius.size()<1)return;
		for (int i=0;i<vecDText.size();i++)
		{
			vecDText[i].radius=vecRadius[0]/4;
			vecDText[i].width=vecRadius[0]/2;
			vecDText[i].Update();
		}
	}
}
/*
	*�������ܣ�ȡֱ�߳���
	*�������ڣ�2013-03-22
	*�������ڣ�2013-03-22
*/
void CmdHelper::BAT_UC_GetLineLen()
{
	vector<string> vecDText;
	CArxHelper::ShowMessage("\n�����û�ȡֱ�߳������ѡ��һ��ֱ�ߣ�");
	vector<CLine> vecLine=CEntitySelector::GetLine();
	if(vecLine.size()>0)
	{
		EntitySort(vecLine);
		for(int i=0;i<vecLine.size();i++)
		{
			vecDText.push_back(toString(vecLine[i].GetLength()*100));
		}
		if(vecDText.size()>0)
		{
			CArxHelper::ShowMessage("\nѡ��Ҫ�洢ֱ�߳��ȵ��ı���");
			vector<CDText> selected=CEntitySelector::GetDText();
			if(vecDText.size()!=vecLine.size())
				CArxHelper::ShowMessage("ע�⣺���߸�������ȡ�");
			EntitySort(selected);
			for (int i=0;i<selected.size();i++)
			{
				selected[i].text=vecDText[i%vecDText.size()];
				selected[i].Update();
			}
		}
	}
}
/*
	*�������ܣ�������ȼ�����
	*�������ڣ�2013-06-04
	*�������ڣ�2013-06-04
*/
void CmdHelper::BAT_UC_Split()
{
	CArxHelper::ShowMessage("\n�����õȼ������ֱ�������ѡ��һ��ֱ�ߣ�");
	vector<CLine> vec=CEntitySelector::GetLine();
	if(vec.size()<2)return;
	EntitySort(vec);
	double dx=-(vec.front().x-vec.back().x)/(vec.size()-1);
	double dy=-(vec.front().y-vec.back().y)/(vec.size()-1);
	double xc=vec.front().x;
	double yc=vec.front().y;
	for(int i=0;i<vec.size();i++)
	{
		double x0=vec[i].x;
		double y0=vec[i].y;
		vec[i].x1+=dx*i+xc-x0;
		vec[i].x2+=dx*i+xc-x0;
		vec[i].y1+=dy*i+yc-y0;
		vec[i].y2+=dy*i+yc-y0;
		vec[i].Update();
	}
}
/*
	*�������ܣ�������ȼ�����
	*�������ڣ�2013-06-04
	*�������ڣ�2013-06-04
*/
void CmdHelper::BAT_UC_SplitText()
{
	CArxHelper::ShowMessage("\n�����õȼ�������ı������ѡ��һ���ı���");
	vector<CDText> vec=CEntitySelector::GetDText();
	if(vec.size()<2)return;
	EntitySort(vec);
	double dx=-(vec.front().x-vec.back().x)/(vec.size()-1);
	double dy=-(vec.front().y-vec.back().y)/(vec.size()-1);
	double xc=vec.front().x;
	double yc=vec.front().y;
	vector<double> vecOffset=CArxHelper::GetDouble("\n��������<�ȼ��>��",1);
	if(vecOffset.size()>0)dy=-vecOffset[0];
	for(int i=0;i<vec.size();i++)
	{
		double x0=vec[i].x;
		double y0=vec[i].y;
		//vec[i].x+=dx*i+xc-x0;
		vec[i].y+=dy*i+yc-y0;
		vec[i].Update();
	}
}
/*
	*�������ܣ�������ȼ�����
	*�������ڣ�2013-06-04
	*�������ڣ�2013-06-04
*/
void CmdHelper::BAT_UC_SplitDot()
{
	CArxHelper::ShowMessage("\n�����õȼ������СԲ�������ѡ��һ��СԲ�㣺");
	vector<CDot> vec=CEntitySelector::GetDot();
	if(vec.size()<2)return;
	EntitySort(vec);
	double dx=-(vec.front().x-vec.back().x)/(vec.size()-1);
	double dy=-(vec.front().y-vec.back().y)/(vec.size()-1);
	double xc=vec.front().x;
	double yc=vec.front().y;
	for(int i=0;i<vec.size();i++)
	{
		double x0=vec[i].x;
		double y0=vec[i].y;
		vec[i].x+=dx*i+xc-x0;
		vec[i].y+=dy*i+yc-y0;
		vec[i].Update();
	}
}
/*
	*�������ܣ�������ȼ�����
	*�������ڣ�2013-06-04
	*�������ڣ�2013-06-04
*/
void CmdHelper::BAT_UC_SplitBlock()
{
	CArxHelper::ShowMessage("\n�����õȼ�����п������ѡ��һ��飺");
	vector<CBlock> vec=CEntitySelector::GetBlock();
	if(vec.size()<2)return;
	EntitySort(vec);
	double dx=-(vec.front().x-vec.back().x)/(vec.size()-1);
	double dy=-(vec.front().y-vec.back().y)/(vec.size()-1);
	double xc=vec.front().x;
	double yc=vec.front().y;
	for(int i=0;i<vec.size();i++)
	{
		double x0=vec[i].x;
		double y0=vec[i].y;
		vec[i].x+=dx*i+xc-x0;
		vec[i].y+=dy*i+yc-y0;
		vec[i].Update();
	}
}
/*
	*�������ܣ�ȡ����ֱ�ߵĳ��Ⱥ�
	*�������ڣ�2013-06-08
	*�������ڣ�2013-06-08
*/
//void CmdHelper::BAT_UC_HRB2HPB()
//{
//	vector<CDText> vec=CEntitySelector::GetDText();
//	for(int i=0;i<vec.size();i++)
//	{
//		string str=vec[i].text;
//		for(int j=0;j<str.size();j++)
//			if(str[j]=='&')str[j]='^';
//		vec[i].text=str;
//		vec[i].Update();
//	}
//}
//void CmdHelper::BAT_UC_HPB2HRB()
//{
//	vector<CDText> vec=CEntitySelector::GetDText();
//	for(int i=0;i<vec.size();i++)
//	{
//		string str=vec[i].text;
//		for(int j=0;j<str.size();j++)
//			if(str[j]=='^')str[j]='&';
//		vec[i].text=str;
//		vec[i].Update();
//	}
//}
void CmdHelper::BAT_UC_AligLeft()
{
	CArxHelper::ShowMessage("\n�������ı����������ѡ��һ���ı���");
	vector<CDText> vec=CEntitySelector::GetDText();
	if(vec.size()<2)return;
	if(EntitySort(vec))
	{
		double yc=vec.front().y;
		for(int i=0;i<vec.size();i++)
		{
			vec[i].y=yc;
			vec[i].Update();
		}
	}
	else
	{
		double xc=vec.front().x;
		for(int i=0;i<vec.size();i++)
		{
			vec[i].x=xc;
			vec[i].Update();
		}
	}
}
void CmdHelper::BAT_UC_DoubleChange()
{
	CArxHelper::ShowMessage("\n�����ý����ı������ѡ��һ���ı���");
	vector<CDText> vec=CEntitySelector::GetDText();
	if(vec.size()!=2)return;
	string str=vec[0].text;
	vec[0].text=vec[1].text;
	vec[0].Update();
	vec[1].text=str;
	vec[1].Update();
}
void CmdHelper::BAT_UC_GetNumber()
{
	CArxHelper::ShowMessage("\n��������ȡ���������ѡ��һ���ı���");
	vector<CDText> vec=CEntitySelector::GetDText();
	if(vec.size()<1)return;
	for(int i=0;i<vec.size();i++)
	{
		string str;
		string s=vec[i].text;
		for (int j=0;j<s.length();j++)
		{
			char ch=s[j];
			if(ch>='0'&&ch<='9')
			{
				str.push_back(ch);
			}
			else if (ch=='.'||ch=='+'||ch=='-')
			{
				str.push_back(ch);
			}
			else if(j<s.length()-1&&(ch=='='||ch==':'))
			{
				str.clear();
			}
		}
		vec[i].text=str;
		vec[i].Update();
	}
}
/*
	*�������ܣ��ֽ��������
	*�������ڣ�2013-10-16
	*�������ڣ�2013-10-16
*/
void CmdHelper::BAT_UC_SumSteelBar()
{
	CArxHelper::ShowMessage("\n�����øֽ���������ѡ��һ���ı������Կ�:");
	vector<CDText> vecDText=CEntitySelector::GetDText();
	if(vecDText.size()>0)
	{
		int scale=1;
		bool isMean=false;
		double ret=0;
		for(int i=0;i<vecDText.size();i++)
		{
			double result=0;
			try
			{
				ExpressionCalculator calc;
				if(vecDText[i].text.find("/2")==vecDText[i].text.size()-2)scale=2;
				int pos=vecDText[i].text.find("~");
				if(pos<0)pos=vecDText[i].text.find("��");
				if(pos>-1)
				{
					vecDText[i].text[pos]='+';
					calc.input(vecDText[i].text);
					result=(double)calc.get()/2;
					isMean=true;
				}
				else
				{
					calc.input(vecDText[i].text);
					result=calc.get();
				}
				ret+=result;
			}
			catch(ExpressionExcept& error)
			{
				CArxHelper::ShowMessage(vecDText[i].text+error.what());
				return;
			}
		}
		string valuetext=(isMean?"��":"")+toString(ret*scale);
		//���ģʽΪ�½�
		if(GetOutMode()==CDocData::NEW)
		{
			CTextValueJig* jig=new CTextValueJig();
			jig->doIt(valuetext);
			delete jig;
		}
		//���ģʽΪ�޸Ļ��Զ�
		else
		{
			CArxHelper::ShowMessage("ѡ��Ҫ�޸ĵ����Կ���ı�:");
			static resbuf eb=*acutBuildList(-4,_T("<or"),RTDXF0,_T("TEXT"),RTDXF0,_T("INSERT"),-4,_T("or>"),RTNONE); 
			vector<AcDbObjectId> vecBlockId=CEntitySelector::SelectAcDbObjects(&eb);
			if(vecBlockId.size()>0)
			{
				for(int i=0;i<vecBlockId.size();i++)
				{
					AcDbEntity* pEnt = NULL;
					acdbOpenAcDbEntity(pEnt,vecBlockId[i],AcDb::kForRead);
					if(AcDbBlockReference::desc()==pEnt->isA())
					{
						pEnt->close();
						CArxHelper::SetBlockPr(vecBlockId[i],"����",valuetext);
					}
					else if(AcDbText::desc()==pEnt->isA())
					{
						pEnt->close();
						CArxHelper::SetDTextContent(vecBlockId[i],valuetext);
					}
				}
			}
		}
	}
}