//3. 在封装完MutexLock之后，封装条件变量Condition类
//

#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;


class MutexLock{
	public:
//		MutexLock();//默认构造函数
		void lock();
		void unlock();
		pthread_mutex_t* getMutexPtr();
	private:
		pthread_mutex_t _mutex;
};

void MutexLock::lock(){
	pthread_mutex_lock(&_mutex);
}

void MutexLock::unlock(){
	pthread_mutex_unlock(&_mutex);
}

pthread_mutex_t* MutexLock::getMutexPtr(){
	return &_mutex;
}


/////////////////////////////////
class Condition{
	public:
//		Condition();//默认构造函数
		void wait(MutexLock&);
		void notify();//只唤醒等待的1个
		void notifyall();//广播唤醒所有等待的
	private:
		pthread_cond_t _cond;
};

void Condition::wait(MutexLock& m){
	pthread_cond_wait(&_cond, m.getMutexPtr());
}

void Condition::notify(){
	pthread_cond_signal(&_cond);
}

void Condition::notifyall(){
	pthread_cond_broadcast(&_cond);
}

/////////////////////////////////
MutexLock ml;
Condition cd;
/////////////////////////////////
//线程清理函数
void cl(void* p){
	ml.unlock();
	pthread_exit((void*)1);
}

//线程函数
void* thread(void* p){
	pthread_cleanup_push(cl, NULL);
	
	ml.lock();
	cout << "2. child wait" <<endl;
	cd.wait(ml);//wait需要MutexLock&引用类型
	cout << "4. child wake up" << endl;
	ml.unlock();

	pthread_cleanup_pop(0);
	pthread_exit((void*)0);
}

int main(){
	pthread_t thid;
	//创建子线程
	pthread_create(&thid, NULL, thread, NULL);
	cout << "1. parent sleep" << endl;
	sleep(2);//主线程睡一会儿
	cout << "3. parent wake up" << endl;
	cd.notify();

	//获取子线程返回值
	int ret;
	pthread_join(thid, (void**)&ret);
	cout<< "5. child return " << ret << endl;

	//主线程结束，自动调用ml和cd的析构函数
	return 0;
}

