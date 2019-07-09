/*
 *�������ܣ��Զ��嵥���ı����϶���
 *�������ڣ�2013-03-25
 *�������ڣ�2013-03-25
*/
#pragma once
#include <string>
#include <vector>
using namespace std;
class CMultDText : public AcDbEntity
{
public:
	CMultDText(const vector<string>&,const AcGeVector3d offset);//ֱ�Ӹ�һ��ƫ������
	CMultDText(const vector<string>&,const vector<AcDbObjectId>&);//����һ��ģ��
	~CMultDText();
#if _MSC_VER>1400
	virtual Adesk::Boolean CMultDText::subWorldDraw (AcGiWorldDraw*);
#else
	virtual Adesk::Boolean worldDraw (AcGiWorldDraw*);
#endif
	void setBasePoint(AcGePoint3d);
	void appendToCurrentSpace();
	void clear();
private:
	vector<AcDbText*> m_vecText;
	vector<AcGeVector3d> m_vecOffset;
	AcGePoint3d m_basePoint;
};