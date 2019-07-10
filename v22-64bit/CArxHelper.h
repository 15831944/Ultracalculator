#pragma once
#include <string>
#include <vector>
#include "CMultDText.h"
#include "CEntity.h"
using namespace std;
/*
 *���͹��ܣ�arx������
 *�������ڣ�2012-11-11
 *�������ڣ�2012-11-13
*/
class CArxHelper
{
public:
	static CDText GetEntityByObjectId(AcDbObjectId);
	static vector<CDText> GetEntityByObjectId(vector<AcDbObjectId>);
	static AcDbObjectId Draw(CDText);
	static vector<AcDbObjectId> Draw(vector<CDText>);
	static vector<AcDbObjectId> SelectAcDbObjects(struct resbuf*);
	static vector<double> GetDouble(string,int);
	//static vector<CDText> SelectDTextEntity(string msg="\n��ѡ���ı�");
	//static vector<CDText> SelectLineEntity(string msg="\n��ѡ��ֱ��");
	//static resbuf GetFilter(AcRxClass*);
	static void ShowMessage(string,string);
	static void ShowMessage(string);
	static bool PickPoint(AcGePoint3d&,string);
	static void Format(AcDbObjectId,AcDbObjectId);
	static void Format(vector<AcDbObjectId>,vector<AcDbObjectId>);
	static AcGePoint3d wcs2ucs(const AcGePoint3d&);
	static AcGePoint3d ucs2wcs(const AcGePoint3d&);
	static void SetDTextContent(AcDbObjectId id,string content);
	static double SumDText(vector<CDText>);
	static double MultDText(vector<CDText>);
	static double MeanDText(vector<CDText>);
	static double MaxDText(vector<CDText>);
	static double MinDText(vector<CDText>);
	static bool CArxHelper::SetBlockPr(AcDbObjectId id,string tag,string text);
};
/*
 *���͹��ܣ�jig��
 *�������ڣ�2012-11-13
 *�������ڣ�2012-11-13
*/
class CTextValueJig:public AcEdJig
{
public:
	CTextValueJig(const vector<AcDbObjectId>&,const vector<string>&);
	CTextValueJig();
	void doIt(string);
	void doIt(const vector<AcDbObjectId>&,const vector<string>&);
	void doIt(AcGeVector3d,const vector<string>&);
	virtual DragStatus sampler();
	virtual Adesk::Boolean update();
	virtual AcDbEntity* entity() const;
private:
	AcGePoint3d m_basepoint;//���ڼ�¼ѡ���е�һ���ı������꣬û��ѡ������Ϊԭ�㡣
	AcGePoint3d m_endpoint;//��ʾ����϶�ʱ���ʵʱλ�á�
	AcGePoint3d m_startpoint;//�϶�ǰѡ�����㡣
	CMultDText* m_pEntity;//������ʵ�塣
};