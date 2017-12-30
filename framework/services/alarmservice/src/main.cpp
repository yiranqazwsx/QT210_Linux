#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include "AlarmService.h"

//#define LOG_TAG_ALARM_MAIN "AlarmService"
//#include <cutils/log.h>

using namespace android;


#if 0
/// 新增一个用于休眠唤醒的source，在休眠时会挂在这个source里等待唤醒源
void ServiceThread()
{
    // 1）增加休眠唤醒的source  
    AlarmService::AddSleepMonitorSource(); //MonitorService
    
    // 2)模块的初始化工作
    AlarmService *svr = AlarmService::getInstance();
	
    svr->Start();
    // 3）启动休眠唤醒的source
    AlarmService::RunSleepMonitorSource();
}

gpointer LoopTaskThreadProc(gpointer data)
{
	AlarmService::InitServiceLoop(); 
	///原来的初始化工作移到这个新的线程中，新增这个线程就是为了增加一个source用于休眠唤醒
	AlarmService::StartServiceThread((GThreadFunc)ServiceThread);
	//CfgService *svr = CfgService::getInstance();    
	//svr->Start();
	AlarmService::RunServiceLoop();
	
	return NULL;
}

#endif







int main(int argc, char* argv[])
{
	int ret;	
	
	//AlarmService *pAlarmService = AlarmService::getInstance();
	sp<ProcessState> proc(ProcessState::self());
	sp<IServiceManager> sm = defaultServiceManager();
	ret = sm->addService(String16("alarmservice"), new AlarmService("123",100));
	printf("ServiceManager addService ret = %d\n", ret);
	proc->startThreadPool();
	IPCThreadState::self()->joinThreadPool();

	return 0;
}

