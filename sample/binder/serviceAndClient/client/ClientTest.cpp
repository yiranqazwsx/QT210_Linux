#include <cerrno>
#include <iostream>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

using namespace android;
using namespace std;


//
String16 SERVICE_NAME("SampleService");
enum command{
		ADD_INTS,
		SHARE_STRING,	
};

int main(int argc, char *argv[])
{
	int ret, opt;
	int  iter=0, payload=0;

	//Parse the command line arguments;
	while((opt = getopt(argc, argv, "n:d:p:?")) != -1){
		char *chaptr;
		switch(opt){
		case 'n': //set the iterations times
			iter = strtoul(optarg, &chaptr, 10);
			if(*chaptr !='\0'){
				cerr << "Invalid iterations value: "<< optarg << endl;
				exit(1);
			}
			if(iter < 1){
				cerr << "Less than 1 iteration specified by:  " << optarg << endl;
				exit(2);
			}
			break;
		case 'p': // set the payload size of share data
			payload = strtoul(optarg, &chaptr, 10);
			if(*chaptr != '\0'){
				cerr << "Invalid payload size: " << optarg << endl;
				exit(4);
			}
			break;
		case '?':
		default:
			cerr <<basename(argv[0])<< " [options]" << endl;
			cerr << "options:" << endl;
			cerr << "-n Test iterations times" << endl;
			cerr << "-s The payload size of data shared" << endl;
		}
	}

	sp<IServiceManager> sm = defaultServiceManager();
	sp<IBinder> binder;
	
	//通过服务名获取服务对象
	do{
		binder = sm->getService(SERVICE_NAME);
		if(binder  != 0) break;
		cout << SERVICE_NAME << ": not published, Waiting!!"<< endl;
		usleep(500000); //waiting 0.5s
	}while(true);

	//根据用户参数发送多次不同请求，分别为加法和字符串请求
	for(int i = 0; i < iter; i++)
	{
		Parcel send, reply;
		int expected, commad_id;

		// if payload == 0, we did the interger test
		if(payload == 0)
		{
			int val1 = i;
			int val2 = i+3;
			expected = val1 + val2;
			commad_id = ADD_INTS;
			send.writeInt32(val1);
			send.writeInt32(val2);
			
		}else{ // if payload size >0, we did the string share
			expected = payload;
			commad_id = SHARE_STRING;
			char *buf = new char [expected + 1];
			fill(buf, buf + expected, 'a');
			buf[expected + 1] = 0;
			cout << "Client buffer:" << buf << endl;
			send.writeInt32(strlen(buf));
			send.writeCString(buf);
		}
		ret = binder->transact(commad_id,send, &reply);
		if(ret){
			cerr << "binder->transact failed. ret:" << ret
			<< "errno:" << errno << endl;
			
			exit(6);
		}
		
		int result = reply.readInt32();
		if(expected != result){
			cerr<<"Error result for count:"<< i << endl;
			cerr << "Expected is:" << expected << endl;
			cerr << "Result is :" << result << endl;
		}else{
			cout << "Times:"<< i  << "; expected:" <<
			expected << "; result:" << result << endl;			
		}
	}

	return 0;
}
