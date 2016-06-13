//4. 将Linux下的互斥锁封装成一个MutexLock类，实现互斥锁中的加锁和解锁功能

#include<iostream>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;

class MutexLock
{
	public:
		MutexLock();
		~MutexLock();

		void lock();
		void unlock();
	private:
		pthread_mutex_t _mutex;
};

MutexLock ml;
int cnt = 0;

void* thread(void* p){
	for(int i = 0; i < 2e7; i++){
		ml.lock();
		cnt++;
		ml.unlock();
	}
}

//不加锁时cnt最后结果不到4e7,加锁后可以得到4e7
int main(){
	pthread_t thid;
	pthread_create(&thid, NULL, thread, NULL);
	
	for(int i = 0; i < 2e7; i++){
		ml.lock();
		cnt++;
		ml.unlock();
	}

	sleep(1);
	cout << cnt << endl;
	return 0;
}

MutexLock::MutexLock(){
	pthread_mutex_init(&_mutex, NULL);
	cout << "init mutex" << endl;
}

MutexLock::~MutexLock(){
//	pthread_mutex_destroy(&_mutex);	
	cout << "destory mutex" << endl;
}

void MutexLock::lock(){
	pthread_mutex_lock(&_mutex);
//	cout << "lock mutex" << endl;
}

void MutexLock::unlock(){
	pthread_mutex_unlock(&_mutex);
//	cout << "unlock mutex" << endl;
}
