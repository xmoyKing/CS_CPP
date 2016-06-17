 ///
 /// @file    String.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-06-16 16:05:23
 ///

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
using namespace std;

class String
{
public:
	String();
	String(const char * pstr);
	String(const String & rhs);
	String & operator=(const String & rhs);
	String & operator=(const char&);
	~String();

	int useCount()
	{	return _pstr[length() + 1];	}

	int length()
	{	return strlen(_pstr);	}

	void increaseRefcount();
	void decreaseRefcount();

	char & operator[](int idx);
	char & operator[](int idx) const;

private:
	char * _pstr;
};

String::String()
: _pstr(new char[2])
{
	cout << "String()" << endl;
	_pstr[1] = 1;
}

String::String(const char * pstr)
{
	int len = strlen(pstr);
	_pstr = new char[len + 2];
	strcpy(_pstr, pstr);
	_pstr[len + 1] = 1;//将引用计数设置为1
	cout << "String(const char *)" << endl;
}

String::String(const String & rhs)
: _pstr(rhs._pstr)
{
	increaseRefcount();
	cout << "String(const String & rhs)" << endl;
}

String & String::operator=(const String & rhs)
{
	if(this != &rhs)
	{
		decreaseRefcount();//将原来的引用计数减1
		if(useCount() == 0)
		{	
			delete [] _pstr;
		}
		_pstr = rhs._pstr;//进行浅拷贝
		increaseRefcount();
	}
	return * this;
}

String::~String()
{
	decreaseRefcount();
	if(useCount() == 0)
	{
		delete [] _pstr;
		cout << "~String()" << endl;
	}
}

//operator[]() 不能区分读操作还是写操作
char& String::operator[](int idx) const
{
	cout << "operator[](int) const" << endl;
	return _pstr[idx];
}

#if 1
char & String::operator[](int idx)
{
	if(idx >=0 && idx < length())
	{
		if(useCount() == 1)//当对象没有共享内存时
			return _pstr[idx];

		decreaseRefcount();//当对象共享内存时
		char * ptmp = new char[length() + 2];
		strcpy(ptmp, _pstr);
		_pstr = ptmp;
		_pstr[length() + 1] = 1;
		return _pstr[idx];
	}
	else
	{
		static char nullchar = '\0';
		cout << "下标越界" << endl;
		return nullchar;
	}
}


#endif

void String::increaseRefcount()
{
	++_pstr[length() + 1];	
}
	
void String::decreaseRefcount()
{
	--_pstr[length() + 1];
}

int main(void)
{
	String s1 = "hello,world";
	String s2 = s1;
	String s3 = s2;
	String s5 = "hello,world";
	cout << "s1' useCnt = " << s1.useCount() << endl;
	cout << "s2' useCnt = " << s2.useCount() << endl;
	cout << "s3' useCnt = " << s3.useCount() << endl;
	cout << "s5' useCnt = " << s5.useCount() << endl;
	cout << endl;

	string ss1 = "xx";
	string ss2 = "xx";
	printf("ss1 %p\n",ss1.c_str());
	printf("ss2 %p\n",ss2.c_str());



	String s4 = "shenzhen";
	cout << "s4' useCnt = " << s4.useCount() << endl;
	cout << endl;
	s4 = s2;
	cout << "s1' useCnt = " << s1.useCount() << endl;
	cout << "s2' useCnt = " << s2.useCount() << endl;
	cout << "s3' useCnt = " << s3.useCount() << endl;
	cout << "s4' useCnt = " << s4.useCount() << endl;
	cout << endl;

	//写操作时会发生写时复制
	s4[0] = 'X';
	cout << "s1' useCnt = " << s1.useCount() << endl;
	cout << "s2' useCnt = " << s2.useCount() << endl;
	cout << "s3' useCnt = " << s3.useCount() << endl;
	cout << "s4' useCnt = " << s4.useCount() << endl;
	cout << endl;

	//读操作时也会发生复制
	cout << s3[0] << endl;
	cout << "s1' useCnt = " << s1.useCount() << endl;
	cout << "s2' useCnt = " << s2.useCount() << endl;
	cout << "s3' useCnt = " << s3.useCount() << endl;
	cout << endl;

	return 0;

}
