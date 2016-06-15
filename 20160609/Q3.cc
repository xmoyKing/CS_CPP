#include <iostream>

using std::cout;
using std::endl;

class PAT{
	public:
		PAT(){
			cout<<"constructor no arg"<<endl;
		}
	
		PAT(int a)
		:_a(a)
		{
			cout<<"constructor"<<endl;
		}

		PAT(const PAT& a){
			cout<<"copy constructor"<<endl;
		}
	private:
		int _a;
};

int main(){
	PAT a(); //
	PAT b(2);
	PAT c[3];
	PAT &ra = b;//
	PAT d = b;
	cout<<"d = b"<<endl;
	PAT *pa = c;
	PAT *p = new PAT(3);
}
