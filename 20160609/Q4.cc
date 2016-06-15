#include<iostream>
#include<string.h>

using namespace std;

class String{
	public:
		String();//默认构造函数
		String(const char* pstr);//带参数的构造函数
		String(const String &rhs);//拷贝构造函数
		String &operator = (const String &rhs);//赋值运算符重载
		~String();//析构函数

		void print();//打印字符串

	private:
		char* _pstr;//数据成员
};

String::String(){
	_pstr = new char[2]; //此处一定要使用new初始化一个空间
	strcpy(_pstr,"");    // 否则最后使用delete会出错
	cout<<"defaul constructor"<<endl;
//	_pstr = NULL;
}

String::String(const char* pstr){
	_pstr = new char[strlen(pstr)+1];
	strcpy(_pstr, pstr);
}

String::String(const String & rhs){
	_pstr = new char[strlen(rhs._pstr)+1];
	strcpy(_pstr, rhs._pstr);
}

String & String::operator = (const String & rhs){
	if(_pstr != rhs._pstr){//直接比较this指针和rhs的地址即可，this != &rhs
		delete [] _pstr; //释放原字符串指针空间
		_pstr = new char[strlen(rhs._pstr)+1];
		strcpy(_pstr, rhs._pstr);
	}
	return *this;
}

void String::print(){
	cout<< this <<" _pstr : "<< _pstr << endl;
}

String::~String(){
	if(this->_pstr){//若该对象还未释放
		delete [] _pstr;//释放空间
		_pstr = NULL; //若不置NULL，会产生野指针
	}
	cout<< this << " deconstructor"<<endl;
}

int main(){
	String str1;
	str1.print();

	String str2 = "Hello, world";
	String str3 = "wangdao";

	str2.print();
	str3.print();
	str2 = str3;
	str2.print();

	String str4 = str3;
	str4.print();
	
	return 0;
}
