#include<iostream>
#include<string>
#include<pthread.h>
#include<cstdlib>

using namespace std;

template <typename T>
class Singleton{
	public:
		static T* getInstance(); //此处返回为T类型的单例类 
		//	static Singleton* getInstance(); 
		static void init();
		static void destory();
		
	private:
		Singleton(){}
		~Singleton(){}

		static T* _pInstance;
		static pthread_once_t _once;
};

template <typename T>
void Singleton<T>::init(){
	atexit(destory); //regist destory when main func return

	if(!_pInstance) //check whether pInstance
		_pInstance = new T;
}

template <typename T>
T* Singleton<T>::getInstance(){
	pthread_once(&_once, &init); //this func make sure exec arg func once 
	return _pInstance;
}

template <typename T>
void Singleton<T>::destory(){
	cout << "destory" << endl;
	if(_pInstance) delete _pInstance;	
}

template <typename T>
T* Singleton<T>::_pInstance = NULL;

template <typename T>
pthread_once_t Singleton<T>::_once = PTHREAD_ONCE_INIT;

int main(){
	int* ps1 = Singleton<int>::getInstance();
//	Singleton<int>* ps1 = Singleton<int>::getInstance(); //错误的调用方式
	int* ps2 = Singleton<int>::getInstance();
	string* ps3 = Singleton<string>::getInstance();

	cout << "ps1 = " << ps1 << endl
		 << "ps2 = " << ps2 << endl
		 << "ps3 = " << ps3 << endl
		 << endl;

	return 0;
}
