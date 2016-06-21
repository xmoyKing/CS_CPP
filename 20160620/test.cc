#include<iostream>
#include<vector>
#include<list>
using namespace std;

void dis(vector<int>& c){
	for(auto& e:c)
		cout<< e << " ";
	cout << endl;
	return;
}

int main(){
	vector<string> vs;
	vs.push_back("this is A");

	vs.push_back("this is B");
	cout << "vs.push B" << endl;

	vector<string>::iterator it = vs.begin();
	int i = 9;
	for(;it != vs.end();++it){
		cout << "size :" << vs.size() <<endl;
		cout << "---> " << *it << endl;
		if(i == 9){
			vs.push_back("this is BBB"); //加上此句直接coredump，
	//		因为在循环内部改变了容器，所以迭代器失效
	//		但迭代器失效的时机和规则与操作有关，此博客有说明：
	//http://blog.csdn.net/xocoder/article/details/8533842
		cout << "---> " << *it << endl;
			cout << "vs.push BBB" << endl;
		}
		cout << "[2]---> " << vs[2] << endl;
		i = 8;
	}
}


int main2(){
	list<int> l = {1,100,2,3,10,1,11,-1,12};
	l.remove(1);
	l.remove_if([](int n){return n > 10;});

	for(int n: l) cout<< n << ' ';

	cout << endl;
	return 0;
}


int main1(){
	vector<int> a;
	a.reserve(100);
	cout<< a.size() << " " << a.capacity() << endl;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	dis(a);
	cout<< a.size() << " " << a.capacity() << endl;
	
	a.resize(2);
	dis(a);
	cout<<"resize(2) "<< a.size() << " " << a.capacity() << endl;

	a.erase(a.begin()+3,a.end());
	dis(a);
	cout<< "erase(3,end) "<<a.size() << " " << a.capacity() << endl;

	a.shrink_to_fit();
	dis(a);
	cout<<"shrink to fit  "  << a.size() << " " << a.capacity() << endl;
}
