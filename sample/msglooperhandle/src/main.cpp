#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <time.h>
#include "AlarmManager.h"
#include <msglooperhandle/ALooper.h>
#include <pthread.h>

#include "TestNotify.h"
#include "TestAHandle.h"

using namespace android;


int alarmEventCallback(unsigned int repeatFlag,time_t deadline)
{
	printf("[%s:%s-%d] repeatFlag= %u,deadline = %lu\n", __FILE__, __func__, __LINE__,repeatFlag,deadline);
	
	return 0;
}

TestNotify *pTestNotify;


sp<TestAHandle> testAHandle;


#define MSG_TYPE1 1
#define MSG_TYPE2 2

void* testNotifyThread(void *data)
{	
	while(1)
	{
		printf("[%s:%s-%d] post message\n", __FILE__, __func__, __LINE__);
		sp<AMessage> msg = new AMessage(MSG_TYPE1,testAHandle->id());
		//msg->setObject("mylooper_msg1", new AMessage(MSG_TYPE1,testAHandle->id())); 
		msg->setString("mylooper_msg1", "LUCY", strlen("LUCY"));
		msg->post(0);//0us

		sp<AMessage> msg2 = new AMessage(MSG_TYPE2,testAHandle->id());
		msg2->setObject("mylooper_msg2", new AMessage(MSG_TYPE2,testAHandle->id())); //�������ı�ʶ����mylooper_msg2
		msg2->post(0);//0us
		
		sleep(1);
		//��������ǰ�ͷ��ڴ�
	}

	
}

int main(int argc, char* argv[])
{
	pthread_t tid;
	int ret = 0;

	sp<ALooper> looper(new ALooper);
	looper->setName("mylooper");
	looper->start(
            false, /* runOnCallingThread */
            true,  /* canCallJava */
            0);//ANDROID_PRIORITY_NORMAL==0
            
	testAHandle = new TestAHandle;//����һ������message��handle����
	looper->registerHandler(testAHandle);//��lopp�ַ�message��testAHandle,�ڲ��Ѿ���testhandle ��looper�󶨣�����һ��id���

	ret = pthread_create(&tid, NULL, testNotifyThread, NULL); //�����߳�  


	while(1)
	{
		sleep(1);
	}
	return 0;
}

