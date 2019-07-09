#pragma once
#include <string>
using namespace std;
/*
 *���͹��ܣ�����
 *�������ڣ�2013-06-04
 *�������ڣ�2013-06-04
*/
class CSelectedEntity
{
public:
	AcDbObjectId id;
	double x;
	double y;
	double z;
public:
	virtual bool Update()=0;
	virtual bool GetEntity(AcDbObjectId)=0;
};
/*
 *���͹��ܣ���ģ����ѡ����ı����󣬿����ǡ�ֱ�ߡ�СԲ�㡢������
 *�������ڣ�2013-06-04
 *�������ڣ�2013-06-04
*/
class CDText:public CSelectedEntity
{
public:
	CDText();
	CDText(AcDbObjectId,string);
	string text;
	virtual bool Update();
	virtual bool GetEntity(AcDbObjectId);
};
/*
 *���͹��ܣ���ģ����ѡ���ֱ�߶���
 *�������ڣ�2013-06-04
 *�������ڣ�2013-06-04
*/
class CLine:public CSelectedEntity
{
public:
	double x1;
	double y1;
	double z1;
	double x2;
	double y2;
	double z2;
	virtual bool Update();
	virtual bool GetEntity(AcDbObjectId);
	double GetLength();
};
/*
 *���͹��ܣ���ģ����ѡ���СԲ�����
 *�������ڣ�2013-06-04
 *�������ڣ�2013-06-04
*/
class CDot:public CSelectedEntity
{
public:
	double radius;
	double width;
	virtual bool Update();
	virtual bool GetEntity(AcDbObjectId);
};
/*
 *���͹��ܣ���ģ����ѡ��Ŀ����
 *�������ڣ�2013-06-04
 *�������ڣ�2013-06-04
*/
class CBlock:public CSelectedEntity
{
public:
	virtual bool Update();
	virtual bool GetEntity(AcDbObjectId);
};