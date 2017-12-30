#include <cerrno>
#include <iostream>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

using namespace android;
using namespace std;

//服务名
String16 SERVICE_NAME("SampleService");

class SampleService:public BBinder
{
public:
	SampleService();
	virtual ~SampleService(){}

	virtual status_t onTransact(uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags = 0);

	enum command{
		ADD_INTS,
		SHARE_STRING,	
	};
};



SampleService::SampleService()
{

}

//在这里根据code的值接收处理不同的客户端请求
status_t SampleService::onTransact(uint32_t code, const Parcel &data, Parcel *reply,
			uint32_t flags)
{
	int val1, val2;

	switch(code){
	case ADD_INTS:
		val1 = data.readInt32();
		val2 = data.readInt32();
		reply->writeInt32(val1 + val2);
		break;
	case SHARE_STRING:	
		val1 = data.readInt32();
		cout << "Service buffer:" << data.readCString() <<endl;
		reply->writeInt32(val1);
		break;
	default:
		cerr << "Unknown Transact code:  " << code << endl;
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	int ret;

	sp<ProcessState> proc(ProcessState::self());
	sp<IServiceManager> sm = defaultServiceManager();
	
	//向ServiceManager注册服务
	ret = sm->addService(SERVICE_NAME, new SampleService());
	if(ret){
		cerr << "Add service" <<  SERVICE_NAME  << "failed return:"
			<< ret << "; erorr num:"<< errno << endl;
	} 	

	proc->startThreadPool();

	IPCThreadState::self()->joinThreadPool();
	return 0;
}


