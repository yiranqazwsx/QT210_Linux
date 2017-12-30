#ifndef __ALARM_SERVICE_H__
#define __ALARM_SERVICE_H__
#include <time.h>
#include "IAlarmService.h"
#include "IAlarmCallback.h"

using namespace android;

#define ALARM_SERVICE_NAME "DSVAlarmSVC"
#define ALARM_SERVICE_NODE_ID  100


typedef enum _eAlarmServiceErrorCode
{
	ALARM_SERVICE_CANCAL_NO_EXIST,
	ALARM_SERVICE_CANCAL_OK,
	ALARM_SERVICE_ERROR_MAX
}ALARM_SERVICE_ERROR_CODE;


typedef struct
{
	unsigned long  mNodeId;
	sp<IAlarmCallback> mCallback;
}AlarmCbNode;

typedef struct alarm  
{
	char name[10];
	unsigned int firstDeadline;//start time,it is unique,not change

	unsigned int mNodeId;	
	bool repeatBit;// true is repeat alarm,false is normal alarm
	unsigned int nextDeadline;//now time + interval,only for repeat alarm
	int interval;//only for repeat alarm
}AlarmTimeNode;

//AlarmEvent *rtcAlarmEventList;
//AlarmEvent *elapseAlarmEventList;


#if 0
//pthread_mutex_t mutexForGetInstance;
//pthread_mutex_init(&mutexForGetInstance, NULL);
//AutolockInServiceSVC _l(mutexForGetInstance);
//delete _l;

class AutolockInServiceSVC {
    public:
        AutolockInServiceSVC(pthread_mutex_t& mutex) : mLock(mutex) { pthread_mutex_lock(&mLock); }
		~AutolockInServiceSVC() { pthread_mutex_unlock(&mLock); }
    private:
        pthread_mutex_t& mLock;
};
#endif


class AlarmService : public BnAlarmService
{
public:
	static AlarmService* getInstance();
	static AlarmService *mInstance;	
	~AlarmService();
	
	int setAlarm(time_t time,unsigned long nodeId);
	static void* alarmWaitNotifyThreadProc(void *data);

//	int setRepeatAlarm(guint firstSetFlag,const time_t firstTime,time_t nextDeadline,time_t interval,guint64 nodeId);
//	int cancelAlarm(time_t time,guint64 nodeId);
	int registerAlarmCallback(const sp<IAlarmCallback>& callback,unsigned long nodeId);
#if 0
protected:
	static gpointer alarmWaitNotifyThreadProc(gpointer data);
	
	
private:
	bool isSameAlarm(GArray *pRtcAlarmTimeList,AlarmTimeNode *newClient);
	bool addToAlarmTimeList(GArray *pRtcAlarmTimeList,AlarmTimeNode *newClient);
	int filterAlarmTimeListAndCallback(GArray *pRtcAlarmTimeList);
	int adjustFromAlarmTimeList(GArray *pRtcAlarmTimeList,int removeCnt);
	void dumpAllAlarmTime(GArray* a);
	int resetAlarm(void);
	int deleteAlarm(time_t time,guint64 nodeId);
	
	int waitAlarm(void);
	void startAlarmCallback(AlarmTimeNode *alarmNode);

	void wakeLock(void);
	void wakeUnlock(void);
	
	int sortTest(void);
	void sortTest2 (void);


	static AlarmService *mInstance;
	bool mIsBusy;
	
	bool IsBusy();
	void SetBusy(bool busy);

#if 0

	TPBool	        m_blThreadRun;
#endif



	GPtrArray      *mAlarmCbList;
	GMutex 			mRegList_mutex;

	GArray      *mRtcAlarmTimeList;
	//GArray      *a;
	GMutex 			mRtcAlarmTimemutex;
	
	GPtrArray      *mElapseAlarmTimeList;

#endif
	int fd;
	//GMutex 			mRegList_mutex;
	sp<IAlarmCallback> mCallback;
	
	AlarmService(char *svr_name,unsigned long node_id);

};

#endif //__MCU_COM_SERVICE_H__

