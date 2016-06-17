
//1. 实现String类的其它运算符的重载，COW实现方式(Copy on Write)
//	由于gcc版本问题，有一些string的实现不是以COW的方式
//	gcc 5.x.x 是SSO（Short String Optimisation 短字符优先）的策略


#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

class String{
	private:
		class CharProxy;//前置声明
	public:
		//String();//默认构造函数
		//String(const char*);//一参构造函数
		String(const char* s = ""); //有默认参数的构造函数则可以替代上2个构造函数
		String(const String&);//拷贝构造函数
		~String();//析构函数
		
		String& operator=(const String&);
		String& operator=(const char*);

		String& operator+=(const String&);
		String& operator+=(const char*);

		CharProxy operator[](size_t);
		char& operator[](size_t) const;//专用于const对象

		size_t size() const{return len;}//返回字符串长度
		const char* c_str() const{return &pstr_[1];}//返回C风格的字符串，即char*类型

		friend bool operator==(const String&, const String&);
		friend bool operator!=(const String&, const String&);

		friend bool operator<(const String&, const String&);
		friend bool operator>(const String&, const String&);
		friend bool operator<=(const String&, const String&);
		friend bool operator>=(const String&, const String&);

		friend ostream &operator<<(ostream&, const String&);
		friend istream &operator>>(istream&, String&);

	private:
		//设置字符串，引用数和长度,仅限类内部使用
		int useCount()const{return pstr_[0];}
		void increaseRefCount(){++pstr_[0];}
		void decreaseRefCount(){--pstr_[0];}
		void setStr(const char*);

		char* pstr_;
		size_t len;//长度，有次数据成员则不用每次都调用strlen
		//自定义字符代理类，绕过内置类型无法重载运算符的限制
		class CharProxy{//函数较短的话直接使用inline效率较高
			public:
				CharProxy(String& s, size_t i):_s(s),_i(i){}//构造函数
				operator char(){return _s.pstr_[_i+1];}//类型转换函数
				char& operator=(char);//=运算符重载函数
			private:
				String& _s;
				size_t _i;
		};
		

};

//三种+号重载函数对应三种不同的情况
String operator+(const String&, const String&);
String operator+(const String&, const char*);
String operator+(const char*, const String&);

//////////////////////////////////////
//实现自定义String类
/////////////////////////////////////

char& String::CharProxy::operator=(char c){
	cout << " CharProxy = " << endl;
	if(_i >= 0 && _i <= _s.size()){//检查下标
		if(_s.useCount() == 1){//检查引用计数
			_s.pstr_[_i+1] = c;
			return _s.pstr_[_i+1];
		}
		_s.decreaseRefCount();
		_s.setStr(_s.c_str());
		_s.pstr_[_i+1] = c;
		return _s.pstr_[_i+1];
	}else{
		static char nullc = '\0';//此处必须使用static，因为返回值为char&
		cout << "error index" << endl;
		return nullc;
	}
}

//String::String(){//默认构造函数
//	cout << "String()" << endl;
//	pstr_ = (char*)malloc(1); //不能直接置NULL,否在会新建对象时出错
//	pstr_[0] = '\0';
//}


void String::setStr(const char* s){
	//长度len的设定在此函数之前，所以可以放心调用setStr
	pstr_ = new char[len+2];
	pstr_[0] = 1;//将字符串的第1位做为引用计数位，
	//由于字符型，所以最多能保存255个引用（unsigned char的最大值为255）
	strcpy(&pstr_[1], s);
}

String::String(const char* s){
	len = strlen(s);//设定长度的函数不可放入setStr中，
	setStr(s);//为了后面String类型的参数复用
}

String::String(const String& s)//拷贝构造函数，通过String对象初始化
	:len(s.size())//先初始化长度
{
	//COW的方式，直接复制，即浅拷贝
	pstr_ = s.pstr_;//s.pstr_可以直接使用时因为本函数为类的成员函数
	increaseRefCount();//增加当前字符串的引用计数
}

String::~String(){
	decreaseRefCount();
	if(useCount() == 0)
		delete[] pstr_;
}

String& String::operator=(const String& s){
	if(&s != this){
		decreaseRefCount();//对旧的字符串引用计数减1
		if(useCount() == 0)
			delete[] pstr_;
		len = s.len;
		pstr_ = s.pstr_;
		increaseRefCount();//对新的字符串引用计数加1
	}
	return *this;
}

String& String::operator=(const char* s){
	delete[] pstr_;
	len = strlen(s);
	setStr(s);
	return *this;
}

String& String::operator+=(const String& s){
	*this = *this + s;//直接调用以及重载的+运算符
	return *this;
}

String& String::operator+=(const char* s){
	*this = *this + s;
	return *this;
}
//要想实现使用[]运算符区分读和写的操作，
//	则需要返回一个内置的临时对象，然后重载这个对象的运算符
//	包括赋值运算符，输入输出运算符等（所有可以使用到[]的场景都可以考虑进去）
//	或直接使用类型转换函数，将CharProxy转为char
String::CharProxy String::operator[](size_t index){//此处返回类型必须为非引用类型
		cout << " CharProxy [] ";
		return CharProxy(*this, index);//因为CharProxy是一个栈对象
}
//此函数再普通情况下（非const对象调用）并没有被调用到
char& String::operator[](size_t index)const{
	cout<< " const char[] ";
	if(index >= 0 && index < len)
		return pstr_[index+1];
}

bool operator==(const String& lhs, const String& rhs){
	if(!strcmp(lhs.c_str(), rhs.c_str()))
		return true;
	return false;
}

bool operator!=(const String& lhs, const String& rhs){
	if(strcmp(lhs.c_str(), rhs.c_str()))
		return true;
	return false;
}

bool operator<(const String& lhs, const String& rhs){
	if(strcmp(lhs.c_str(), rhs.c_str()) < 0)
		return true;
	return false;
}
bool operator>(const String& lhs, const String& rhs){
	if(strcmp(lhs.c_str(), rhs.c_str()) > 0)
		return true;
	return false;
}
bool operator<=(const String& lhs, const String& rhs){
	if(strcmp(lhs.c_str(), rhs.c_str()) < 0 && !strcmp(lhs.c_str(), rhs.c_str()))
		return true;
	return false;
}
bool operator>=(const String& lhs, const String& rhs){
	if(strcmp(lhs.c_str(), rhs.c_str()) < 0 && !strcmp(lhs.c_str(), rhs.c_str()))
		return true;
	return false;
}

ostream& operator<<(ostream& os, const String& s){
	os << s.c_str() << " [By overlaod <<] " << endl;
	return os;
}

istream& operator>>(istream& is, String& s){
	string temp;//使用string类临时对象，若不能使用string类则使用char* 字符数组
	is >> temp;
	s.len = temp.size();
	s.setStr(temp.c_str());
	return is;
}

//三种+号重载函数对应三种不同的情况
String operator+(const String& lhs, const String& rhs){
	size_t len = lhs.size()+rhs.size();
	char* temp  = new char[len+1];
	strcpy(temp, lhs.c_str());
	strcat(temp, rhs.c_str());
	String* tempS = new String(temp);
	delete[] temp;
	return *tempS;
}

String operator+(const String& lhs, const char* rhs){
	size_t len = lhs.size()+strlen(rhs);
	char* temp  = new char[len+1];
	strcpy(temp, lhs.c_str());
	strcat(temp, rhs);
	String* tempS = new String(temp);
	delete[] temp;
	return *tempS;
}

String operator+(const char* lhs, const String& rhs){
	size_t len = rhs.size()+strlen(lhs);
	char* temp  = new char[len+1];
	strcpy(temp, lhs);
	strcat(temp, rhs.c_str());
	String* tempS = new String(temp);
	delete[] temp;
	return *tempS;
}

int main(){
	String s1;
	String* s2 = new String();
	String* s3 = new String("s3");
	String s4 = "s4";

	cout << "String s1:" << s1 << endl;
	cout << "Stting* s2 = new String(), s2->c_str():" << s2->c_str() << endl;
	cout << "String* s3 = new String(\"s3\"), s3->c_str():" << s3->c_str() << endl;
	cout << "s4:" << s4 << endl;

	//测试COW的用例
	String cow1 = "BABY,HELLO";
	String cow2 = cow1;
	String cow3 = cow2;

	printf("cow1 %p\ncow2 %p\ncow3 %p\n", cow1.c_str(), cow2.c_str(), cow3.c_str());

	cout << cow1[1] << cow2[2] << cow3[3] << endl;


//老大的测试用例～ 感谢我老大
	String a("hello");
	String b;
	b = ",world";
	char ch[4] = "123";
	b += ch;
	cout << b << endl;
	String c;
	c = a + b;
	cout << c << endl;
	String d;
	d = b + ch;
	cout << d << endl;
	String e;
//	cin >> e;//测试重载>>运算符
	e += ch;
	cout << e << endl;

	return 0;
}
