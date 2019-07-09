#include "stringhelper.h"
#include <vector>
//Converting a WChar string to a Ansi string
std::string StringHelper::WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen<= 0) return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen -1] = 0;
	std::string strTemp(pszDst);
	delete [] pszDst;
	return strTemp;
}
string StringHelper::ws2s(wstring& inputws)
{ 
	return WChar2Ansi(inputws.c_str()); 
}
//Converting a Ansi string to WChar string
std::wstring StringHelper::Ansi2WChar(LPCSTR pszSrc, int nLen)
{
	int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);
	if(nSize <= 0) return NULL;
	WCHAR *pwszDst = new WCHAR[nSize+1];
	if( NULL == pwszDst) return NULL;
	MultiByteToWideChar(CP_ACP, 0,(LPCSTR)pszSrc, nLen, pwszDst, nSize);
	pwszDst[nSize] = 0;
	if( pwszDst[0] == 0xFEFF) // skip Oxfeff
		for(int i = 0; i < nSize; i ++) 
			pwszDst[i] = pwszDst[i+1]; 
	wstring wcharString(pwszDst);
	delete pwszDst;
	return wcharString;
}
std::wstring StringHelper::s2ws(const string& s)
{ 
	return Ansi2WChar(s.c_str(),s.size());
}
/*
 *�������ܣ��ַ���ת��Ϊʵ��
 *�������ڣ�2013/3/30 21:25
 *�������ڣ�2013/3/30 21:25
*/
double StringHelper::toDouble(const string& str)
{
	return atof(parseDouble(str).c_str());
}

/*
 *�������ܣ�ʵ��ת��Ϊ�ַ���������ȥ��ĩβ�������
 *�������ڣ�2013/3/30 21:25
 *�������ڣ�2013/3/30 22:12
*/
string StringHelper::toString(double value)
{
	char str[255];
	sprintf(str,"%lf",value);
	string s=string(str);
	if(s.length()==0)return "";
	bool hasdot=false;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='.')
		{
			hasdot=true;
			break;
		}
	}
	if(hasdot)
	{
		while(s[s.length()-1]=='0')
		{
			s.erase(s.length()-1);
		}
		if(s[s.length()-1]=='.')s.erase(s.length()-1);
	}
	return s;
}
/*
 *�������ܣ���ȡ����
 *�������ڣ�2013/3/30 22:58
 *�������ڣ�2013/3/30 22:58
*/
string StringHelper::parseDouble(const string& s)
{
	string str;
	for (int i=0;i<s.length();i++)
	{
		char ch=s[i];
		if(ch>='0'&&ch<='9')
		{
			str.push_back(ch);
		}
		else if (ch=='.'||ch=='+'||ch=='-')
		{
			str.push_back(ch);
		}
	}
	return str;
}
/*
 *�������ܣ��ж��Ƿ���ʵ��
 *�������ڣ�2013/5/9 22:58
 *�������ڣ�2013/5/9 22:58
*/
bool StringHelper::isDouble(const string& s)
{
	int count=0;
	for (int i=0;i<s.length();i++)
	{
		char ch=s[i];
		if(ch>='0'&&ch<='9')
		{
			continue;
		}
		else if (ch=='.'&&count<2)
		{
			count++;
			continue;
		}
		else if(i==0&&(ch=='+'||ch=='-'))
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}
/*
 *�������ܣ����ַ������ַ���
 *�������ڣ�2013/5/9 22:58
 *�������ڣ�2013/5/9 22:58
*/
vector<string> StringHelper::split(string s,char c)
{
	vector<string> ret;
	string str="";
	for(int i=0;i<s.length();i++)
	{
		if(s[i]==c)
		{
			ret.push_back(str);
			str="";
		}
		else
		{
			str.push_back(s[i]);
		}
	}
	ret.push_back(str);
	return ret;
}