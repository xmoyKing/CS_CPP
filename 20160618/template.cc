#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;

template <typename T>
T add(const T& a, const T& b){
//	cout << "T" << endl;
	return a+b;
}


template<typename Ta, int NUM>
//NUM为一个常量
Ta arr(Ta d){
	Ta n[NUM] = {d};
	int i = 0;
	while(i < NUM)
		cout << n[i++] << endl;
}

int main(){
	cout << add(1, 2) << endl;
	cout << add(1.0, 2.1) << endl;
	cout << add<double>(1, 2.1) << endl;


	char* p1 = new char[6];
	char* p2 = new char[6];

	strcpy(p1,"hello");
	strcpy(p2,"baby!");
	//cout<< p1 + p2 << endl; //
//	cout<< add(p1,p2) << endl;

	string s1 = "hello";
	string s2 = "world";

//	int a[10] ={}; //测试数组地址，问题是间隔为28,而不是40
//	printf("%p\n%p\n%p\n%p\n",a,a+1,&a+1,&a+2);

	arr<double, 4>(3.1);

}
