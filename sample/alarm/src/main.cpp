#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include "AlarmManager.h"
#include <time.h>


using namespace android;


int alarmEventCallback(unsigned int repeatFlag,time_t deadline)
{
	printf("[%s:%s-%d] repeatFlag= %u,deadline = %u\n", __FILE__, __func__, __LINE__,repeatFlag,deadline);
	
	return 0;
}

int main(int argc, char* argv[])
{

	AlarmManager* pAlarmManager = AlarmManager::getInstance(100);

	pAlarmManager->registerAlarmCallback(alarmEventCallback);

	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);//real time now
	printf("clock_gettime : tv_sec=%ld, tv_nsec=%ld\n", ts.tv_sec, ts.tv_nsec);
	ts.tv_sec += 20;//alarm time
	pAlarmManager->setAlarm(ts.tv_sec);
	
	//pAlarmManager->setRepeatAlarm(ts.tv_sec,15);
	//printf("clock_gettime : tv_sec=%ld, tv_nsec=%ld\n", ts.tv_sec, ts.tv_nsec);

#if 0
	pAlarmManager->setRepeatAlarm(ts.tv_sec,5);
	pAlarmManager->setAlarm(ts.tv_sec + 2);
	pAlarmManager->setAlarm(ts.tv_sec + 2);
	pAlarmManager->setAlarm(ts.tv_sec + 4);
	pAlarmManager->setAlarm(ts.tv_sec + 6);
	pAlarmManager->cancelAlarm(ts.tv_sec + 6);
	pAlarmManager->setAlarm(ts.tv_sec + 20);
#endif

	sp<ProcessState> proc(ProcessState::self());
	proc->startThreadPool();
	IPCThreadState::self()->joinThreadPool();


	return 0;
}

