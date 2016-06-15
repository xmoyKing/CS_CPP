//4. 编写一个类，实现简单的栈。

#include<iostream>
using namespace std;

class Stack{
	public:
		void push(int);
		void pop();
		int top();
		bool empty();
		bool full();
	private:
		int _arr[10];
		int _head;//记录栈顶,指向下一个空元素
};

void Stack::push(int n){
	if(!full())
		_arr[_head++] = n;
	else cout << "stack is full" << endl;
}

void Stack::pop(){
	if(!empty())
		_head--;
	else cout << "stack is empty" << endl;
}

int Stack::top(){
	if(!empty())
		return _arr[_head-1];
	else cout << "stack is empty" << endl;
}

bool Stack::empty(){
	if(_head == 0)
		return true;
	return false;
}

bool Stack::full(){
	if(_head == 10)
		return true;
	return false;
}

int main(){
	Stack s;
	s.push(10);
	s.push(12);
	s.push(14);
	cout << "the top element of stack is " << s.top() << endl;
	s.pop();
	cout << "the top element of stack is " << s.top() << endl;
}
