#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include "AlarmService.h"

//#define LOG_TAG_ALARM_MAIN "AlarmService"
//#include <cutils/log.h>

using namespace android;


#if 0
/// ����һ���������߻��ѵ�source��������ʱ��������source��ȴ�����Դ
void ServiceThread()
{
    // 1���������߻��ѵ�source  
    AlarmService::AddSleepMonitorSource(); //MonitorService
    
    // 2)ģ��ĳ�ʼ������
    AlarmService *svr = AlarmService::getInstance();
	
    svr->Start();
    // 3���������߻��ѵ�source
    AlarmService::RunSleepMonitorSource();
}

gpointer LoopTaskThreadProc(gpointer data)
{
	AlarmService::InitServiceLoop(); 
	///ԭ���ĳ�ʼ�������Ƶ�����µ��߳��У���������߳̾���Ϊ������һ��source�������߻���
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

