
#define LOG_TAG "AlarmManager"
#include <cutils/log.h>

#include <stdio.h>
#include <unistd.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include "AlarmManager.h"
//#include <uchar.h>

using namespace android;


AlarmManager* AlarmManager::m_pInstance = NULL;


#if 0

size_t UTF16ToUTF8(char *mbBuffer, const char16_t *utf16String)
{
    if(mbBuffer == NULL || utf16String == NULL)
        return 0;
	
    mbstate_t state = { };
        
    size_t mbIndex = 0;
    for(int utf16Index = 0; utf16String[utf16Index] != u'\0'; utf16Index++)
    {
        const size_t length = c16rtomb(&mbBuffer[mbIndex], utf16String[utf16Index], &state);
        mbIndex += length;
    }
    
    mbBuffer[mbIndex] = '\0';
    
    return mbIndex;
}

#endif


AlarmManager* AlarmManager::getInstance(unsigned long nodeId)
{
	printf("AlarmManager init in.\n");
	
    if (NULL == m_pInstance)
    {
        m_pInstance = new AlarmManager(nodeId);
    }
	else
    {
		printf("AlarmManager init  fail.\n");
	}

	printf("AlarmManager init  out.\n");
	
    return m_pInstance;
}


AlarmManager::AlarmManager(unsigned long  nodeId)
{
	char name8Buffer[64] = {0};
	
	sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> binder;
	do{
		binder = sm->getService(String16("alarmservice"));
		if(binder != 0)
		{
			break;
		}
		printf("Binder handle not published alarmservice, waiting...!!!\n");
		usleep(100000);
	}while(true);

	mIAlarmService = interface_cast<IAlarmService>(binder);

	const char16_t* name16 = mIAlarmService->getInterfaceDescriptor().string();
	//UTF16ToUTF8(name8Buffer,name16);
	//name8Buffer[63] = 0;

	mNodeId = nodeId;
	
	printf("AlarmManager InterfaceDescriptor = %s\n",name8Buffer);
}

AlarmManager::~AlarmManager(void)
{
	printf("~AlarmManager in.\n");

	printf("~AlarmManager out.\n");
}


int AlarmManager::setAlarm(time_t time)
{
	printf("setAlarm: %s in.\n", __func__);
	mIAlarmService->setAlarm(time, mNodeId);
	printf("setAlarm: %s out.\n", __func__);
	return true;
}
int AlarmManager::setRepeatAlarm(time_t time,time_t interval)
{
	printf("setAlarm: %s in.\n", __func__);
	//mIAlarmService->setRepeatAlarm(true,time,time,interval,mNodeId);
	printf("setAlarm: %s out.\n", __func__);
	return true;
}


int AlarmManager::cancelAlarm(time_t time)
{
	printf("setAlarm: %s in.\n", __func__);
	//mIAlarmService->cancelAlarm(time, mNodeId);
	printf("setAlarm: %s out.\n", __func__);
	return true;
}



bool AlarmManager::registerAlarmCallback(alarmEventCb pAlarmEventCb)
{
	printf("registerAlarmCallback in.\n");

	mAlarmEventCallback = pAlarmEventCb;
	
	if(0 != mIAlarmService.get())
	{
		cb = new AlarmCallback(this);
		printf("mIAlarmService->registerAlarmCallback .\n");
		mIAlarmService->registerAlarmCallback(cb,mNodeId);
	}
	else
	{
		printf("Register callback fail, mIAlarmService is NULL.\n");
		return false;
	}
	
	printf("registerAlarmCallback out.\n");

	return true;
}



