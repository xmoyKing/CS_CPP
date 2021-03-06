
//1. 实现String类的其它运算符的重载

#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

class String{
	public:
		//String();//默认构造函数
		//String(const char*);//1参构造函数
		String(const char* s = ""); //有默认参数的构造函数则可以替代上2个构造函数
		String(const String&);//拷贝构造函数
		~String();//析构函数
		
		String& operator=(const String&);
		String& operator=(const char*);

		String& operator+=(const String&);
		String& operator+=(const char*);

		char& operator[](size_t);
		const char& operator[](size_t) const;//专用于const对象

		size_t size() const;//返回字符串长度
		const char* c_str() const;//返回C风格的字符串，即char*类型

		friend bool operator==(const String&, const String&);
		friend bool operator!=(const String&, const String&);

		friend bool operator<(const String&, const String&);
		friend bool operator>(const String&, const String&);
		friend bool operator<=(const String&, const String&);
		friend bool operator>=(const String&, const String&);

		friend ostream &operator<<(ostream&, const String&);
		friend istream &operator>>(istream&, String&);

	private:
		//设置字符串和长度,仅限类内部使用
		void setStr(const char*);
		char* pstr_;
		size_t len;//长度，有次数据成员则不用每次都调用strlen
};

//三种+号重载函数对应三种不同的情况
String operator+(const String&, const String&);
String operator+(const String&, const char*);
String operator+(const char*, const String&);

//////////////////////////////////////
//实现自定义String类
/////////////////////////////////////

//String::String(){//默认构造函数
//	cout << "String()" << endl;
//	pstr_ = (char*)malloc(1); //不能直接置NULL,否在会新建对象时出错
//	pstr_[0] = '\0';
//}

void String::setStr(const char* s){
	//长度len的设定在此函数之前，所以可以放心调用setStr
	pstr_ = new char[len+1];
	strcpy(pstr_, s);
}

String::String(const char* s){
	len = strlen(s);//设定长度的函数不可放入setStr中，
	setStr(s);//为了后面String类型的参数复用
}

String::String(const String& s):len(s.size()){//先初始化长度
	setStr(s.c_str());
}

String::~String(){
	delete[] pstr_;
}

String& String::operator=(const String& s){
	if(&s != this){
		delete[] pstr_;
		len = s.len;
		setStr(s.c_str());
	}
	return *this;
}

String& String::operator=(const char* s){
	delete[] pstr_;
	len = strlen(s);
	setStr(s);
	return *this;
}


size_t String::size()const{
	return len;
}

const char* String::c_str()const{
	return pstr_;
}

String& String::operator+=(const String& s){
//	len = size()+s.size();
//	char* temp = new char[len+1];
//	strcpy(temp, c_str());
//	strcat(temp, s.c_str());
//	delete this;
//	setStr(temp);	
//	delete[] temp;
	*this = *this + s;//以上可以使用此句代替
	return *this;
}

String& String::operator+=(const char* s){
	*this = *this + s;//以上可以使用此句代替
	return *this;
}

char& String::operator[](size_t index){
	if(index >= 0 && index < len)
		return pstr_[index];
}

const char& String::operator[](size_t index)const{
	if(index >= 0 && index < len)
		return pstr_[index];
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
	cin >> e;
	e += ch;
	cout << e << endl;

	return 0;
}
