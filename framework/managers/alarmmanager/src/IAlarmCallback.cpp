#include <binder/Parcel.h>

#include "IAlarmCallback.h"

using namespace android;

class BpAlarmCallback : public BpInterface<IAlarmCallback>
{
public:
	BpAlarmCallback(const sp<IBinder> & impl) : BpInterface<IAlarmCallback>(impl)
    {
    
    }
	virtual int AlarmNotifyCallback(unsigned int repeatFlag,time_t deadline)
	{
        printf("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);  
        Parcel data,reply;
		data.writeInt32(repeatFlag);
		data.writeInt64(deadline);
        remote()->transact(ALARM_NOTIFY_CALLBACK, data, &reply);
        return reply.readInt32();  
	}  
};

IMPLEMENT_META_INTERFACE(AlarmCallback, "Desay.IAlarmCallback");

status_t BnAlarmCallback::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
	switch(code) 
	{
		case ALARM_NOTIFY_CALLBACK:
		{
			printf("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);  
			unsigned int repeatFlag = data.readInt32();
			time_t deadline = data.readInt64();
			int res = AlarmNotifyCallback(repeatFlag,deadline);
			reply->writeInt32(res);
			return NO_ERROR;
		}
		break;
		
		default:
	    return BBinder::onTransact(code, data, reply, flags);
	}
}
