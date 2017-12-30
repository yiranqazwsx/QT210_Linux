#ifndef __ALARM_MANAGER_H__
#define __ALARM_MANAGER_H__

#include <binder/IServiceManager.h>
#include "IAlarmService.h"
#include "AlarmCallback.h"

using namespace android;

typedef int (* alarmEventCb)(unsigned int repeatFlag,time_t deadline);


//typedef int (* cfg_change_callback)(int iFlag, char * pModuleName, char * pItemName, char * pValue);

class AlarmManager
{
public:
	static AlarmManager* getInstance(unsigned long nodeId);
	~AlarmManager(void);
	int setAlarm(time_t time);
	int setRepeatAlarm(time_t time,time_t interval);
	int cancelAlarm(time_t time);
	bool registerAlarmCallback(alarmEventCb pAlarmEventCb);
	alarmEventCb	mAlarmEventCallback;
	//virtual void callback(void) = 0;
	//void *pSon;
protected:
	
	
private:
	AlarmManager(unsigned long nodeId);
	sp<IAlarmService> mIAlarmService;

	static  AlarmManager *mpInstance;
	sp<AlarmCallback> cb;
	unsigned long mNodeId;
};
#endif  //__ALARM_MANAGER_H__
