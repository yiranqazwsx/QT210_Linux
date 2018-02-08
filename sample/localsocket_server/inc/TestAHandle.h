
#include <msglooperhandle/AHandler.h>
#include <msglooperhandle/AMessage.h>
#include <utils/RefBase.h>

namespace android {


enum {
	SIGNAL_1,
	SIGNAL_2,
};


struct TestAHandle : public AHandler {
    TestAHandle();
protected:
	virtual ~TestAHandle();
	virtual void onMessageReceived(const sp<AMessage> &msg);
};

}

