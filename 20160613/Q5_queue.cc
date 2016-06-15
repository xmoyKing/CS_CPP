//5. 编写一个类，实现简单的队列。

#include<iostream>
#define SIZE 10 //定义数组长度
using namespace std;

class Queue{
	public:
		void push(int);
		void pop();
		int front();
		int back();
		bool empty();
		bool full();
	private://使用链表实现比循环数组要方便清晰些
		int _arr[SIZE];
		int _head;//头
		int _rear;//尾
};

//简单队列不需要考虑循环的问题
//循环队列,循环队列需考虑空和满的区别
void Queue::push(int n){
	if(!full()){
		_arr[_rear] = n;
		_rear = (_rear+1)%SIZE;
	}
	else cout << "queue is full" << endl;
}

void Queue::pop(){
	if(!empty())
		_head = (_head+1)%SIZE;
	else cout << "queue is empty" << endl;
}

int Queue::front(){
	if(!empty())
		return _arr[_head];
	else cout << "queue is empty" << endl;
	return -1;
}

int Queue::back(){
	if(!empty())
		return _arr[_rear-1];
	else cout << "queue is empty" << endl;
	return -1;
}

bool Queue::empty(){//初始化时rear和head都为0,出队操作时head向后增加
	if(_rear == _head)//全部出队后，head增加到rear
		return true;
	return false;
}

bool Queue::full(){//始终再数组末尾留一个空位用于判满
	if((_rear+1)%SIZE == _head)
		return true;
	return false;
}

int main(){
	Queue q;
	q.push(1);
	q.push(2);
	q.push(5);
	cout << "the front of queue is " << q.front() << endl;
	cout << "the back of queue is " << q.back() << endl;
	q.pop();
	q.push(8);
	cout << "the front of queue is " << q.front() << endl;
	cout << "the back of queue is " << q.back() << endl;
}
