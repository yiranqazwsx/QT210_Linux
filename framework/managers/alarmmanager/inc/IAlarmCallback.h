#ifndef _I_ALARM_CALLBACK_H_
#define	_I_ALARM_CALLBACK_H_

#include <binder/IInterface.h>
#include <time.h>

using namespace android;

class IAlarmCallback : public IInterface
{
public:
	DECLARE_META_INTERFACE(AlarmCallback);  
	virtual int AlarmNotifyCallback(unsigned int repeatFlag,time_t deadline) = 0; 
	enum{
		ALARM_NOTIFY_CALLBACK = IBinder::FIRST_CALL_TRANSACTION,
	};
};

class BnAlarmCallback : public BnInterface<IAlarmCallback>
{
public:
	virtual status_t onTransact(uint32_t code,  
                                    const Parcel& data,  
                                    Parcel* reply,  
                                    uint32_t flags = 0);

};

#endif //_I_ALARM_CALLBACK_H_