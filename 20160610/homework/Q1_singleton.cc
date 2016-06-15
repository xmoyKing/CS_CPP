//1. 理解单例模式的实现原理，并掌握，做到随手能够写出来

#include<iostream>
using namespace std;

//单例模式，构造/析构函数为private，
//同时定义一个static private的指向对象的指针
//静态成员变量创建/返回对象

class Singleton{
	public:
		static Singleton* getInstance();
		static void destory();
	private:
		Singleton();
		~Singleton();

		static Singleton* _pInstance;
};

Singleton* Singleton::getInstance(){
	if(!_pInstance)
		_pInstance = new Singleton;
	return _pInstance;
}

void Singleton::destory(){
	delete _pInstance;
}

Singleton::Singleton(){
	cout << "default constructor" << endl;
}

Singleton::~Singleton(){
	cout << "destructor" << endl;
}

Singleton* Singleton::_pInstance = NULL;//静态数据成员必须在类体外初始化

int main(){
	Singleton* pS1 = Singleton::getInstance();
	Singleton* pS2 = Singleton::getInstance();
	
	cout << "pS1 = " << pS1
		<< " pS2 = " << pS2
		<< endl;

	Singleton::destory();
	return 0;
}
