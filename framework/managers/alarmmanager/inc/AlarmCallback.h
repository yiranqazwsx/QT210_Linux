#ifndef _ALARM_CALL_BACK_H_
#define _ALARM_CALL_BACK_H_

#include "IAlarmCallback.h"

class AlarmCallback:public BnAlarmCallback
{
public:
	
	//AlarmCallback(AlarmManager *p);
	AlarmCallback(void *pAlarmManager);
	virtual ~AlarmCallback();
	virtual int AlarmNotifyCallback(unsigned int repeatFlag,time_t deadline); 
	//int readCallbackMsg(CommunicateData  &pdata);
	
private:
	//GQueue	     *mpIndataQueue;
	//GMutex        gmutex;
	//GCond         gcond;
	//void *mParent;
	void *mAlarmManager;
};

#endif
