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


AlarmManager* AlarmManager::mpInstance = NULL;


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
	LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);

	if (NULL == mpInstance)
	{
		mpInstance = new AlarmManager(nodeId);
	}
	else
	{
		LOGE("[%s:%s-%d] AlarmManager init  fail.\n", __FILE__, __func__, __LINE__);
	}

	LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);

	return mpInstance;
}


AlarmManager::AlarmManager(unsigned long  nodeId)
{
	char name8Buffer[64] = {0};
	
	sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> binder;

	binder = sm->getService(String16("alarmservice"));
	if(binder != 0)
	{	
		mIAlarmService = interface_cast<IAlarmService>(binder);

		const char16_t* name16 = mIAlarmService->getInterfaceDescriptor().string();
		//UTF16ToUTF8(name8Buffer,name16);
		//name8Buffer[63] = 0;
		mNodeId = nodeId;
		LOGD("[%s:%s-%d] AlarmManager InterfaceDescriptor = %s \n", __FILE__, __func__, __LINE__,name8Buffer);
	}
	else
	{
		LOGE("[%s:%s-%d] Binder handle not published alarmservice\n", __FILE__, __func__, __LINE__);
	}

}

AlarmManager::~AlarmManager(void)
{
	LOGD("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
}


int AlarmManager::setAlarm(time_t time)
{
	LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
	mIAlarmService->setAlarm(time, mNodeId);
	LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
	return true;
}
int AlarmManager::setRepeatAlarm(time_t time,time_t interval)
{
	LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
	//mIAlarmService->setRepeatAlarm(true,time,time,interval,mNodeId);
	LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
	return true;
}


int AlarmManager::cancelAlarm(time_t time)
{
	LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
	//mIAlarmService->cancelAlarm(time, mNodeId);
	LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
	return true;
}



bool AlarmManager::registerAlarmCallback(alarmEventCb pAlarmEventCb)
{
	LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);

	mAlarmEventCallback = pAlarmEventCb;
	
	if(0 != mIAlarmService.get())
	{
		cb = new AlarmCallback(this);
		LOGD("[%s:%s-%d] mIAlarmService->registerAlarmCallback\n", __FILE__, __func__, __LINE__);
		mIAlarmService->registerAlarmCallback(cb,mNodeId);
	}
	else
	{
		LOGE("[%s:%s-%d] Register callback fail, mIAlarmService is NULL\n", __FILE__, __func__, __LINE__);
		return false;
	}
	
	LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);

	return true;
}



