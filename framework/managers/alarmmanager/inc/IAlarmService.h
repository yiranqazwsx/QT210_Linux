#ifndef _I_ALARM_SERVICE_H_
#define _I_ALARM_SERVICE_H_

#include <binder/IInterface.h>
#include "IAlarmCallback.h"


using namespace android;



class IAlarmService : public IInterface
{
public:
	DECLARE_META_INTERFACE(AlarmService);
	virtual int setAlarm(time_t time,unsigned long nodeId) = 0;
	//virtual int setRepeatAlarm(unsigned int firstSetFlag,const time_t firstTime,time_t nextDeadline,time_t interval,unsigned long nodeId) = 0;
	//virtual int cancelAlarm(time_t time,unsigned long  nodeId) = 0;
	virtual int registerAlarmCallback(const sp<IAlarmCallback>& callback,unsigned long nodeId) = 0;
	enum {
		ALARM_SET = 0,
		//ALARM_SET_REPEAT,
		//ALARM_CANCEL,
		ALARM_REGISTER_CALLBACK,
	};
};

class BnAlarmService : public BnInterface<IAlarmService>
{
public:
	virtual status_t onTransact(unsigned int code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    unsigned int flags = 0);
};

#endif //_I_ALARM_SERVICE_H_
