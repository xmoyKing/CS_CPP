#include "mylog.hh"

int main(){
	cout << "hello, world" << endl;
	
	//ostringstream oss;//此处使用oss有些麻烦可以直接使用string类
	//oss.str("");//清空数据
	//oss << "debugMsg" << " " << __FILE__ << " " << __FUNCTION__ << " " << ((int)__LINE__) +1;
	//由于宏在预编译阶段替换，所以必须在每一次调用log之前把oss置空并拼接一次
	string oss = "msg";

	logInfo(oss);
	logError(oss);
	logWarn(oss);
	logDebug(oss);
}
