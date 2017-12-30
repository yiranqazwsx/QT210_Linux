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
	sp<IAlarmService> mIAlarmService;
	alarmEventCb	mAlarmEventCallback;
	
	static AlarmManager* getInstance(unsigned long nodeId);
	AlarmManager(unsigned long nodeId);
	~AlarmManager(void);
	
	int setAlarm(time_t time);
	int setRepeatAlarm(time_t time,time_t interval);
	int cancelAlarm(time_t time);
	
	bool registerAlarmCallback(alarmEventCb pAlarmEventCb);
	//virtual void callback(void) = 0;
	//void *pSon;
protected:

private:
	static  AlarmManager *m_pInstance;
	sp<AlarmCallback> cb;
	unsigned long mNodeId;
};
#endif  //__ALARM_MANAGER_H__
