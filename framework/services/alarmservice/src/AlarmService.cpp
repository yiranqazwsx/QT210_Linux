
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "android_alarm.h"
#include <sys/ioctl.h>
#include <linux/rtc.h>
#include <unistd.h>
#include<pthread.h> 

#include <iostream>

#define LOG_TAG "AlarmService"
#include <cutils/log.h>
#include "AlarmService.h"

#define RTC_DEV "/dev/rtc0"

AlarmService* AlarmService::mInstance = NULL;


AlarmService* AlarmService::getInstance()
{	
	LOGD("getInstance: %s in.\n", __func__);

	if(NULL == mInstance)
	{
		mInstance = new AlarmService(ALARM_SERVICE_NAME,ALARM_SERVICE_NODE_ID);
	}
	
	LOGD( "getInstance: %s out.\n", __func__);

	return mInstance;
}

//void* alarmWaitNotifyThreadProc(void *data);

AlarmService::AlarmService(char *svr_name,unsigned long node_id)
{
	pthread_t tid;
	int ret = 0;

	mCallback = NULL;
#if 0
	//m_blThreadRun		= true;
	//g_pNotifyQueue      = g_queue_new();
	
     mIsBusy = false ;

	mAlarmCbList = g_ptr_array_new();
	g_mutex_init(&mRegList_mutex);

	//mRtcAlarmTimeList = g_ptr_array_new();
	//a = g_array_new(FALSE, FALSE, sizeof(AlarmTimeNode));
	
	mRtcAlarmTimeList = g_array_new(FALSE, FALSE, sizeof(AlarmTimeNode));
	g_mutex_init(&mRtcAlarmTimemutex);
	
	//g_mutex_init(&notify_mutex);
	//g_mutex_init(&mmutex);
	//g_cond_init(&mcond);

#endif

	fd = open("/dev/alarm", O_RDWR);
	if(fd < 0) {
		LOGE("Unable to open alarm driver: %s\n", strerror(errno));
	}
	else
	{
		LOGD("/dev/alarm open ok\n");
	}
	
	//g_thread_new ("AlarmServiceWaitThread",(GThreadFunc)alarmWaitNotifyThreadProc,(gpointer)this);
	
	ret = pthread_create(&tid, NULL, alarmWaitNotifyThreadProc, (void *)this); //创建线程  
    	if(ret != 0){
		LOGE("pthread_create fail\n");
	}
	else
	{
		LOGD("pthread_create OK\n");
	}

}

AlarmService::~AlarmService()
{
#if 0
	//if(g_pNotifyQueue)
	//{
	//	g_queue_free(g_pNotifyQueue);
	//}
	//g_pNotifyQueue = NULL;

	g_mutex_clear(&mRegList_mutex);
	g_mutex_clear(&mRtcAlarmTimemutex);

	///TODO:free g_array_new  and free g_array_new
	//g_mutex_clear(&notify_mutex );
	//g_mutex_clear(&mmutex);
	//g_cond_clear(&mcond);
#endif

}

int AlarmService::setAlarm(time_t deadline,unsigned long nodeId)
{
	

	// 2 time more than time(null)
	
	// 3 check rtc list,if it is least,cancel last one,and set into kernel
	//gboolean			bIsFind  = false; 
	LOGD("AlarmService setAlarm in.\n");
#if 0
	if((0 == nodeId) || (0 == deadline))
	{
		LOGD("nodeId == 0 or callback is NULL.\n");
		return 0;
	}
	
	AlarmTimeNode *newClient = NULL;
	newClient = new AlarmTimeNode;
	newClient->mNodeId = nodeId;
	newClient->repeatBit = false;
	newClient->firstDeadline = deadline;
	newClient->nextDeadline = deadline;
	
	g_mutex_lock(&mRtcAlarmTimemutex);
	
	if(false == addToAlarmTimeList(mRtcAlarmTimeList,newClient))
	{
		delete newClient;
	}
	//dumpAllAlarmTime(mRtcAlarmTimeList);
	g_mutex_unlock(&mRtcAlarmTimemutex);	
#endif
	
	LOGD("AlarmService setAlarm out.\n");
	return 1;

}


void* AlarmService::alarmWaitNotifyThreadProc(void *data)
{	
#if 0
	AlarmService* pThis = (AlarmService*)data;
	int ret = 0;
	int pos = 0;
	
	//thread to wait alarm and callback
	while(1)
	{
		ret = pThis->waitAlarm();
		pThis->wakeLock();
		LOGD("[%s:%s-%d]\n",__FILE__, __func__, __LINE__);
		
		if(ret == ANDROID_ALARM_RTC_WAKEUP_MASK)		
		{
			pos = pThis->filterAlarmTimeListAndCallback(pThis->mRtcAlarmTimeList);
			if(0 == pos)
			{
				continue;
			}
			LOGD("%s ret = %d,pos = %d\n",__func__,ret,pos);
			
			pThis->adjustFromAlarmTimeList(pThis->mRtcAlarmTimeList,pos);
			pThis->dumpAllAlarmTime(pThis->mRtcAlarmTimeList);
			
			//clear and reset alarm
			if(0 != pThis->mRtcAlarmTimeList->len)
			{
				struct timespec ts;
				AlarmTimeNode *newClient;

				ioctl(pThis->fd, ANDROID_ALARM_CLEAR(ANDROID_ALARM_RTC_WAKEUP));
				
				newClient = &(g_array_index(pThis->mRtcAlarmTimeList, AlarmTimeNode, 0));
				ts.tv_sec = newClient->nextDeadline;
				ts.tv_nsec = 0;		
				ioctl(pThis->fd, ANDROID_ALARM_SET(ANDROID_ALARM_RTC_WAKEUP),&ts);
				LOGD("%s,clear and reset ts.tv_sec = %u\r\n",__func__,ts.tv_sec );
			}
		}
		else if(ret == ANDROID_ALARM_RTC_WAKEUP_MASK)
		{
			
		}
		
		LOGD("have 10s alive\n");
		sleep(10);
		pThis->wakeUnlock();
	}
#endif

	AlarmService* pAlarmService = (AlarmService*)data;

	while(1)
	{
		LOGD("alarmWaitNotifyThreadProc int.\n");
		sleep(5);
		if(NULL != pAlarmService->mCallback.get())
		{
			pAlarmService->mCallback->AlarmNotifyCallback(0,123456789);
		}
		LOGD("alarmWaitNotifyThreadProc out.\n");
	}
	return NULL;
}






#if 0


int AlarmService::waitAlarm(void)
{
	return ioctl(fd, ANDROID_ALARM_WAIT);
}


void AlarmService::startAlarmCallback(AlarmTimeNode *alarmNode)
{
	AlarmCbNode *newclient	 = NULL;
	
	for (guint i = 0; i < mAlarmCbList->len; i++)
	{	
		g_mutex_lock(&mRegList_mutex);
		newclient = (AlarmCbNode *)g_ptr_array_index(mAlarmCbList, i);
		g_mutex_unlock(&mRegList_mutex);
		
		if((NULL != newclient) && (alarmNode->mNodeId == newclient->mNodeId))
		{
			sp<IAlarmCallback> cb = newclient->mCallback;
			LOGD("%s cb->AlarmNotifyCallback,nodeId = %u,repeatBit = %u,firstDeadline = %u\n",
					__func__,alarmNode->mNodeId,alarmNode->repeatBit,alarmNode->firstDeadline);
			
			cb->AlarmNotifyCallback(alarmNode->repeatBit,alarmNode->firstDeadline);
		}
	}
}




gpointer AlarmService::alarmWaitNotifyThreadProc(gpointer data)
{	
	AlarmService* pThis = (AlarmService*)data;
	int ret = 0;
	int pos = 0;
	
	//thread to wait alarm and callback
	while(1)
	{
		ret = pThis->waitAlarm();
		pThis->wakeLock();
		LOGD("[%s:%s-%d]\n",__FILE__, __func__, __LINE__);
		
		if(ret == ANDROID_ALARM_RTC_WAKEUP_MASK)		
		{
			pos = pThis->filterAlarmTimeListAndCallback(pThis->mRtcAlarmTimeList);
			if(0 == pos)
			{
				continue;
			}
			LOGD("%s ret = %d,pos = %d\n",__func__,ret,pos);
			
			pThis->adjustFromAlarmTimeList(pThis->mRtcAlarmTimeList,pos);
			pThis->dumpAllAlarmTime(pThis->mRtcAlarmTimeList);
			
			//clear and reset alarm
			if(0 != pThis->mRtcAlarmTimeList->len)
			{
				struct timespec ts;
				AlarmTimeNode *newClient;

				ioctl(pThis->fd, ANDROID_ALARM_CLEAR(ANDROID_ALARM_RTC_WAKEUP));
				
				newClient = &(g_array_index(pThis->mRtcAlarmTimeList, AlarmTimeNode, 0));
				ts.tv_sec = newClient->nextDeadline;
				ts.tv_nsec = 0;		
				ioctl(pThis->fd, ANDROID_ALARM_SET(ANDROID_ALARM_RTC_WAKEUP),&ts);
				LOGD("%s,clear and reset ts.tv_sec = %u\r\n",__func__,ts.tv_sec );
			}
		}
		else if(ret == ANDROID_ALARM_RTC_WAKEUP_MASK)
		{
			
		}
		
		LOGD("have 10s alive\n");
		sleep(10);
		pThis->wakeUnlock();
	}
	return NULL;
}



void AlarmService::dumpAllAlarmTime(GArray* a) 
{
	LOGD("\r\nAllAlarmTime \r\n");

	if(0 == a->len)
	{
		LOGD("no alarm\r\n");
	}	
	for (guint i = 0; i < a->len; i++)
	{
		AlarmTimeNode *newclient = &(g_array_index(a, AlarmTimeNode, i));
		LOGD("firstDeadline = %u,nextDeadline = %u,appNodeId = %u,repeatBit = %d\r\n",
			newclient->firstDeadline,newclient->nextDeadline,newclient->mNodeId,newclient->repeatBit);
	}

	LOGD("\r\n");
	
}


bool AlarmService::isSameAlarm(GArray *pRtcAlarmTimeList,AlarmTimeNode *newClient)
{
	int pos = 0;

	for(pos = 0; pos < pRtcAlarmTimeList->len; pos++)
	{
		AlarmTimeNode *alarmNode = &(g_array_index(pRtcAlarmTimeList, AlarmTimeNode, pos));
		LOGD("alarmNode->nextDeadline = %u,alarmNode->mNodeId = %u\n", alarmNode->nextDeadline,alarmNode->mNodeId);
		LOGD("newClient->nextDeadline = %u,newClient->mNodeId = %u\n", newClient->nextDeadline,newClient->mNodeId);

		if((newClient->nextDeadline == alarmNode->nextDeadline) && 
			(newClient->mNodeId == alarmNode->mNodeId) && //same process not add to mRtcAlarmTimeList
			(newClient->repeatBit == false) 
			)
		{
			return true;
		}
	}
	return false;
}


bool AlarmService::addToAlarmTimeList(GArray *pRtcAlarmTimeList,AlarmTimeNode *newClient)
{
	bool ret = false;
	
	if(0 == pRtcAlarmTimeList->len)
	{
		g_array_append_vals(mRtcAlarmTimeList,newClient, 1);
		LOGD("ANDROID_ALARM_RTC_WAKEUP first one newClient->nextDeadline = %u\n", newClient->nextDeadline);
		struct timespec ts;
		ts.tv_sec = newClient->nextDeadline;
		ts.tv_nsec = 0;
		ioctl(fd, ANDROID_ALARM_SET(ANDROID_ALARM_RTC_WAKEUP),&ts);
		ret = true;
	}
	else if(false == isSameAlarm(pRtcAlarmTimeList,newClient))
	{
		int pos = 0;
		for(pos = 0; pos < mRtcAlarmTimeList->len; pos++)
		{
			AlarmTimeNode *alarmNode = &(g_array_index(pRtcAlarmTimeList, AlarmTimeNode, pos));

			if(newClient->nextDeadline <= alarmNode->nextDeadline)
			{
				LOGD("[%s:%s-%d] pos = %d\n",__FILE__, __func__, __LINE__,pos);
				break;
			}
		}

		if(pos == mRtcAlarmTimeList->len)
		{
			g_array_append_vals(mRtcAlarmTimeList,newClient, 1);
		}
		else if(pos < mRtcAlarmTimeList->len)
		{
			g_array_insert_val(mRtcAlarmTimeList, pos, *newClient);
			if(pos == 0)
			{
				struct timespec ts;

				ts.tv_sec = newClient->nextDeadline;
				ts.tv_nsec = 0;
				
				ioctl(fd, ANDROID_ALARM_CLEAR(ANDROID_ALARM_RTC_WAKEUP));
				ioctl(fd, ANDROID_ALARM_SET(ANDROID_ALARM_RTC_WAKEUP),&ts);

				LOGD("clear and reset ts.tv_sec  = %u\r\n",ts.tv_sec );
			}
		}
		ret = true;
	}
	else
	{
		LOGD("add same alarm error\n");
		ret =  false;
	}
	return ret;
}


int AlarmService::adjustFromAlarmTimeList(GArray *pRtcAlarmTimeList,int pos)
{
	///TODO:think in repeat alarm case
	for(int i=0; i<pos; ++i)
	{
		AlarmTimeNode *alarmNode = &(g_array_index(pRtcAlarmTimeList, AlarmTimeNode, 0));
		LOGD("[%s:%s-%d] nextDeadline = %u,nextDeadline = %u,mNodeId = %u,repeatBit = %u\n", 
					__FILE__, __func__, __LINE__,alarmNode->nextDeadline,alarmNode->nextDeadline,alarmNode->mNodeId,alarmNode->repeatBit);
		
		if(true == alarmNode->repeatBit)
		{
			struct timespec ts;
			clock_gettime(CLOCK_REALTIME, &ts);//real time now
			setRepeatAlarm(false,alarmNode->firstDeadline,ts.tv_sec + alarmNode->interval,alarmNode->interval,alarmNode->mNodeId);
		}
		//error
		
		g_array_remove_index(pRtcAlarmTimeList,0);
	}

	//first delete alarmNode->repeatBit == false

	//than  setRepeatAlarm
	return 0;
}



int AlarmService::filterAlarmTimeListAndCallback(GArray *pRtcAlarmTimeList)
{
	int pos = 0;
	
	if(0 == pRtcAlarmTimeList->len)
	{
		pos = 0;
	}
	else
	{
		///TODO: g_array_remove_index maybe leak memory
		AlarmTimeNode *alarmNode = &(g_array_index(pRtcAlarmTimeList, AlarmTimeNode, 0));
		time_t tmpTime = alarmNode->nextDeadline;
		unsigned long tmpNodeId =  alarmNode->mNodeId;
		
		startAlarmCallback(alarmNode);

		pos = 1;
		
		for(guint i = 1; i < mRtcAlarmTimeList->len; i++)
		{
			alarmNode = &(g_array_index(pRtcAlarmTimeList, AlarmTimeNode, i));
			
			if(tmpTime == alarmNode->nextDeadline)
			{
				startAlarmCallback(alarmNode);
				pos++;
				LOGD("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
			}
			else
			{
				LOGD("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
				break;
			}
		}
		
	}
	return pos;
}





#if 0

gint ptr_compare_data (gconstpointer p1, gconstpointer p2)

//gint ptr_compare_data (gconstpointer p1, gconstpointer p2, gpointer data)
{
  //gpointer i1 = *(gpointer*)p1;
  //gpointer i2 = *(gpointer*)p2;

  //return GPOINTER_TO_INT (i1) - GPOINTER_TO_INT (i2);
  
  const AlarmTimeNode *i1 = (AlarmTimeNode *)p1;
  const AlarmTimeNode *i2 = (AlarmTimeNode *)p2;
  
  LOGD("i1->times = %d,i2->times = %d\r\n",i1->time,i2->time);
  return 1;
}

//#define g_array_index(a,t,i)      (((t*) (void *) (a)->data) [(i)])
//g_array_index(a, AlarmTimeNode, i); (((AlarmTimeNode *(void *)(a))->data)[])



int AlarmService::sortTest(void)
{


#if 0
	AlarmTimeNode x[2] = {{1,"1234"},{5,"45678"}};
	g_array_append_vals(a, &x, 2);
	prt(a);
	LOGD("Inserting a '2'\n");
	AlarmTimeNode b = {2,"abc"};
	g_array_insert_val(a, 1, b);
	prt(a);
	LOGD("Inserting multiple values\n");
	//int y[2] = {3,4};
	//g_array_insert_vals(a, 2, y, 2);
	//prt(a);
	g_array_free(a, FALSE);
#endif


#if 1
	gint prev, cur;

	for(int i = 0; i < 10; ++i)
	{		
		AlarmTimeNode *newClient = new AlarmTimeNode;
		memset(newClient,0,sizeof(AlarmTimeNode));
		//AlarmTimeNode *newClient = (AlarmTimeNode *)g_malloc(sizeof (AlarmTimeNode));
		//strcpy(newClient->mClientName, clientName);
		//newClient->mNodeId = 0;
		//newClient->repeatBit = false;
		//newClient->time = g_random_int_range (0, 9);
		newClient->mNodeId = 12345678;
		newClient->time = time(NULL);
		strcpy(newClient->name,"1234");
		newClient->repeatBit = false;
		LOGD("before newclient->mNodeId = %u\r\n",newClient->mNodeId);
		g_array_append_vals(a, newClient, 1);
	}
	

	AlarmTimeNode *newClient = new AlarmTimeNode;
	memset(newClient,0,sizeof(AlarmTimeNode));
	newClient->mNodeId = 12345678;
	newClient->time = time(NULL);
	strcpy(newClient->name,"56789");
	g_array_insert_val(a, 3, *newClient);

	//g_array_prepend_vals(a,newClient, 1);

	prt(a);
	g_array_remove_index(a,1);
	prt(a);

	//g_ptr_array_sort (mRtcAlarmTimeList, ptr_compare_data);
	//g_ptr_array_sort_with_data (mRtcAlarmTimeList, ptr_compare_data, NULL);
	//g_qsort_with_data (mRtcAlarmTimeList, 10, sizeof (AlarmTimeNode), ptr_compare_data, NULL);
	
	for (int i = 0; i < 10; i++)
	{
		//AlarmTimeNode *newclient = (AlarmTimeNode *)g_ptr_array_index(mRtcAlarmTimeList, i);
		//LOGD("after newclient->times = %d\r\n",newclient->time);
		//cur = GPOINTER_TO_INT (g_ptr_array_index (gparray, i));
		//g_assert_cmpint (prev, <=, cur);
		//prev = cur;
	}

#endif


}
#endif



#if 0

typedef struct {
  int val;
  int i;
} SortItem;


int
item_compare_data (gconstpointer p1, gconstpointer p2, gpointer data)
{
  const SortItem *i1 = (SortItem *)p1;
  const SortItem *i2 = (SortItem *)p2;

  return i1->val - i2->val;
}






void
AlarmService::sortTest2 (void)
{
  SortItem *data;
  gint i;

  data = (SortItem *)g_malloc (100 * sizeof (SortItem));
  for (i = 0; i < 100; i++)
    {
      data[i].val = g_random_int_range (0, 100);
      data[i].i = i;
    }

  g_qsort_with_data (data, 100, sizeof (SortItem), item_compare_data, NULL);

  for (i = 1; i < 100; i++)
    {
      //g_assert_cmpint (data[i -1].val, <=, data[i].val);
      //if (data[i -1].val == data[i].val)
      //  g_assert_cmpint (data[i -1].i, <, data[i].i);
      
    //SortItem *newclient = (AlarmTimeNode *)g_ptr_array_index(mRtcAlarmTimeList, i);
    
	LOGD("after SortItem->val = %d\r\n",data[i].val);
    }
  g_free (data);
}
#endif




int AlarmService::setRepeatAlarm(guint firstSetFlag,const time_t firstTime,time_t nextDeadline,time_t interval,unsigned long nodeId)
{
	LOGD("[%s:%s-%d] firstSetFlag = %u,firstTime = %u,nextRepeatTime = %u,interval= %u,nodeId = %u\n",
					__FILE__, __func__, __LINE__,firstSetFlag,firstTime,nextDeadline,interval,nodeId);
	
	if((0 == nodeId) || (0 == firstTime) || (nextDeadline == 0)|| (0 == interval))
	{
		LOGD("nodeId == 0 or callback or 0 == interval is NULL.\n");
		return 0;
	}
	
	AlarmTimeNode *newClient = NULL;
	newClient = new AlarmTimeNode;
	newClient->mNodeId = nodeId;
	newClient->repeatBit = true;
	newClient->interval = interval;
	
	
	if(true == firstSetFlag)
	{
		newClient->firstDeadline = firstTime;//it is unique for cancel time, not change
		newClient->nextDeadline = firstTime;
	}
	else
	{
		newClient->firstDeadline = firstTime;
		newClient->nextDeadline = nextDeadline;
	}
	
	g_mutex_lock(&mRtcAlarmTimemutex);
	
	if(false == addToAlarmTimeList(mRtcAlarmTimeList,newClient))
	{
		delete newClient;
	}
	
	//dumpAllAlarmTime(mRtcAlarmTimeList);
	g_mutex_unlock(&mRtcAlarmTimemutex);

	LOGD("AlarmService registerAlarmCallback out.\n");
	return 0;
	
}


int AlarmService::resetAlarm(void)
{
	int ret = -1;
	ioctl(fd, ANDROID_ALARM_CLEAR(ANDROID_ALARM_RTC_WAKEUP));

	
	AlarmTimeNode *alarmNode = &(g_array_index(mRtcAlarmTimeList, AlarmTimeNode, 0));
	time_t tmpTime = alarmNode->nextDeadline;
	
	g_array_remove_index(mRtcAlarmTimeList,0);
	LOGD("[%s:%s-%d] ((1 == sameAlarmCnt) && (time == tmpTime)) g_array_remove_index time = %u\n",
							__FILE__, __func__, __LINE__,tmpTime);
	if(mRtcAlarmTimeList->len > 0)
	{
		AlarmTimeNode *alarmNode = &(g_array_index(mRtcAlarmTimeList, AlarmTimeNode, 0));
		struct timespec ts;
		ts.tv_sec = alarmNode->nextDeadline;
		ts.tv_nsec = 0;
		ioctl(fd, ANDROID_ALARM_SET(ANDROID_ALARM_RTC_WAKEUP),&ts);
		LOGD("[%s:%s-%d] ((1 == sameAlarmCnt) && (time == tmpTime)) reset alarmNode->nextDeadline = %u\n", 
							__FILE__, __func__, __LINE__,alarmNode->nextDeadline);
		ret =  0;
	}
	else
	{
		LOGD("[%s:%s-%d] ((1 == sameAlarmCnt) && (time == tmpTime)) no alarm to set\n",
							__FILE__, __func__, __LINE__);
		ret =  -1;
		
	}
	return ret;
}

int AlarmService::deleteAlarm(time_t deadline,unsigned long nodeId)
{
	guint pos = 0;
	int ret = 0;
	
	for(pos=0; pos < mRtcAlarmTimeList->len; pos++)
	{
		AlarmTimeNode *alarmNode = &(g_array_index(mRtcAlarmTimeList, AlarmTimeNode, pos));
		if((deadline == alarmNode->nextDeadline) && (nodeId == alarmNode->mNodeId))
		{
			LOGD("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
			break;
		}
	}
	
	if(pos == mRtcAlarmTimeList->len)	
	{
		//error
		ret = -1;
	}
	else
	{
		g_array_remove_index(mRtcAlarmTimeList,pos);
		LOGD("[%s:%s-%d] ((1 == sameAlarmCnt) && (time != tmpTime)) g_array_remove_index time = %d\n",
								__FILE__, __func__, __LINE__,deadline);
		ret = 0;
	}
	return ret;
	
}




int AlarmService::cancelAlarm(time_t deadline,unsigned long nodeId)
{
	ALARM_SERVICE_ERROR_CODE ret = ALARM_SERVICE_ERROR_MAX;
	int sameAlarmCnt = 0;
	
	LOGD("%s\n",__func__);
	/*1 calc  sameAlarmCnt */
	
	for(guint i = 0; i < mRtcAlarmTimeList->len; i++)
	{
		AlarmTimeNode *alarmNode = &(g_array_index(mRtcAlarmTimeList, AlarmTimeNode, i));
		if(deadline == alarmNode->nextDeadline)
		{
			sameAlarmCnt++;
			LOGD("[%s:%s-%d]\n", __FILE__, __func__, __LINE__);
		}
	}
	
	LOGD("[%s:%s-%d] sameAlarmCnt = %d\n", __FILE__, __func__, __LINE__,sameAlarmCnt);

	// 2 get 1th node in mRtcAlarmTimeList
	AlarmTimeNode *alarmNode = &(g_array_index(mRtcAlarmTimeList, AlarmTimeNode, 0));
	time_t tmpTime = alarmNode->nextDeadline;
	unsigned long tmpNodeId =  alarmNode->mNodeId;

	// 3 
	if(0 == sameAlarmCnt)
	{
		//error cancel fail
		ret = ALARM_SERVICE_CANCAL_NO_EXIST;
	}
	else if((1 == sameAlarmCnt) && (deadline == tmpTime))//first and only one,clear alarm,and delete from AlarmTimeList,and set new alarm
	{
		if(tmpNodeId == nodeId)
		{
			LOGD("[%s:%s-%d] ((1 == sameAlarmCnt) && (time == tmpTime)) tmpNodeId == nodeId \n", __FILE__, __func__, __LINE__);
			ret = (0 == resetAlarm())?ALARM_SERVICE_CANCAL_OK:ALARM_SERVICE_CANCAL_NO_EXIST;
		}
		else
		{
			LOGD("[%s:%s-%d] ((1 == sameAlarmCnt) && (time == tmpTime)) tmpNodeId = %d,nodeId = %d\n", __FILE__, __func__, __LINE__,tmpNodeId,nodeId);
			ret = ALARM_SERVICE_CANCAL_NO_EXIST;
		}
	}
	else if((1 == sameAlarmCnt) && (deadline != tmpTime))//delete from AlarmTimeList
	{	
		int pos = 0;
		LOGD("[%s:%s-%d] ((1 == sameAlarmCnt) && (time != tmpTime))\n", __FILE__, __func__, __LINE__);
		ret = (0 == deleteAlarm(deadline,nodeId))?ALARM_SERVICE_CANCAL_OK:ALARM_SERVICE_CANCAL_NO_EXIST;
	}
	else if((sameAlarmCnt >= 2) && (deadline == tmpTime))//first and not only one,and delete from AlarmTimeList
	{
		LOGD("[%s:%s-%d] ((sameAlarmCnt >= 2)&& (time == tmpTime))\n", __FILE__, __func__, __LINE__);
		ret = (0 == deleteAlarm(deadline,nodeId))?ALARM_SERVICE_CANCAL_OK:ALARM_SERVICE_CANCAL_NO_EXIST;
	}
	else if((sameAlarmCnt >= 2) && (deadline != tmpTime))//delete from AlarmTimeList
	{
		LOGD("[%s:%s-%d] ((sameAlarmCnt >= 2)&& (time != tmpTime))\n", __FILE__, __func__, __LINE__);
		ret = (0 == deleteAlarm(deadline,nodeId))?ALARM_SERVICE_CANCAL_OK:ALARM_SERVICE_CANCAL_NO_EXIST;

	}
	
	return ret;
}
#endif


int AlarmService::registerAlarmCallback(const sp<IAlarmCallback>& callback,unsigned long nodeId)
{
	AlarmCbNode *client	 = NULL;
	bool bIsFind  = false; 
	
	LOGD("AlarmService registerAlarmCallback in.\n");

	if((0 == nodeId) && (NULL == callback.get()))
	{
		LOGD("nodeId == 0 or callback is NULL.\n");
		return -1;
	}
	
	mCallback = callback;
#if 0
	if(NULL != mAlarmCbList)
	{
		g_mutex_lock(&mRegList_mutex);
		for(int i = 0; i < mAlarmCbList->len; i++)
		{
			client = (AlarmCbNode *)g_ptr_array_index(mAlarmCbList, i);
			if(nodeId == client->mNodeId)
			{	
				LOGD("Already register callback.\n");
				bIsFind = true;
				client->mCallback = callback;  //need to update callback object 
			}
		}
		g_mutex_unlock(&mRegList_mutex);
	}
	
	if(!bIsFind)
	{
		AlarmCbNode *newClient = new AlarmCbNode;
		newClient->mNodeId = nodeId;
		newClient->mCallback = callback;
		
		LOGD("array_add %d node to mAlarmCbList\n", newClient->mNodeId);
		g_mutex_lock(&mRegList_mutex);
		g_ptr_array_add(mAlarmCbList, (gpointer)newClient);
		g_mutex_unlock(&mRegList_mutex);
	}
#endif
	
	LOGD("AlarmService registerAlarmCallback out.\n");
	
//sortTest();

//sortTest2();

}



