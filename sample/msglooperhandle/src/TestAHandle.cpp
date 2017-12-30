#include <stdio.h>
#include "TestAHandle.h"


namespace android {



#define MSG_TYPE1 1
#define MSG_TYPE2 2


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
		case MSG_TYPE1:
		{
			AString *aString = new AString();
			msg->findString("mylooper_msg1",aString);
			printf("onMessageReceived msg1 : %s\r\n",aString->c_str());
			break;
		}
		case MSG_TYPE2:
		{
			printf("onMessageReceived msg2 \r\n");
			break;
		}
		default:
		break;

	}

}

}

	
