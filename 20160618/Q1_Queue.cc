#include<cstdlib> //exit() defined in this header
#include<iostream>
#include<string>
using namespace std;

template <typename T, int cap>
class Queue{
	public:
	Queue(); //constructor
	~Queue(); //destructor

	bool full(); //checks whether the underlying container is full
	bool empty(); //checks whether the underlying container is empty 
	
	bool push(T); //insert element at the end
	bool pop(); //removes the frist element
	
	//returns reference to the ? element in the queue
	T& front(); //access the first element 
	T& back(); //access the last element

	int size(){ return _size;} //returns the number of elements
	int capacity(){ return cap;} //returns capacity

	private:
	int _front;
	int _back;
	int _size;
	//int _capacity; //use capacity instead of this private var
	T _parr[cap+1]; //implement by arry with capacity, 
	//there is a empty element to check full, so need +1
};

template <typename T, int cap>
Queue<T, cap>::Queue()
	:_front(0)
	 ,_back(0)
	 ,_size(0)
{}

template <typename T, int cap>
Queue<T, cap>::~Queue(){}

template <typename T, int cap>
bool Queue<T, cap>::full(){
	if((_back+1)%(cap+1) == _front) return true;
	return false;
}

template <typename T, int cap>
bool Queue<T, cap>::empty(){
	if(_back == _front) return true;
	return false;
}

template <typename T, int cap>
bool Queue<T, cap>::push(T elem){
	if(!full()){
		++_size;
		_parr[_back] = elem;
		_back = (_back+1)%(cap+1);
		return true;
	}
	cout << "this queue is full" << endl;
	return false;		
}

template <typename T, int cap>
bool Queue<T, cap>::pop(){
	if(!empty()){
		--_size;
		_front = (_front+1)%(cap+1);
		return true;
	}
	cout << "this queue is empty" << endl;
	return false;
}

template <typename T, int cap>
T& Queue<T, cap>::front(){
	if(!empty())
		return _parr[_front];
	cout << "this queue is empty" << endl;
	exit(-1);
}

template <typename T, int cap>
T& Queue<T, cap>::back(){
	if(!empty())
		return _parr[(_back+cap)%(cap+1)];
	cout << "this queue is empty" << endl;
	exit(-1);
}

////////////////////////////////////////////////////////////
void test();

int main(){
	test();

	return 0;
}

void test(){
	Queue<string, 3> queStr;
	cout << "empty: " << queStr.empty() << " capcity: " << queStr.capacity() << endl;
	queStr.push("aa");
	cout << "empty: " << queStr.empty() << endl;

	queStr.push("ba");
	
	queStr.push("ca");

	cout << "full: " << queStr.full() << " size: " << queStr.size() << endl;

	
	for(int i = 0, size = queStr.size(); i < size; i++){
		cout << queStr.front() << endl;
		queStr.pop();
	}
	cout << "full: " << queStr.full() << " size: " << queStr.size() << endl;
	cout << queStr.front() << endl;
	queStr.pop();
	
	cout << "empty: " << queStr.empty() << " capcity: " << queStr.capacity() << endl;
}

