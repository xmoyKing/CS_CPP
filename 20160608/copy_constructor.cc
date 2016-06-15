#include<iostream>
using namespace std;
//测试fun2对析构函数，copy constructor的调用
class CPoint{
	private:
		int x;
		int y;
	public:
		CPoint(){
			cout<< "defalut constructor "<< this << " "<< endl;
			x = 0;
			y = 0;
		}

		CPoint(int ix){
			cout<< " 1 arg constructor "<< this << " " <<endl;
			x = ix;
			y = 0;
		}

		CPoint(int ix, int iy){
			cout<< "2 args constructor "<< this << " " << endl;
			x = ix;
			y = iy;
		}
	
		CPoint(const CPoint &cp){
			cout << "copy constructor "<< this << " " << endl;
			x = cp.x;
			y = cp.y;
		}

		CPoint &operator=(const CPoint &cp){
			cout<< "overload = function "<< this << " " << endl;
			if(this != &cp){
				x = cp.x;
				y = cp.y;
			}
			return *this;
		}

		~CPoint(){ cout<< "destructor "<< this << " " << endl;	}
};

void fun1(CPoint pt){
}

CPoint fun2(){
	CPoint a;
	return a;
}

CPoint fun(CPoint a){
	return a;
}

///////////////////////////////
//

int main(){
	CPoint pt6 = fun2();

	return 0;
}

