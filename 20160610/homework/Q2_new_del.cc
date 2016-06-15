//2. 理解new/delete机制，实现只能栈对象和只能生成堆对象代码
//只能生成栈对象A：将operator new放入private区
//只能生成堆对象B：将析构函数放入private区


#include<iostream>
using namespace std;

class A{
	public:
		A(int x = 0):_x(x){
			cout << "constructor with default arg" << endl;
		}
		~A(){
			cout << "destructor" << endl;
		}
		void print()const{
			cout << "_x = " << _x << endl;
		}
	private:
		void* operator new(size_t count);
	//	void operator delete(void* p);

		int _x;
};

class B{
	public:
		B(int x = 0):_x(x){
			cout << "constructor with default arg" << endl;
		}
		void print()const{
			cout << "_x = " << _x << endl;
		}
		void destory(){
			delete this;//必须使用this指针，销毁本对象
		}

	private:
		~B(){
			cout << "destructor" << endl;
		}
		int _x;
};

int main(){
	//只能生成栈对象
	A a(1);
//	A* a1 = new A(1);
	a.print();

	//只能生成堆对象
	//B b1(2);
	B* b = new B(2);
	b->print();
	b->destory();
	return 0;
}
