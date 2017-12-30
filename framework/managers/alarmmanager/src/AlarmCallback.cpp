
#define LOG_TAG "AlarmCallback"
#include "AlarmCallback.h"
#include "AlarmManager.h"


#include <cutils/log.h>


AlarmCallback::AlarmCallback(void *pAlarmManager)

{
	//mpIndataQueue = g_queue_new();
	//g_mutex_init(&gmutex);
	//g_cond_init(&gcond);
	mAlarmManager = pAlarmManager;
	
}

AlarmCallback::~AlarmCallback()
{
	//g_mutex_clear(&gmutex);
	//g_cond_clear(&gcond);
	mAlarmManager = NULL;
}

int AlarmCallback::AlarmNotifyCallback(unsigned int repeatFlag,time_t deadline)
{  
	LOGD("AlarmNotifyCallback in.\n"); 
	if(mAlarmManager && (((AlarmManager *)mAlarmManager)->mAlarmEventCallback))
	{
		((AlarmManager *)mAlarmManager)->mAlarmEventCallback(repeatFlag,deadline);
	}
	
#if 0
	LOG_I("NotifyCallback in.\n"); 

	printf("Callback Msg = ");
	for(int i = 0; i < length; i++)
	{
		printf("%#2x ", Msg[i]);
	}
	printf("\n");

	CommunicateData *pCommunication = new CommunicateData;
	
	pCommunication->Cmd_type     = Msg[0];
	pCommunication->Component_id = Msg[1] >> 3;
	pCommunication->Cmd_type     = Msg[1] & 0x07;
	pCommunication->Cmd_number   = Msg[2];
	pCommunication->Cmd_size     = Msg[3];
	pCommunication->Cmd_flag     = Msg[4];
	memcpy(pCommunication->Cmd_param, Msg + 5, pCommunication->Cmd_size - 1);

	g_mutex_lock (&gmutex);
	g_queue_push_tail(mpIndataQueue, pCommunication);
	if(mpIndataQueue->length > 64)
	{
		LOG_E("Callback List len > 64.\n");
		g_queue_pop_head(mpIndataQueue);
	}
	g_mutex_unlock (&gmutex);
	g_cond_signal (&gcond);

	LOG_I("NotifyCallback out.\n"); 
#endif

	return 1;  
}


#if 0
int AlarmCallback::readCallbackMsg(CommunicateData  &pdata)
{
	CommunicateData *data = NULL;
	
	g_mutex_lock (&gmutex);
	while (!(mpIndataQueue->length > 0))
	{
		g_cond_wait(&gcond, &gmutex);
	}

	data = (CommunicateData*)g_queue_pop_head(mpIndataQueue);
	g_mutex_unlock (&gmutex);
	
	pdata = *data;
	
	delete data;
	
	return 1;
}
#endif


