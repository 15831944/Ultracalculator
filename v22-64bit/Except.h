/*======================================================================
//        filename :ExpressionCalculator.h
//        description :���ʽ����
//        created by ������   2012-10-17
//        updated by ������   2012-11-09	
//======================================================================*/
#ifndef _EXPRESSIONEXCEPT_H_H
#define _EXPRESSIONEXCEPT_H_H
# include <string>
using namespace std;
/*
 *���͹��ܣ����ʽ�쳣��
 *�������ڣ�2012-11-08
 *�������ڣ�2012-11-08
*/
class ExpressionExcept
{
private:
	string error;
public:
	string what(){return error;};
	ExpressionExcept(string str){error=str;};
	ExpressionExcept(string str,string name){error=str.replace(str.find("%s"),2,name);};
};
#endif