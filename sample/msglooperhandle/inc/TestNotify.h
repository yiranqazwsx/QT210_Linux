
#include <msglooperhandle/AHandler.h>
#include <msglooperhandle/AMessage.h>
#include <utils/StrongPointer.h>

namespace android {


struct TestNotify{
	TestNotify();
	void registerHandle(const char *signalName,const sp<AHandler> &handler) ;
protected:
	~TestNotify();

	
};

}

