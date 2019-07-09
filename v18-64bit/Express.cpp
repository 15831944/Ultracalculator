/*======================================================================
//        filename :ExpressionCalculator.cpp
//        description :���ʽ����
//        created by ������   2012-10-17
//        updated by ������   2012-11-09			
//======================================================================*/
# include "Express.h"
#include "Except.h"
#include "function.h"
#include <cmath>
#include <string>
#include <sstream>
# define MAXARGUMENTNUMBER 3

using namespace::std;
/*
 *�������ܣ�stringתvariant
 *�������ڣ�2012-10-20
 *�������ڣ�2012-10-25
*/
variant& operator<<(variant& var,const string& str)
{
	vector<string>* g_pconst=ExpressionCalculator::m_pconst;
	var.type=String;
	int pos=-1;
	for(int i=0;i<g_pconst->size();i++)
	{
		if(str==g_pconst->at(i))
		{
			pos=i;
			break;
		}
	}
	if(pos!=-1)
	{
		var.value.String=pos;
	}
	else
	{
		g_pconst->push_back(str);
		var.value.String=g_pconst->size()-1;
	}
	return var;
}
/*
 *�������ܣ�doubleתvariant
 *�������ڣ�2012-10-20
 *�������ڣ�2012-10-25
*/
variant& operator<<(variant& var,const double& number)
{
	var.type=Double;
	var.value.Double=number;
	return var;
}
/*
 *�������ܣ�intתvariant
 *�������ڣ�2012-10-20
 *�������ڣ�2012-10-25
*/
variant& operator<<(variant& var,const int& number)
{
	var.type=Integer;
	var.value.Double=number;
	return var;
}
/*
 *�������ܣ�variantתvariant
 *�������ڣ�2012-10-20
 *�������ڣ�2012-10-25
*/
variant& operator<<(variant& var,const variant& number)
{
	var.type=number.type;
	var.value=number.value;
	return var;
}
/*
 *�������ܣ�variantתstring
 *�������ڣ�2012-10-20
 *�������ڣ�2012-10-25
*/
string& operator<<(string& str,const variant& var)
{
	vector<string>* g_pconst=ExpressionCalculator::m_pconst;
	switch(var.type)
	{
	case String:
		str=g_pconst->at(var.value.String);break;
	case Double:
	case Integer:
		str=func::toString(var.value.Double);break;
	case Bool:
		str=var.value.Double==0?"false":"true";break;
	default:
		throw(ExpressionExcept("��������δ֪"));
	}
	return str;
}
/*
 *�������ܣ�variantתdouble
 *�������ڣ�2012-10-20
 *�������ڣ�2012-10-26
*/
double& operator<<(double& number,const variant& var)
{
	vector<string>* g_pconst=ExpressionCalculator::m_pconst;
	if(var.type==String)
	{
		string str=g_pconst->at(var.value.String);
		number=func::toDouble(str);
	}		
	else number=var.value.Double;
	return number;
}
/*
 *�������ܣ�variantתint
 *�������ڣ�2012-10-20
 *�������ڣ�2012-10-25
*/
int& operator<<(int& number,const variant& variant)
{
	double num;
	number=(num<<variant,(int)(num+0.5));
	return number;
}
/*
 *�������ܣ��ַ���ת���֣�֧�ֿ�ѧ������ʾ������
 *�������ڣ�2012-10-20
 *�������ڣ�2012-10-30
*/
double ExpressionCalculator::toDouble(string str)
{
	return func::toDouble(str);
}
/*
 *�������ܣ�����ת�ַ���
 *�������ڣ�2012-10-20
 *�������ڣ�2012-11-01
*/
string ExpressionCalculator::toString(double num)
{
	return func::toString(num);
}
/*
 *�������ܣ�ָ���ַ������б��ָ��
 *�������ڣ�2012-11-09
 *�������ڣ�2012-11-09
*/
vector<string>* ExpressionCalculator::m_pconst=NULL;
/*
 *�������ܣ����캯��
 *�������ڣ�2012-10-17
 *�������ڣ�2012-10-25
*/
ExpressionCalculator::ExpressionCalculator()
{
	initialize();
}
/*
 *�������ܣ�����µı��������Ҹ�ֵ
 *�������ڣ�2012-11-08
 *�������ڣ�2012-11-08
*/
void ExpressionCalculator::addVar(string name,variant value)
{
	list<string>::iterator iter;
	//�����δ֪���������еĻ����Ȱ����������ɾ��
	for(iter=m_varnotmap.begin();iter!=m_varnotmap.end();++iter)
	{
		if((*iter)==name)m_varnotmap.erase(iter);
	}
	//��ӵ���֪����������ȥ
	m_varmap[name]=value;
}
/*
 *�������ܣ�����µı��������Ҹ�ֵ
 *�������ڣ�2012-11-08
 *�������ڣ�2012-11-08
*/
void ExpressionCalculator::addVar(string name,double value)
{
	variant var;
	var<<value;
	addVar(name,var);
}
/*
 *�������ܣ�����µı��������Ҹ�ֵ
 *�������ڣ�2012-11-08
 *�������ڣ�2012-11-08
*/
void ExpressionCalculator::addVar(string name,string value)
{
	variant var;
	var<<value;
	addVar(name,var);
}
/*
 *�������ܣ��������б�����ֵ
 *�������ڣ�2012-11-09
 *�������ڣ�2012-11-09
*/
void ExpressionCalculator::setVarValue(string var,variant value)
{
	//�������֪����������û�У���ô��δ֪������������û�У��������
	if(m_varmap.find(var)==m_varmap.end())
	{
		bool hasTheName=false;
		list<string>::iterator iter;
		for(iter=m_varnotmap.begin();iter!=m_varnotmap.end();++iter)
		{
			if((*iter)==var)
			{
				m_varmap[var]=value;
				m_varnotmap.erase(iter);
				hasTheName=true;
				break;
			}
		}
		if(!hasTheName)throw(ExpressionExcept("����%sδ����",var));
	}
	else m_varmap[var]=value;
}
/*
 *�������ܣ��������б�����ֵ
 *�������ڣ�2012-11-08
 *�������ڣ�2012-11-08
*/
void ExpressionCalculator::setVarValue(string name,double value)
{
	variant var;
	var<<value;
	setVarValue(name,var);
}
/*
 *�������ܣ��������б�����ֵ
 *�������ڣ�2012-11-09
 *�������ڣ�2012-11-09
*/
void ExpressionCalculator::setVarValue(string name,string value)
{
	variant var;
	var<<value;
	setVarValue(name,var);
}
/*
 *�������ܣ��õ���ǰ����������
 *�������ڣ�2012-11-08
 *�������ڣ�2012-11-08
*/
string ExpressionCalculator::getCurrentVarName()
{
	return m_currentvar;
}
/*
 *�������ܣ��õ���ǰ������ֵ
 *�������ڣ�2012-11-08
 *�������ڣ�2012-11-08
*/
variant ExpressionCalculator::getCurrentVarValue()
{
	return getVarValue(m_currentvar);
}
/*
 *�������ܣ��õ�ָ��������ֵ
 *�������ڣ�2012-11-09
 *�������ڣ�2012-11-09
*/
variant ExpressionCalculator::getVarValue(string name)
{
	if(m_varmap.find(name)==m_varmap.end())throw(ExpressionExcept("����%s������",name));
	try
	{
		//ͨ����ջ��ջ�����ַ������ʽ��ֵ
		calculate();
	}
	catch(ExpressionExcept&error)
	{
		while(!m_symbolstack.empty())m_symbolstack.pop();
		while(!m_variantstack.empty())m_variantstack.pop();
		throw(error);
	}
	//���򷵻ظñ�����ֵ
	return m_varmap[name];
}
/*
 *�������ܣ��õ�ָ������������
 *�������ڣ�2012-11-09
 *�������ڣ�2012-11-09
*/
vector<string> ExpressionCalculator::getUnknowVar()
{
	vector<string> ret;
	list<string>::iterator iter;
	for(iter=m_varnotmap.begin();iter!=m_varnotmap.end();++iter)
	{
		ret.push_back(*iter);
	}
	return ret;
}
/*
 *�������ܣ������ַ������ʽ
 *�������ڣ�2012-11-08
 *�������ڣ�2012-11-08
*/
void ExpressionCalculator::input(string expression)
{
	//������Ĭ��Ϊans
	string first="ans";
	string second;
	int count=0;
	//���Ⱥ���ߵı����͵Ⱥ��ұߵı��ʽ�������
	for(int i=0;i<expression.size();i++)
	{
		if(expression[i]=='=')
		{
			count++;
			if(!second.empty())first=second;
			second.clear();
			continue;
		}
		second.push_back(expression[i]);
	}
	if(second.empty())throw(ExpressionExcept("���ʽ����Ϊ��"));
	//���ֶ�������򱨴�
	if(count>1)throw(ExpressionExcept("�ж�����ڷ���"));
	else
	{
		int parenthesis=0;
		//��������Ƿ�ƥ��
		for(int i=0;i<second.size();i++)
		{
			if(second[i]=='(')parenthesis++;
			if(second[i]==')')parenthesis--;
			if(parenthesis<0)throw(ExpressionExcept("���Ų�ƥ��"));
		}
		if(parenthesis!=0)throw(ExpressionExcept("���Ų�ƥ��"));
	}
	//����������ַ������
	m_expression.clear();
	//����������ַ���д��((var)=(���ʽ))����ʽ
	m_expression.append("(");
	m_expression.append(first);
	m_expression.append("=(");
	m_expression.append(second);
	m_expression.append("))");
	//��¼��ǰ�ı�����
	m_currentvar=first;
	//����������������,�����
	if(m_varmap.find(first)==m_varmap.end())addVar(first,0);
	//ɨ��֮ǰ���Ԫ������Ķ���
	m_elements.clear();
	//ɨ���������ַ���
	try
	{
		scan();
	}
	catch(ExpressionExcept& error)
	{
		//ɨ����������Ԫ������Ķ���
		m_elements.clear();
		throw(error);
	}
}
/*
 *�������ܣ��õ����������߱�����ans����ֵ
 *�������ڣ�2012-10-30
 *�������ڣ�2012-11-08
*/
variant ExpressionCalculator::get()
{
	return getVarValue("ans");
}
/*
 *�������ܣ��������
 *�������ڣ�2012-10-19
 *�������ڣ�2012-11-09
*/
void ExpressionCalculator::calculate()
{
	//����֮ǰ������ջ����ֵջ��Ҫ���,�Ա��ں����У��
	while(!m_symbolstack.empty())m_symbolstack.pop();
	while(!m_variantstack.empty())m_variantstack.pop();
	//��̬Ȩ�أ����ڼ�¼�����ѽ���Ĳ���
	int weight=0;
	list<Element>::iterator iter;
	//˳�����Ԫ������
	for(iter=m_elements.begin();iter!=m_elements.end();++iter)
	{
		Element element=*iter;
		//�ж��Ƿ�Ϊ���������������
		if(element.type==operatorsymbol)
		{
			Handler handler=element.e.handler;
			//���Ϊ�����ţ���������ջ������̬Ȩ�ؼ�1
			if(handler.parameter=='(')
			{
				m_symbolstack.push(element.e.handler);
				weight++;
			}
			//���Ϊ�����ţ���������ջջ���Ĳ�������ֱ������������Ϊֹ
			else if(handler.parameter==')')
			{
				//����������ʱ������ǰ���������в�����
				while(m_symbolstack.top().parameter!='(')doIt();
				//��󵯳������ţ�����̬Ȩ�ؼ�1
				m_symbolstack.pop();
				weight--;
			}
			//�Ǻ���������������ѧ����������׼����ջ
			else
			{
				//����ջ�Ĳ��������ȼ�=����Ȩ��+��̬Ȩ��
				element.e.handler.weight+=weight;
				//��ջǰ������ǰջ���������ȼ��ߵĲ�����
				while(m_symbolstack.top().parameter!='(' && element.e.handler.weight <= m_symbolstack.top().weight)doIt();
				//�²�������ջ
				m_symbolstack.push(element.e.handler);
			}
		}
		//����ֵ
		else
		{
			//��ֵ��ջ
			m_variantstack.push(element.e.number);
		}
	}
	//������һ��������
	if(m_variantstack.size()!=1||m_symbolstack.size()!=0)throw(ExpressionExcept("��ջ��ƽ��"+getErrorExpress()));
}
/*
 *�������ܣ�ɨ����ʽ
 *�������ڣ�2012-10-19
 *�������ڣ�2013-03-21
*/
void ExpressionCalculator::scan()
{
	//ɨ��ǰ���λ�ñ���
	m_varnotmap.clear();
	//ɨ��ǰ���Ԫ������
	m_elements.clear();
	//��¼��ǰ���������Ĳ�������
	stack<int> arguments;
	//��¼��ǰ�����Ĳ����б������Ѿ�����������������
	stack<int> parenthesis;
	//���ó�ʼֵ
	arguments.push(1);
	parenthesis.push(1);
	//˳�������������ʽ��ÿ���ַ�
	for(int i=0;i<m_expression.size();i++)
	{
		//ȡ�õ�ǰ�ַ�
		char ch=m_expression[i];
		//�ж�����ѧ������+ - * /��
		if(isSymbol(ch))
		{
			Element element;
			element.type=operatorsymbol;
			//����Ƕ��ţ����������ź������ţ����Һ�������������1
			if(ch==',')
			{
				element.e.handler=getHandler(")");
				m_elements.push_back(element);
				element.e.handler=getHandler("(");
				m_elements.push_back(element);
				arguments.top()=arguments.top()-1;
				continue;
			}
			//����������ţ����ż�����1
			else if(ch=='(')parenthesis.top()=parenthesis.top()+1;
			//����������ţ����ż�����1
			else if(ch==')')
			{
				parenthesis.top()=parenthesis.top()-1;
				//�ж����ż�������0���Ҳ�������С�ڵ���1����Ϊ0��������1��������û�ж��ţ�����˵������ɨ�����
				if(parenthesis.top()==0 && arguments.top()<=1)
				{
					//����������
					element.e.handler=getHandler(")");
					m_elements.push_back(element);
					//�������������ż�������
					arguments.pop();
					parenthesis.pop();
				}
			}
			string str;
			str.push_back(ch);
			//ȡ�������Ĵ�����
			element.e.handler=getHandler(str);
			m_elements.push_back(element);
		}
		//�ж���Ӣ����ĸ
		else if(isAbc(ch))
		{
			Element element;
			//Ԫ����������Ϊ������
			element.type=operatorsymbol;
			string strVar;
			//��һ������Ӣ����ĸ����
			while(isAbc(m_expression[i])||isNumber(m_expression[i]))
				strVar.push_back(m_expression[i++]);
			//������������������ŵĻ�������������
			if(m_expression[i]!='(')
			{
				//�����������������ֵ�������򱨴�
				if(!isSymbol(m_expression[i]))throw(ExpressionExcept("����%sʹ�ò���ȷ",strVar));
				//����ǰ�����������
				element.e.handler=getHandler("(");
				m_elements.push_back(element);
				//���������������ڣ���ӵ�δ֪�����б�
				if(m_varmap.find(strVar)==m_varmap.end())
				{
					//2013-3-21�޸ģ�ʹδ֪���������ظ����
					bool found=false;
					list<string>::iterator iter;
					for(iter=m_varnotmap.begin();iter!=m_varnotmap.end();++iter)
					{
						if((*iter)==strVar)found=true;
					}
					if(!found)m_varnotmap.push_back(strVar);
				}
				//Ϊ������Ӵ�����������һ������Ŀմ�����
				Handler handler;
				{
					handler.num=0;
					handler.weight=0;
					handler.funcid=0;//�ؼ���ͨ��funcidΪ0���ж��Ǳ���
					variant var;var<<strVar;
					handler.parameter=var.value.String;
				}
				element.e.handler=handler;
				m_elements.push_back(element);
				//�����������������
				element.e.handler=getHandler(")");
				//���ñ�������Ԫ�ر�
				m_elements.push_back(element);
				//��Ϊ����һ����ǰ��飬����Ҫ����һ���ַ�
				i--;
			}
			//�������Ǻ�������
			else
			{
				string strFunc=strVar;
				//����ǰ�����������
				element.e.handler=getHandler("(");
				m_elements.push_back(element);
				//����ú����Ĵ�����
				element.e.handler=getHandler(strFunc);	
				m_elements.push_back(element);
				//��Ӳ��������������ż�����
				arguments.push(element.e.handler.num);
				parenthesis.push(0);
				//��Ϊ����һ����ǰ��飬����Ҫ����һ���ַ�
				i--;
			}
		}
		//������
		else if(isNumber(ch))
		{
			Element element;
			string strNumber;
			//��һ��������һ���Զ���
			while(isNumber(m_expression[i]))
				strNumber.push_back(m_expression[i++]);
			//�ж��ǲ��ǿ�ѧ��������ʾ������
			if(m_expression[i]=='e'||m_expression[i]=='E')
			{
				//����e��ѹ��
				strNumber.push_back(m_expression[i++]);
				//�ж�e�����ǲ������ֻ���������
				if(m_expression[i]=='+'||m_expression[i]=='-'||isNumber(m_expression[i]))
				{
					//��������ѹ��
					strNumber.push_back(m_expression[i++]);
					//��֮��һ��������ѹ��
					while(isNumber(m_expression[i]))
						strNumber.push_back(m_expression[i++]);
					//��Ϊ����һ����ǰ��飬����Ҫ����һ���ַ�
					i--;
				}
				//���򱨴�
				else throw("��ֵ��ʾ����");
			}
			else
			{
				//��Ϊ����һ����ǰ��飬����Ҫ����һ���ַ�
				i--;
			}
			//Ԫ����������Ϊ��ֵ
			element.type=operatorvariant;
			//ת��Ϊdouble
			element.e.number<<toDouble(strNumber);
			m_elements.push_back(element);
		}
		//���ַ���
		else if('"'==ch)
		{
			Element element;
			string str;
			//��˫�����е�����ȡ��
			while(m_expression[++i]!='"'&& i<m_expression.size())
				str.push_back(m_expression[i]);
			//Ԫ����������Ϊ��ֵ
			element.type=operatorvariant;
			element.e.number<<str;
			m_elements.push_back(element);
		}
	}
	if(arguments.size()!=1||parenthesis.size()!=1)throw(ExpressionExcept("����������ƥ��"+getErrorExpress()));
	check();
}
/*
 *�������ܣ�ɨ���ļ��
 *�������ڣ�2012-11-07
 *�������ڣ�2012-12-04
*/
void ExpressionCalculator::check()
{
	list<Element>::iterator iter;
	bool hasSymbol=false;
	//��������������ź���������
	for(iter=m_elements.begin();iter!=m_elements.end();++iter)
	{
		if(iter->type==operatorsymbol)
		{
			if(iter->e.handler.parameter=='(')
			{
				hasSymbol=true;
				continue;
			}
			if(hasSymbol && (iter->e.handler.parameter=='+'||iter->e.handler.parameter=='-'))
			{
				Element element;
				element.type=operatorvariant;
				element.e.number<<0.0;
				m_elements.insert(iter,element);
				++iter;
			}
			hasSymbol=false;
		}
		else hasSymbol=false;
	}
}
/*
 *�������ܣ���ձ���
 *�������ڣ�2012-10-21
 *�������ڣ�2012-11-09
*/
void ExpressionCalculator::initialize()
{
	m_pconst=&m_const;
	//���Ǻ���
	addHandler("sin",func::sin);
	addHandler("asin",func::asin);
	addHandler("sinh",func::sinh);
	addHandler("cos",func::cos);
	addHandler("acos",func::acos);
	addHandler("cosh",func::cosh);
	addHandler("tan",func::tan);
	addHandler("tanh",func::tanh);
	addHandler("atan",func::atan);
	addHandler("atan2",func::atan2);
	//��ָ����
	addHandler("ln",func::ln);
	addHandler("log",func::log);
	addHandler("log10",func::log10);
	addHandler("exp",func::exp);
	addHandler("sqrt",func::sqrt);
	addHandler("power",func::power);
	//�ǶȺ���
	addHandler("pi",func::pi);
	addHandler("degrees",func::degrees);
	addHandler("radians",func::radians);
	//ȡ������
	addHandler("int",func::integer);
	addHandler("floor",func::floor);
	addHandler("ceiling",func::ceiling);
	//��������
	addHandler("sign",func::sign);
	addHandler("mod",func::mod);
	addHandler("fact",func::fact);
	addHandler("rand",func::rand);
	addHandler("abs",func::abs);
	//�ַ�������
	addHandler("left",func::left);
	addHandler("right",func::right);
	addHandler("mid",func::mid);
	addHandler("len",func::len);
	addHandler("substitute",func::substitute);
	//����רҵ����
	addHandler("kg",func::kg);
}
/*
 *�������ܣ���������ʼ��
 *�������ڣ�2012-10-21
 *�������ڣ�2012-11-09
*/
void ExpressionCalculator::clear()
{
	//����ַ������б�
	m_const.clear();
	//�����֪����
	m_varmap.clear();
	//������ʽ�ַ���
	m_expression.clear();
	//�����ǰ����
	m_currentvar.clear();
	//���δ֪����
	m_varnotmap.clear();
}
/*
 *�������ܣ�ִ�д�����
 *�������ڣ�2012-10-19
 *�������ڣ�2012-11-07
*/
void ExpressionCalculator::doIt()
{
	variant var;
	variant args[MAXARGUMENTNUMBER];
	if(m_symbolstack.empty())throw(ExpressionExcept("���ʽ����"));
	Handler handler=m_symbolstack.top();
	//���ݲ���������������
	int i=handler.num-1;
	while(i>=0)
	{	
		if(m_variantstack.empty())throw(ExpressionExcept("���ʽ����"));
		args[i--]=m_variantstack.top();
		m_variantstack.pop();
	}
	//������
	string varname;
	switch(handler.funcid)
	{
	//�Ǳ���
	case 0:
		//�õ�������
		varname=m_const[handler.parameter];
		//�������Ƿ����
		if(m_varmap.find(varname)==m_varmap.end())throw(ExpressionExcept("����%sδ����",varname));
		//ȡ��������ֵ
		var=m_varmap[varname];break;
	case gdv:
		var<<(*handler.func.gdv)();break;
	case gid:
		var<<(*handler.func.gid)(args[0]);break;
	case giv:
		var<<(*handler.func.giv)();break;
	case gdd:
		var<<(*handler.func.gdd)(args[0]);break;
	case gddd:	
		var<<(*handler.func.gddd)(args[0],args[1]);break;
	case gddi:
		var<<(*handler.func.gddi)(args[0],args[1]);break;
	case vivv:
		var<<(this->*handler.func.vivv)(handler.parameter,args[0],args[1]);break;
	case gssi:
		var<<(*handler.func.gssi)(args[0],args[1]);break;
	case gssii:
		var<<(*handler.func.gssii)(args[0],args[1],args[2]);break;
	case gis:
		var<<(*handler.func.gis)(args[0]);break;
	case gssss:
		var<<(*handler.func.gssss)(args[0],args[1],args[2]);break;
	default:
		throw(ExpressionExcept("���޷�ʶ��Ĳ��������ߺ���"));
	}
	m_variantstack.push(var);
	m_symbolstack.pop();
}
/*
 *�������ܣ�������������
 *�������ڣ�2012-10-20
 *�������ڣ�2012-11-08
*/
variant ExpressionCalculator::doSymbol(int symbol,variant v1,variant v2)
{
	variant ret;
	switch(symbol)
	{
	case '+':
		return ret<<(double)v1+(double)v2;
	case '-':
		return ret<<(double)v1-(double)v2;
	case '*':
		return ret<<(double)v1*(double)v2;
	case '/':
		if(((double)v2)==0)throw(ExpressionExcept("�����쳣"));
		return ret<<(double)v1/(double)v2;
	case '^':
		return ret<<pow((double)v1,(double)v2);
	case '%':
		return ret<<fmod((double)v1,(double)v2);
	case '&':
		return ret<<(string)v1+(string)v2;
	case '=':
		m_varmap[m_currentvar]=v2;
		return v2;
	default:
		throw(ExpressionExcept("δ֪������"));
	}
}
/*
 *�������ܣ��õ��������Ĺ̶����ȼ�
 *�������ڣ�2012-10-19
 *�������ڣ�2012-11-01
*/
int ExpressionCalculator::getWeight(char symbol)
{
	switch(symbol)
	{
	case '=':
		return -1;
	case '&':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '%':
		return 3;
	case '^':
		return 4;
	default:
		return 0;
	}
}
/*
 *�������ܣ��õ�����������
 *�������ڣ�2012-10-20
 *�������ڣ�2012-11-09
*/
Handler ExpressionCalculator::getHandler(string str)
{
	if(str.empty())throw(ExpressionExcept("�õ�������ʧ��"));
	char ch=str[0];
	//�ǲ�����
	if(isSymbol(ch))
	{
		Handler handler;
		handler.num=2;
		handler.parameter=ch;
		handler.weight=getWeight(ch);
		handler.funcid=vivv;
		handler.func.vivv=&ExpressionCalculator::doSymbol;
		return handler;
	}
	string funcname;
	for(int i=0;i<str.length();i++)
	{
		funcname.push_back(tolower(str[i]));
	}
	if(m_handlermap.find(funcname)==m_handlermap.end())throw(ExpressionExcept("δ֪����%s",str));
	return m_handlermap[funcname];
}
/*
 *�������ܣ��ж��Ƿ���Ӣ����ĸ
 *�������ڣ�2012-10-19
 *�������ڣ�2012-10-20
*/
bool ExpressionCalculator::isAbc(char ch)
{
	if((ch>='a' && ch<='z')||(ch>='A' && ch<='Z'))
	{
		return true;
	}
	return false;
}
/*
 *�������ܣ��ж��Ƿ��Ƿ���
 *�������ڣ�2012-10-19
 *�������ڣ�2012-10-20
*/
bool ExpressionCalculator::isSymbol(char ch)
{
	switch(ch)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '^':
	case '(':
	case ')':
	case ',':
	case '&':
	case '=':
		return true;
	default:
		return false;
	}
}
/*
 *�������ܣ��ж��Ƿ�������
 *�������ڣ�2012-10-19
 *�������ڣ�2012-10-20
*/
bool ExpressionCalculator::isNumber(char ch)
{
	if((ch>='0' && ch<='9')||(ch=='.'))
	{
		return true;
	}
	return false;
}
/*
 *�������ܣ���Ӻ���������
 *�������ڣ�2012-11-08
 *�������ڣ�2012-11-08
*/
void ExpressionCalculator::addHandler(string name,double (*func)(double))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gdd;
	handler.num=1;
	handler.func.gdd=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *�������ܣ���Ӻ���������
 *�������ڣ�2012-11-08
 *�������ڣ�2012-11-08
*/
void ExpressionCalculator::addHandler(string name,double (*func)())
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gdv;
	handler.num=0;
	handler.func.gdv=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *�������ܣ���Ӻ���������
 *�������ڣ�2012-11-08
 *�������ڣ�2012-11-08
*/
void ExpressionCalculator::addHandler(string name,int (*func)())
{
	Handler handler;
	handler.weight=0;
	handler.funcid=giv;
	handler.num=0;
	handler.func.giv=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *�������ܣ���Ӻ���������
 *�������ڣ�2012-11-08
 *�������ڣ�2012-11-08
*/
void ExpressionCalculator::addHandler(string name,int (*func)(double))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gid;
	handler.num=1;
	handler.func.gid=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *�������ܣ���Ӻ���������
 *�������ڣ�2012-11-08
 *�������ڣ�2012-11-08
*/
void ExpressionCalculator::addHandler(string name,double (*func)(double,double))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gddd;
	handler.num=2;
	handler.func.gddd=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *�������ܣ���Ӻ���������
 *�������ڣ�2012-11-08
 *�������ڣ�2012-11-08
*/
void ExpressionCalculator::addHandler(string name,double (*func)(double,int))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gddi;
	handler.num=2;
	handler.func.gddi=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *�������ܣ���Ӻ���������
 *�������ڣ�2012-11-09
 *�������ڣ�2012-11-09
*/
void ExpressionCalculator::addHandler(string name,string (*func)(string,int))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gssi;
	handler.num=2;
	handler.func.gssi=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *�������ܣ���Ӻ���������
 *�������ڣ�2013-08-22
 *�������ڣ�2013-08-22
*/
void ExpressionCalculator::addHandler(string name,string (*func)(string,int,int))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gssii;
	handler.num=3;
	handler.func.gssii=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *�������ܣ���Ӻ���������
 *�������ڣ�2013-08-22
 *�������ڣ�2013-08-22
*/
void ExpressionCalculator::addHandler(string name,int (*func)(string))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gis;
	handler.num=1;
	handler.func.gis=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *�������ܣ���Ӻ���������
 *�������ڣ�2013-08-22
 *�������ڣ�2013-08-22
*/
void ExpressionCalculator::addHandler(string name,string (*func)(string,string,string))
{
	Handler handler;
	handler.weight=0;
	handler.funcid=gssss;
	handler.num=3;
	handler.func.gssss=func;
	m_handlermap.insert(pair<string,Handler>(name,handler));
}
/*
 *�������ܣ��������ı��ʽ
 *�������ڣ�2012-12-04
 *�������ڣ�2012-12-04
*/
string ExpressionCalculator::getErrorExpress()
{
	ostringstream out;
	list<Element>::iterator iter;
	for(iter=m_elements.begin();iter!=m_elements.end();++iter)
	{
		switch(iter->type)
		{
		case operatorsymbol:
			//�ǲ���������
			if(iter->e.handler.funcid==vivv)
			{
				char ch=iter->e.handler.parameter;
				out<<ch;
			}
			else if(iter->e.handler.funcid==0)out<<m_const[iter->e.handler.parameter];
			else out<<"[F"<<iter->e.handler.funcid<<"]";
			break;
		case operatorvariant:
			if(iter->e.number.isString())out<<(string)iter->e.number;
			else out<<(double)iter->e.number;
			break;
		}
	}
	return out.str();
}

# ifdef _DEBUG
/*
 *�������ܣ����������
 *�������ڣ�2012-11-01
 *�������ڣ�2012-11-08
*/
ostream& operator<<(ostream& cout,const variant& var)
{
	variant out=var;
	if(out.type==String)
	{
		cout<<"\""<<(string)out<<"\"";
	}
	else
	{
		cout<<(double)out;
	}
	return cout;
}
/*
 *�������ܣ��������������ɨ���Ľ��
 *�������ڣ�2012-11-01
 *�������ڣ�2012-11-09
*/
void ExpressionCalculator::output()
{
	cout<<m_expression<<endl;
	list<Element>::iterator iter;
	for(iter=m_elements.begin();iter!=m_elements.end();++iter)
	{
		switch(iter->type)
		{
		case operatorsymbol:
			//�ǲ���������
			if(iter->e.handler.funcid==vivv)
			{
				char ch=iter->e.handler.parameter;
				cout<<ch;
			}
			else if(iter->e.handler.funcid==0)cout<<m_const[iter->e.handler.parameter];
			else cout<<"[F"<<iter->e.handler.funcid<<"]";
			break;
		case operatorvariant:
			cout<<iter->e.number;
			break;
		}
		//cout<<',';
	}
	vector<string> vec=getUnknowVar();
	for(int i=0;i<vec.size();i++)
	{
		cout<<","<<vec[i];
	}
	cout<<endl;
}
#endif