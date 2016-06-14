//2. 封装log4cpp,使用起来比较方便，
//输出的日志信息能同时输出到终端和文件
//	加分项：输出的日志信息中最好能有文件的名字，函数的名字及其所在的行号
//			使用宏 __FILE__ __LINE__ __FUNCTION__
//
#include<cstdio>
#include<iostream>
#include<sstream>
#include<string>
#include<log4cpp/Category.hh>
#include<log4cpp/PatternLayout.hh>
#include<log4cpp/FileAppender.hh>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/Priority.hh>

using namespace std;
using namespace log4cpp;

class Mylog{
	public:
		Mylog();
		~Mylog();

		void warn(const string);
		void error(const string);
		void debug(const string);
		void info(const string);
	private://使用非静态数据成员时会报错,无法编译通过
		static Category& root; 
};

Category& Mylog::root = Category::getRoot().getInstance("RootCat");

int main(){
	cout << "hello, world" << endl;
	
	Mylog log;//创建一个log对象
	ostringstream oss;
	//由于宏在预编译阶段替换，所以必须在每一次调用log之前把oss置空并拼接一次

	oss.str("");//清空数据
	oss << "infoMsg" << " " << __FILE__ << " " << __FUNCTION__ << " " << ((int)__LINE__) -1;
	log.info(oss.str());

	oss.str("");//清空数据
	oss << "errorMsg" << " " << __FILE__ << " " << __FUNCTION__ << " " << ((int)__LINE__) -1;
	log.error(oss.str());

	oss.str("");//清空数据
	oss << "warnMsg" << " " << __FILE__ << " " << __FUNCTION__ << " " << ((int)__LINE__) -1;
	log.warn(oss.str());

	oss.str("");//清空数据
	oss << "debugMsg" << " " << __FILE__ << " " << __FUNCTION__ << " " << ((int)__LINE__) -1;
	log.debug(oss.str());
}

Mylog::Mylog()
//	:Mylog::root(Category::getRoot())
{
	//设定日志输出格式Layout
	PatternLayout* ptn2cout = new PatternLayout();
	ptn2cout->setConversionPattern("%d: %p %c %x:%m%n");
	PatternLayout* ptn2file = new PatternLayout();
	ptn2file->setConversionPattern("%d: %p %c %x:%m%n");
	
	//设定日志输出目的地Appender
	OstreamAppender* pOA = new OstreamAppender("coutAppender", &cout);
	pOA->setLayout(ptn2cout);
	FileAppender* pFA = new FileAppender("fileAppender", "Q2_log.txt");
	pFA->setLayout(ptn2file);

	//将Appender加入root并设置优先级
	root.addAppender(pOA);
	root.addAppender(pFA);
	root.setPriority(Priority::DEBUG);
}

Mylog::~Mylog(){
	Category::shutdown();
}

void Mylog::warn(const string msg){
	root.warn(msg);
}
void Mylog::error(const string msg){
	root.error(msg);
}
void Mylog::debug(const string msg){
	root.debug(msg);
}
void Mylog::info(const string msg){
	root.info(msg);
}
