#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

class String{
	public:
		String();//默认构造函数
		String(const char*);//1参构造函数
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

String::String(){//默认构造函数
	cout << "String()" << endl;
	pstr_ = (char*)malloc(1); //不能直接置NULL,否在会新建对象时出错
	pstr_[0] = '\0';
}

String::String(const char* s){
	pstr_ = (char*)malloc(strlen(s)+1);
	strcpy(pstr_, s);
}

String::String(const String& s){
	pstr_ = (char*)malloc(s.size()+1);
	strcpy(pstr_, s.c_str());
}

String::~String(){
	free(pstr_);
	pstr_ = NULL;
}

String& String::operator=(const String& s){
	if(pstr_){
		free(pstr_);
		pstr_ = NULL;
	}
	pstr_ = (char*)malloc(s.size()+1);
	strcpy(pstr_, s.c_str());
	return *this;
}

String& String::operator=(const char* s){
	if(pstr_){
		free(pstr_);
		pstr_ = NULL;
	}
	pstr_ = (char*)malloc(strlen(s)+1);
	strcpy(pstr_, s);
	return *this;
}


size_t String::size()const{
	return strlen(pstr_);
}

const char* String::c_str()const{
	return pstr_;
}

String& String::operator+=(const String& s){
	char* temp = (char*)malloc(size()+s.size()+1);
	strcpy(temp, c_str());
	strcat(temp, s.c_str());
	delete this;
	pstr_ = (char*)malloc(strlen(temp));
	strcpy(pstr_, temp);
	free(temp);
	temp = NULL;
	return *this;
}

String& String::operator+=(const char* s){
	char* temp = (char*)malloc(size()+strlen(s)+1);
	strcpy(temp, c_str());
	strcat(temp, s);
	delete this;
	pstr_ = (char*)malloc(strlen(temp));
	strcpy(pstr_, temp);
	free(temp);
	temp = NULL;
	return *this;
}

char& String::operator[](size_t index){
	return pstr_[index];
}

const char& String::operator[](size_t index)const{
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
	string temp;
	is >> temp;
	s.pstr_ = (char*)malloc(temp.size()+1);
	strcpy(s.pstr_, temp.c_str());
	return is;
}

//三种+号重载函数对应三种不同的情况
String operator+(const String& lhs, const String& rhs){
	char* temp  = (char*)malloc(lhs.size()+rhs.size()+1);
	strcpy(temp, lhs.c_str());
	strcat(temp, rhs.c_str());
	String* tempS = new String(temp);
	return *tempS;
}

String operator+(const String& lhs, const char* rhs){
	char* temp  = (char*)malloc(lhs.size()+strlen(rhs)+1);
	strcpy(temp, lhs.c_str());
	strcat(temp, rhs);
	String* tempS = new String(temp);
	return *tempS;
}

String operator+(const char* lhs, const String& rhs){
	char* temp  = (char*)malloc(rhs.size()+strlen(lhs)+1);
	strcpy(temp, lhs);
	strcat(temp, rhs.c_str());
	String* tempS = new String(temp);
	return *tempS;
}

int main(){
	String s1;
	String* s2 = new String();
	String* s3 = new String("s3");
	String s4 = "s4";

	cout << "s1:" << s1 << endl;
	cout << "s2:" << s2->c_str() << endl;
	cout << "s3:" << s3->c_str() << endl;
	cout << "s4:" << s4 << endl;


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
