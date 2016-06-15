//3. 统计一篇英文(The_Holy_Bible.txt)文章中出现的单词和词频，
//   输入：某篇文章的绝对路径
//   输出：词典（词典中的内容为每一行都是一个“单词 词频”）
// -----------------
//|   a 66          |
//|   abandon 77    |
//|   public 88     |
//|    ......	      |
//|_________________|
//
//	class WordStatic
//	{
//	public:
//	    void read_file(std::string filename);
//	    void write_file(std::string filename);
//	private:
//	    //......
//	};

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<string.h>
using namespace std;

class WordStatic
{
	public:
		void read_file(string filename);
		void write_file(string filename);
//		void read_file(const char* filename);
	private:
		//若需要实现排序，则需将此2个vector定义到结构体中，
		//然后使用C++提供的sort函数对结构体排序，
		//可自定义排序规则函数，需要包含algorithm头文件
		vector<string> _vecWord;//存储每一个不同的单词，
		vector<int> _vecWordCount;//存储每一个单词的词频
};

int main(){
	WordStatic* ws = new WordStatic;//去掉()
	ws->read_file("The_Holy_Bible.txt");
	ws->write_file("Q3_dictionary.txt");
	return 0;
}

//void WordStatic::read_file(const char* filename){
//	ifstream ifs(filename); //ifstream的构造函数需要char* 类型，
//	直接使用string类型会报无法转化类型的错误
void WordStatic::read_file(string filename){
	ifstream ifs(filename.data());//利用data方法将string转化为char*类型
	if(!ifs.good()){
		cout << "ifstream open error" << endl;
		return;
	}

	string tmpStr;
	int i, size;
	_vecWord.reserve(13e4);//预先设定容器大小，自动扩容效率低,设定为13万
	_vecWordCount.reserve(13e4);
	cout << "Statistic ... " << filename << " ..." << endl;

	while(ifs >> tmpStr){
		if(tmpStr[0] <= '9' && tmpStr[0] >= '0')
			continue; //跳过数字

		size = _vecWord.size();//每次获取单词后需计算size的大小
		for(i = 0; i < size; i++)
			if(!_vecWord[i].compare(tmpStr)){
				_vecWordCount[i]++;
				break;
			}
			
		if(i == size){
			_vecWordCount.push_back(1);
			_vecWord.push_back(tmpStr);
		}
	}
	
	ifs.close();
}

void WordStatic::write_file(string filename){
	ofstream ofs(filename.data());
	if(!ofs.good()){
		cout << "ofstream open error" << endl;
		return;
	}

	int i;
	for(i = 0; i < _vecWord.size(); i++)
		ofs << _vecWord[i] << " " << _vecWordCount[i] << endl;

	cout << " Statistic is done, there are "  << _vecWord.size() << " words in " << filename << endl;
	ofs.close();
}
