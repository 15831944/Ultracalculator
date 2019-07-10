/*======================================================================
//        filename :CmdHandler.h
//        description :���������Ŀ���ǽ��߼������ֿ�
//        created by ������   2013-03-26
//        updated by ������   2013-03-26	
//======================================================================*/
#ifndef _EXPRESSIONCMDHANDLER_H_H
#define _EXPRESSIONCMDHANDLER_H_H
#include "Express.h"
#include "CArxHelper.h"
#include <map>
#include <vector>

class CmdHandler
{
private:
	enum {MAX=255,MAXSELECT=1000,MAXEXPRESSLENGTH=1024} ;
	string toString(double);
	string toString(variant);
	void DTextSort(vector<CDText>&);
	int GetOutMode();
	int GetSortMode();
	map<string,void(*)()> m_mapfunc;
	void initialize();
public:
	CmdHandler();
	void run(string);
	void parse(string);
};
#endif