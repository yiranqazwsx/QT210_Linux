#if 0

#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <time.h>
#include <pthread.h>


using namespace android;



void* testNotifyThread(void *data)
{	
	int cnt = 0;
	
	while(1)
	{
		printf("[%s:%s-%d] cnt = %d\n", __FILE__, __func__, __LINE__,cnt++);
		sleep(1);
		//反大括号前释放内存
	}
}

int main(int argc, char* argv[])
{
	pthread_t tid;
	int ret = 0;
	
	ret = pthread_create(&tid, NULL, testNotifyThread, NULL); //创建线程  

	while(1)
	{
		sleep(1);
	}
	return 0;
}

#endif


#if 0

#include <signal.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <execinfo.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <string.h>  
#include <unistd.h> 


#define PRINT_DEBUG  
static void print_reason(int sig, siginfo_t * info, void *secret)  
{  
	void *array[10];  
	size_t size;
	
#ifdef PRINT_DEBUG  
	char **strings;  
	size_t i;  
	
	size = backtrace(array, 10);  
	strings = backtrace_symbols(array, size);  
	printf("Obtained %zd stack frames.\n", size);  
	
	for (i = 0; i < size; i++)  
	{
		printf("%s\n", strings[i]);  
	}
		
	free(strings);  
#else
	int fd = open("err.log", O_CREAT | O_WRONLY);  
	size = backtrace(array, 10);  
	backtrace_symbols_fd(array, size, fd);  
	close(fd);  
#endif  
	exit(0);  
}  
void die()  
{  
	char *test1;  
	char *test2;  
	char *test3;  
	char *test4 = NULL;  
	strcpy(test4, "ab");  
}

void test1()  
{  
	die();  
} 



int main(int argc, char **argv)  
{  
	struct sigaction myAction;  
	
	myAction.sa_sigaction = print_reason;  
	sigemptyset(&myAction.sa_mask);  
	myAction.sa_flags = SA_RESTART | SA_SIGINFO;  

	sigaction(SIGSEGV, &myAction, NULL);  
	sigaction(SIGUSR1, &myAction, NULL);  
	sigaction(SIGFPE, &myAction, NULL);  
	sigaction(SIGILL, &myAction, NULL);  
	sigaction(SIGBUS, &myAction, NULL);  
	sigaction(SIGABRT, &myAction, NULL);  
	sigaction(SIGSYS, &myAction, NULL);  
	
	test1();

	while(1);
}


#endif



#if 0
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <execinfo.h>
#include <signal.h>

void dump(int signo)
{
 void *buffer[30] = {0};
 size_t size;
 char **strings = NULL;
 size_t i = 0;

 size = backtrace(buffer, 30);
 fprintf(stdout, "Obtained %zd stack frames.nm\n", size);
 strings = backtrace_symbols(buffer, size);
 if (strings == NULL)
 {
  perror("backtrace_symbols.");
  exit(EXIT_FAILURE);
 }
 
 for (i = 0; i < size; i++)
 {
  fprintf(stdout, "%s\n", strings[i]);
 }
 free(strings);
 strings = NULL;
 exit(0);
}

void func_c()
{
 *((volatile char *)0x0) = 0x9999;
}

void func_b()
{
 func_c();
}

void func_a()
{
 func_b();
}

int main(int argc, const char *argv[])
{
 if (signal(SIGSEGV, dump) == SIG_ERR)
  perror("can't catch SIGSEGV");
 func_a();
 return 0;
}


#endif



#include<stdio.h>  
#include<stdlib.h>  
#include<signal.h>  
#include<string.h>  
#include<execinfo.h>  
#include<debugger.h>
#include <unistd.h>
#include <pthread.h>
//#include <utils/CallStack.h>  
//#include <utils/CallStack.h>  


//using namespace android;

void fun2()
{
	//CallStack stack;  
	//stack.update();
	//stack.dump(); 
}

void SystemErrorHandler(int signum)  
{  
#if 0
    const int len=1024*10;  
    void *func[len];  
    size_t size;  
    int i;  
    char **funs;  
  
    signal(signum,SIG_DFL);  
    size=backtrace(func,len);  
    funs=(char**)backtrace_symbols(func,size);  
    fprintf(stderr,"System error, Stack trace:\n");  
    for(i=0;i<size;++i) fprintf(stderr,"%d %s \n",i,funs[i]);  
    free(funs);  

#else


fun2();

exit(1); 
#endif

}  
  
void Fun1()  
{  
#if 0
    char *p=NULL;  
    *p = 'A';  
#else
	char *p = (char *)malloc(64);
	free(p);
	free(p);

#endif




}  
  
void Fun()  
{  
    Fun1();  
}  


  
void* testNotifyThread(void *data)
{	
	int cnt = 0;
	
	while(1)
	{
		printf("[%s:%s-%d] cnt = %d\n", __FILE__, __func__, __LINE__,cnt++);
		sleep(1);
		Fun() ;
		//反大括号前释放内存
	}
}



int main(const int argc,const char* argv[])  
{  
	pthread_t tid;
	int ret = 0;
	
	debugger_init();

	ret = pthread_create(&tid, NULL, testNotifyThread, NULL); //创建线程  

	while(1)
	{
		sleep(1);
	}
    return 0;  
}
