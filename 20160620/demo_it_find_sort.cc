//容器元素的遍历，查找与排序等综合应用

#include<iostream>
#include<vector>
#include<deque>
#include<list>
#include<map>
#include<algorithm>
#include<string.h>
using namespace std;

#pragma warning(disable:4096)

class CMyString;
ostream& operator<<(ostream &os, const CMyString &s);
CMyString operator+(const CMyString &s1, const CMyString &s2);


class CMyString{
	private:
		char* m_pData;
	public:
		CMyString(){m_pData = new char[1]; m_pData[0] = '\0';}
		CMyString(const char* pBuf){
			if(NULL == pBuf){
				m_pData = new char[1];
				m_pData[0] = '\0';
			}else{
				m_pData = new char[strlen(pBuf)+1];
				strcpy(m_pData, pBuf);
			}
		}
		CMyString(const CMyString &s){
			m_pData = new char[strlen(s.m_pData)+1];
			strcpy(m_pData, s.m_pData);
		}

		//map要求运算比较符为const类型
		bool operator<(const CMyString &s)const{
			return (strcmp(this->m_pData, s.m_pData) < 0);
		}

		bool operator==(const CMyString &s)const{
			return (strcmp(this->m_pData, s.m_pData) == 0);
		}
		//省略> , <=, >=,

		CMyString &operator=(const CMyString &s){
			if(this != &s){
				delete m_pData;
				m_pData = new char[strlen(s.m_pData)+1];
				strcpy(m_pData, s.m_pData);
			}
			return (*this);
		}

		char& operator[](const unsigned int &i){return m_pData[i];}
		operator char*(){return m_pData;}

		friend CMyString operator+(const CMyString &s1, const CMyString &s2);
		friend ostream& operator<<(ostream &os, const CMyString &s);

		int GetLength(){return strlen(m_pData)+1;}
		char* GetBuffer(){return m_pData;}
		~CMyString(){delete m_pData;m_pData = NULL;}
};

CMyString operator+(const CMyString &s1, const CMyString &s2){
	char* pTemp = new char[strlen(s1.m_pData) + strlen(s2.m_pData) +1];
	strcpy(pTemp, s1.m_pData);
	strcat(pTemp, s2.m_pData);
	return CMyString(pTemp);
}

ostream &operator<<(ostream &os, const CMyString &s){
	os<<s.m_pData;
	return os;
}

void PrintCString(CMyString &s){cout << s << " ";}
void PrintPair(pair<CMyString, string> ob){cout << ob.first << " " << ob.second << endl;}

///////////////////////////////////////////////////////
//
//

void testVector(){
	//1.测试自定义数据类型
	vector<CMyString> ob;
	ob.push_back("A");
	ob.push_back("B");
	ob.push_back("C");
	ob.push_back(CMyString("A"));
	ob.push_back(CMyString("B"));
	ob.push_back(CMyString("C"));

	for_each(ob.begin(), ob.end(), PrintCString);
	cout << endl;

	sort(ob.begin(), ob.end(), PrintCString);
	for_each(ob.begin(), ob.end(), PrintCString);
	cout << endl;

	//find第一个“B”并删除
	vector<CMyString>::iterator it = find(ob.begin(), ob.end(), CMyString("B"));
	if(it != ob.end()) ob.erase(it);
	for_each(ob.begin(), ob.end(), PrintCString);
	cout << endl;


	//find第一个“C”并删除其后所有元素
	it = find(ob.begin(), ob.end(), CMyString("C"));
	if(it != ob.end()) ob.erase(it, ob.end());
	for_each(ob.begin(), ob.end(), PrintCString);
	cout << endl;
}

void testList(){
	//1.测试自定义数据类型
	list<CMyString> ob;
	ob.push_back("A");
	ob.push_back("B");
	ob.push_back("C");
	ob.push_back("A");
	ob.push_back("B");
	ob.push_back("C");

	for_each(ob.begin(), ob.end(), PrintCString);
	cout << endl;

	ob.sort();//调用list自身的排序函数
//	sort(ob.begin(), ob.end(), PrintCString);//不能用泛型算法，因为list不支持随机访问
	for_each(ob.begin(), ob.end(), PrintCString);
	cout << endl;

	//find第一个“B”并删除
	list<CMyString>::iterator it = find(ob.begin(), ob.end(),"B");
	if(it != ob.end()) ob.erase(it);
	for_each(ob.begin(), ob.end(), PrintCString);
	cout << endl;


	//find第一个“C”并删除其后所有元素
	it = find(ob.begin(), ob.end(),"C");
	if(it != ob.end()) ob.erase(it, ob.end());
	for_each(ob.begin(), ob.end(), PrintCString);
	cout << endl;
}

void testMap(){
	//3.map要求CMyString类的==和<比较运算符定义为const类型
	pair<CMyString, string> sz[] = {
		pair<CMyString, string>("beijing","huabei"),
		pair<CMyString, string>("shenzhen", "huanan")
	};

	map<CMyString, string> ob(sz,sz+2);
	ob.insert(pair<CMyString,string>("hangzhou","huadong"));
	ob["wuhan"] = "huazhong";
	ob["xiamen"] = "huanan";
	ob["shanghai"] = "huanan";
	ob["shanghai"] = "huadong";

	for_each(ob.begin(), ob.end(), PrintPair);
	cout << endl;
	
	//map使用自身的find
	map<CMyString,string>::iterator it = ob.find("xiamen");
	if(it != ob.end()) ob.erase(it);
	for_each(ob.begin(), ob.end(), PrintPair);
}

//////////////////////////////////////////////////////
//

int main(){
	testVector();
	testList();
	testMap();
}
