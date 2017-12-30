#include <stdio.h>
#include "TestAHandle.h"


namespace android {


TestAHandle::TestAHandle()
{
	
}

TestAHandle::~TestAHandle() 
{
	
}


void TestAHandle::onMessageReceived(const sp<AMessage> &msg) 
{
	switch (msg->what())
	{
		case 123:
		{
			//LOGD("onMessageReceived SIGNAL_1");
			printf("onMessageReceived 123 \r\n");
			break;
		}

		default:
		break;

	}

}

}

	
