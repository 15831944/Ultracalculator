/*======================================================================
//        filename :ExpressionCalculator.h
//        description :���ʽ����
//        created by ������   2012-10-17
//        updated by ������   2012-11-09	
//======================================================================*/
#ifndef _EXPRESSIONCALCULATOR_H_H
#define _EXPRESSIONCALCULATOR_H_H

# include <stack>
# include <vector>
# include <map>
# include <string>
# include <iostream>
# include <list>

using namespace std;
class ExpressionCalculator;
struct variant;
variant& operator<<(variant&,const string&);
variant& operator<<(variant&,const double&);
variant& operator<<(variant&,const int&);
variant& operator<<(variant&,const variant&);
string& operator<<(string&,const variant&);
double& operator<<(double&,const variant&);
int& operator<<(int&,const variant&);
/*
 *���͹��ܣ�����������
 *�������ڣ�2012-10-21
 *�������ڣ�2012-11-08
*/
struct Handler
{
	int num;
	int weight;
	int parameter;
	int funcid;
	union _func
	{
		variant (ExpressionCalculator::*vivv)(int,variant,variant);//�������
		int (*giv)();
		double (*gdv)();
		double (*gdd)(double);
		double (*gddd)(double,double);
		double (*gddi)(double,int);
		int (*gid)(double);
		int (*gis)(string);
		string (*gssi)(string,int);
		string (*gssii)(string,int,int);
		string (*gssss)(string,string,string);
	}func;
};
/*
 *�������ܣ��궨���ݵ�����
 *�������ڣ�2012-10-27
 *�������ڣ�2012-11-01
*/
enum{Double,String,Integer,Bool};//��ֵ����
/*
 *���͹��ܣ���������
 *�������ڣ�2012-10-29
 *�������ڣ�2012-11-08
*/
struct variant
{
	int type;
	union _value
	{
		int String;
		double Double;
	}value;
	bool isString(){return type==String?true:false;};
	operator string(){string str;return str<<*this;};
	operator double(){double num;return num<<*this;};
	operator int(){int num;return num<<*this;};
	operator bool(){return value.Double==0?false:true;};
};
/*
 *���͹��ܣ����ʽ����Ԫ��
 *�������ڣ�2012-10-17
 *�������ڣ�2012-11-08
*/
struct Element
{
	int type;
	union _value
	{
		Handler handler;
		variant number;
	}e;
};
/*
 *���͹��ܣ����ʽ�����ඨ��
 *�������ڣ�2012-10-17
 *�������ڣ�2012-11-09
*/
class ExpressionCalculator
{
public:
	ExpressionCalculator();
	//��������
	void input(string);//������ʽ�ַ���
	variant get();//�õ����
	//�߼�����
	void clear();//��ձ���
	variant getVarValue(string);
	void setVarValue(string,variant);
	void setVarValue(string,double);
	void setVarValue(string,string);
	void addVar(string,variant);
	void addVar(string,double);
	void addVar(string,string);
	string getCurrentVarName();
	variant getCurrentVarValue();
	vector<string> getUnknowVar();
	//ȫ�ֳ�Ա
	static double toDouble(string);//�ַ���ת����
	static string toString(double);//�ַ���ת����
	static vector<string>* m_pconst;//��̬ȫ�ֱ���
private:
	enum{giv=1,gdv,gdd,gddd,gddi,vivv,gid,gssi,gssii,gis,gssss};//��������
	enum{operatorsymbol=0,operatorvariant=1};//Ԫ������
	stack<Handler> m_symbolstack;//����ջ
	stack<variant> m_variantstack;//��ֵջ
	list<Element> m_elements;//ɨ����Ԫ��
	vector<string> m_const;//�ַ�����
	map<string,variant> m_varmap;//�����������ӳ��
	list<string> m_varnotmap;//δ��ֵ�ı����б�
	map<string,Handler> m_handlermap;//����ӳ��
	string m_expression;//���ʽֵ
	string m_currentvar;//��ǰ����
	int m_precision;//�������
	void initialize();//��ʼ��
	void calculate();//�������
	void scan();//ɨ��
	void check();//ɨ�����
	bool isSymbol(char);//�Ƿ�Ϊ����
	bool isNumber(char);//�Ƿ�Ϊ���ֻ�С����
	bool isAbc(char);//�Ƿ���ĸ
	int getWeight(char);//������Ȩ�ط���
	Handler getHandler(string);//�õ��������������handler
	double doSymbol(int,double,double);//���������
	variant doSymbol(int,variant,variant);//���������
	double doVar(int);//�������
	void doIt();//handler��������
	void addHandler(string,double (*)());
	void addHandler(string,int (*)());
	void addHandler(string,int (*)(double));
	void addHandler(string,double (*)(double));
	void addHandler(string,double (*)(double,double));
	void addHandler(string,double (*)(double,int));
	void addHandler(string,string (*)(string,int));
	void addHandler(string,string (*)(string,int,int));
	void addHandler(string,int (*)(string));
	void addHandler(string,string (*)(string,string,string));
	string getErrorExpress();
# ifdef _DEBUG
public:
	void output();//����м���
#endif
};
#endif