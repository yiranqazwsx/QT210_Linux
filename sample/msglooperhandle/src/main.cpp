#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <time.h>
#include "AlarmManager.h"
#include <msglooperhandle/ALooper.h>
#include <pthread.h>

#include "TestNotify.h"
#include "TestAHandle.h"

using namespace android;


int alarmEventCallback(unsigned int repeatFlag,time_t deadline)
{
	printf("[%s:%s-%d] repeatFlag= %u,deadline = %lu\n", __FILE__, __func__, __LINE__,repeatFlag,deadline);
	
	return 0;
}

TestNotify *pTestNotify;




void* testNotifyThread(void *data)
{	
	//sp<AMessage> msg =new AMessage(kWhatSetDataSource, id());
}

int main(int argc, char* argv[])
{
	pthread_t tid;
	int ret = 0;
#if 0
	AlarmManager* pAlarmManager = AlarmManager::getInstance(100);

	pAlarmManager->registerAlarmCallback(alarmEventCallback);

	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);//real time now
	printf("clock_gettime : tv_sec=%ld, tv_nsec=%ld\n", ts.tv_sec, ts.tv_nsec);
	ts.tv_sec += 20;//alarm time
	pAlarmManager->setAlarm(ts.tv_sec);
	
	//pAlarmManager->setRepeatAlarm(ts.tv_sec,15);
	//printf("clock_gettime : tv_sec=%ld, tv_nsec=%ld\n", ts.tv_sec, ts.tv_nsec);


	pAlarmManager->setRepeatAlarm(ts.tv_sec,5);
	pAlarmManager->setAlarm(ts.tv_sec + 2);
	pAlarmManager->setAlarm(ts.tv_sec + 2);
	pAlarmManager->setAlarm(ts.tv_sec + 4);
	pAlarmManager->setAlarm(ts.tv_sec + 6);
	pAlarmManager->cancelAlarm(ts.tv_sec + 6);
	pAlarmManager->setAlarm(ts.tv_sec + 20);
#endif
	sp<TestAHandle> testAHandle;
	sp<ALooper> looper(new ALooper);
	
	looper->setName("mylooper");
	looper->start(
            false, /* runOnCallingThread */
            true,  /* canCallJava */
            0);//ANDROID_PRIORITY_NORMAL==0
	testAHandle = new TestAHandle;//------------创建一个AHandler即Nuplayer
	looper->registerHandler(testAHandle);//-----把该AHandler注册到Looper中，具体的实现我们往后看

#if 0
	pTestNotify = new TestNotify();
	pTestNotify->registerHandle(SIGNAL_1,testAHandle);


	ret = pthread_create(&tid, NULL, testNotifyThread, NULL); //创建线程  
	
	//proc->startThreadPool();
	//IPCThreadState::self()->joinThreadPool();
#endif

	while(1)
	{
		//testAHandle->
		printf("[%s:%s-%d] \n", __FILE__, __func__, __LINE__);
		sp<AMessage> msg =new AMessage(123,testAHandle->id());
		msg->setObject("mylooper", new AMessage(123,testAHandle->id())); 
		msg->post(1000);
		printf("[%s:%s-%d] \n", __FILE__, __func__, __LINE__);
		sleep(1);
	}
	return 0;
}

