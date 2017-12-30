/* Copyright 2008 The Android Open Source Project
 */

//#define LOG_TAG "MsgLooperHandle"



#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>

//#include <utils/RefBase.h>
#include <msglooperhandle/ALooper.h>

//#include <cutils/log.h>

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
//#include <private/android_filesystem_config.h>
#endif


#include <msglooperhandle/ADebug.h>

#include <msglooperhandle/ABase.h>
#include <msglooperhandle/AHandler.h>
#if 0
#define LOGI(x...) fprintf(stderr, "svcmgr: " x)
#define LOGE(x...) fprintf(stderr, "svcmgr: " x)
#else


#endif

#if 0
struct xxPlayerDriver {
   sp<ALooper> mLooper;

	xxPlayerDriver()
    {
    	mLooper(new ALooper);
	}

};
#endif


int main(int argc, char **argv)
{
	sp<ALooper> mLooper;
	
	//ALooper *pALooper = new ALooper();
	//mLooper(new ALooper);
	
	while(1)
	{
		printf("printf cannot become context manager\r\n");
   		LOGE("LOGE cannot become context manager\r\n");	
		SLOGD("SLOGD cannot become context manager\r\n");
  		sleep(1);
	}
  

    return 0;
}

