#include "mylog.hh"

Mylog::Mylog()//此处初始化列表数据成员前不能加类限定符
	:root(Category::getRoot().getInstance("RootCat"))
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
//定义Mylog
Mylog log;

void logInfo(const string msg){
	log.info(msg);
}

void logError(const string msg){
	log.error(msg);
}
void logWarn(const string msg){
	log.warn(msg);
}

void logDebug(const string msg){
	log.debug(msg);
}
