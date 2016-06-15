//2. 封装log4cpp,使用起来比较方便，
//输出的日志信息能同时输出到终端和文件
//	加分项：输出的日志信息中最好能有文件的名字，函数的名字及其所在的行号
//			使用宏 __FILE__ __LINE__ __FUNCTION__

#ifndef __MYLOG_H__
#define __MYLOG_H__

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
		 Category& root; 
};

void logInfo(const string);
void logError(const string);
void logWarn(const string);
void logDebug(const string);

#endif
