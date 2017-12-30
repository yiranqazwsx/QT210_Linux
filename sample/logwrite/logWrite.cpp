/* Copyright 2008 The Android Open Source Project
 */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
//#include <private/android_filesystem_config.h>



#if 0
#define LOGI(x...) fprintf(stderr, "svcmgr: " x)
#define LOGE(x...) fprintf(stderr, "svcmgr: " x)
#else
#define LOG_TAG "ServiceManager"
#include <cutils/log.h>
#endif


int main(int argc, char **argv)
{

	while(1)
	{
		printf("printf cannot become context manager\r\n");
   		LOGE("LOGE cannot become context manager\r\n");	
		SLOGD("SLOGD cannot become context manager\r\n");
  		sleep(1);
	}
  

    return 0;
}

