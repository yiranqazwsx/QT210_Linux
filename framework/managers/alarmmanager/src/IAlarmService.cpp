
#define LOG_TAG "IAlarmService"
#include <binder/Parcel.h>
#include "IAlarmService.h"
#include "IAlarmCallback.h"

#include <cutils/log.h>


using namespace android;

class BpAlarmService : public BpInterface<IAlarmService>
{
public:

	BpAlarmService(const sp<IBinder>& impl) : BpInterface<IAlarmService>(impl)
    {
    	
    }

	virtual int setAlarm(time_t time,unsigned long nodeId)
	{
		LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);

		Parcel data, reply;
		//data.writeInterfaceToken(IMcuComManager::getInterfaceDescriptor());

		data.writeInt64(time);
		data.writeInt64(nodeId);
		remote()->transact(ALARM_SET, data, &reply);
		int res = reply.readInt32();  

		LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);

		return res;
	}
#if 0
	virtual int setRepeatAlarm(unsigned int firstSetFlag,const time_t firstTime,time_t nextDeadline,time_t interval,unsigned long nodeId)
	{
		LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);

		Parcel data, reply;
		//data.writeInterfaceToken(IMcuComManager::getInterfaceDescriptor());
		data.writeInt32(firstSetFlag);
		data.writeInt64(firstTime);
		data.writeInt64(nextDeadline);
		data.writeInt64(interval);	
		data.writeInt64(nodeId);

		remote()->transact(ALARM_SET_REPEAT, data, &reply);
		int res = reply.readInt32();  

		LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);

		return res;
	}

	virtual int cancelAlarm(time_t time,unsigned long nodeId)
	{
		LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);

		Parcel data, reply;
       	//data.writeInterfaceToken(IMcuComManager::getInterfaceDescriptor());
       	data.writeInt64(time);
		data.writeInt64(nodeId);
      
       	remote()->transact(ALARM_CANCEL, data, &reply);
		int res = reply.readInt32();

		LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);

		return res;
	}
#endif


	virtual int registerAlarmCallback(const sp<IAlarmCallback>& callback,unsigned long nodeId)
	{

		LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);

		Parcel data, reply;
		//data.writeStrongBinder(IInterface::asBinder(callback));
		data.writeStrongBinder(callback->asBinder());
		data.writeInt64(nodeId);
		remote()->transact(ALARM_REGISTER_CALLBACK, data, &reply);
		int res = reply.readInt32();
		
		LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
		return 0;
	}

};

IMPLEMENT_META_INTERFACE(AlarmService, "Desay.IAlarmService");

status_t BnAlarmService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
	LOGV("[%s:%s-%d] code = \n", __FILE__, __func__, __LINE__,code);
	
	switch(code){
		
		
		case ALARM_SET:
		{
			//CHECK_INTERFACE(IMcuComManager, data, reply);
			
			//LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
			
			time_t time = data.readInt64();
			unsigned long nodeId = data.readInt64();
			//LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
			int res = setAlarm(time,nodeId);
			reply->writeInt32(res);
			
            		return res;
		}
		
		break;
		
#if 0
		case ALARM_SET_REPEAT:
		{

			//CHECK_INTERFACE(IMcuComManager, data, reply);
			//const char *clientName = data.readCString();
			//LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
			unsigned int firstSetFlag = data.readInt32();
			time_t firstTime = data.readInt64();
			time_t nextDeadline = data.readInt64();
			time_t interval = data.readInt64();
			unsigned long nodeId = data.readInt64();
			int res = setRepeatAlarm(firstSetFlag,firstTime,nextDeadline,interval,nodeId);
			reply->writeInt32(res);
            		return res;
		}
		break;

		case ALARM_CANCEL:
		{
			//CHECK_INTERFACE(IMcuComManager, data, reply);
			//const char *clientName = data.readCString();
			//LOGV("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
			time_t time = data.readInt64();
			unsigned long nodeId = data.readInt64();
			int res = cancelAlarm(time,nodeId);
			reply->writeInt32(res);
            return res;
		}
		break;
#endif
		
		case ALARM_REGISTER_CALLBACK:
		{
			int res= 0 ;
			//const char *clientName = data.readCString();
			sp<IAlarmCallback> callback = interface_cast<IAlarmCallback>(data.readStrongBinder());
			unsigned long nodeId = data.readInt64();
			res = registerAlarmCallback(callback,nodeId);
			reply->writeInt32(res);
			return res;
		}
		break;


		default:
            return BBinder::onTransact(code, data, reply, flags);
	}
}

