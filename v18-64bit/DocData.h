/********************************************************************
		filename :D:\MyAppProject\���˼�����\����\source\DocData.h
    	description :�ض����ĵ������ݴ洢��
		created	by ������ 2013/3/30 19:20
    	updated	by ������ 2013/3/30 19:20
*********************************************************************/
#pragma once
# include <vector>
# include <string>
using namespace std;
//-----------------------------------------------------------------------------
//----- Here you can store the document / database related data.
class CDocData {
public:
	enum{XX=0,YY=1,XY=2};//����ģʽ
	enum{NEW=0,MODIFY=1,AUTO=2};//���ģʽ
private:
	int m_nTextOutMode;//�������ģʽ��0-�½���1-�޸ģ�2-�޸��Լ�
	int m_nTextSortMode;//��������ģʽ��0-X���꣬1-Y���꣬2-�Զ��ж�
	int m_nTextScale;//С��λ��
	int m_nIsExpand;//�Ƿ�չ����0-��չ������0-չ��
	double m_fTextHeight;//���ָ߶�
	vector<string> m_lstExpression;//���ʽ��¼
public:
	CDocData () ;
	CDocData (const CDocData &data) ;
	~CDocData () ;
	void SaveExpression(string);
	string GetLastExpression();
	int GetOutMode();
	int GetSortMode();
	int GetScale();
	string GetTextHeightStr();
	double GetTextHeight();
	void SetOutMode(int);
	void SetSortMode(int);
	void SetScale(int);
	void SetTextHeight(string);
	void SetTextHeight(double);
} ;
