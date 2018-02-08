/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>

#include <sys/syscall.h>

//#include "linker.h"
#include <stddef.h>
#include <sys/socket.h>
#include <sys/un.h>


pid_t gettid()
{
     return syscall(SYS_gettid);  /*������ں�*/
}


//void notify_gdb_of_libraries();

#define  RETRY_ON_EINTR(ret,cond) \
    do { \
        ret = (cond); \
    } while (ret < 0 && errno == EINTR)


static int socket_abstract_client(const char *name, int type)
{
    struct sockaddr_un addr;
    size_t namelen;
    socklen_t alen;
    int s, err;

    namelen  = strlen(name);

    // Test with length +1 for the *initial* '\0'.
    if ((namelen + 1) > sizeof(addr.sun_path)) {
        errno = EINVAL;
		printf("socket_abstract_client 01\r\n");
        return -1;
    }

    /* This is used for abstract socket namespace, we need
     * an initial '\0' at the start of the Unix socket path.
     *
     * Note: The path in this case is *not* supposed to be
     * '\0'-terminated. ("man 7 unix" for the gory details.)
     */
    memset (&addr, 0, sizeof addr);
    addr.sun_family = AF_LOCAL;
    addr.sun_path[0] = 0;
    memcpy(addr.sun_path + 1, name, namelen);

    alen = namelen + offsetof(struct sockaddr_un, sun_path) + 1;

    s = socket(AF_LOCAL, type, 0);
    if(s < 0) {
		printf("socket_abstract_client 02\r\n");
		return -1;
	}

    RETRY_ON_EINTR(err,connect(s, (struct sockaddr *) &addr, alen));
    if (err < 0) {
		
	printf("socket_abstract_client 03 err = %d\r\n",err);
        close(s);
        s = -1;
    }

    return s;
}

//#include "linker_format.h"
//#include <../libc/private/logd.h>

/*
 * Writes a summary of the signal to the log file.
 *
 * We could be here as a result of native heap corruption, or while a
 * mutex is being held, so we don't want to use any libc functions that
 * could allocate memory or hold a lock.
 */
static void logSignalSummary(int signum, const siginfo_t* info)
{
    char buffer[128];

    char* signame;
    switch (signum) {
        case SIGILL:    signame = "SIGILL";     break;
        case SIGABRT:   signame = "SIGABRT";    break;
        case SIGBUS:    signame = "SIGBUS";     break;
        case SIGFPE:    signame = "SIGFPE";     break;
        case SIGSEGV:   signame = "SIGSEGV";    break;
        case SIGSTKFLT: signame = "SIGSTKFLT";  break;
        case SIGPIPE:   signame = "SIGPIPE";    break;
        default:        signame = "???";        break;
    }

    //format_buffer(buffer, sizeof(buffer),
    //    "Fatal signal %d (%s) at 0x%08x (code=%d)",
    //    signum, signame, info->si_addr, info->si_code);
    
    //__libc_android_log_write(ANDROID_LOG_FATAL, "libc", buffer);
	sprintf(buffer,		
	        "Fatal signal %d (%s) at 0x%08x (code=%d)\r\n",
	        signum, signame, info->si_addr, info->si_code);
		
	printf("ANDROID_LOG_FATAL libc %s",buffer);

}

/*
 * Catches fatal signals so we can ask debuggerd to ptrace us before
 * we crash.
 */
void debugger_signal_handler(int n, siginfo_t* info, void* unused)
{
    unsigned tid;
    int s;
	
	printf("debugger_signal_handler 01\r\n");
	logSignalSummary(n, info);
	printf("debugger_signal_handler 02\r\n");
	tid = gettid();
	printf("debugger_signal_handler 03 tid = %d\r\n",tid);
	
    s = socket_abstract_client("android:debuggerd", SOCK_STREAM);

    if(s >= 0) {
        /* debugger knows our pid from the credentials on the
         * local socket but we need to tell it our tid.  It
         * is paranoid and will verify that we are giving a tid
         * that's actually in our process
         */
        int  ret;

        RETRY_ON_EINTR(ret, write(s, &tid, sizeof(unsigned)));
        if (ret == sizeof(unsigned)) {
            /* if the write failed, there is no point to read on
             * the file descriptor. */
            RETRY_ON_EINTR(ret, read(s, &tid, 1));
			printf("debugger_signal_handler 05 tid = %d\r\n",tid);
            //notify_gdb_of_libraries();
        }
        close(s);
    }
else
{
	printf("debugger_signal_handler 06 tid = %d\r\n",tid);

}	
    /* remove our net so we fault for real when we return */
    signal(n, SIG_DFL);
}

void debugger_init()
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = debugger_signal_handler;
    act.sa_flags = SA_RESTART | SA_SIGINFO;
    sigemptyset(&act.sa_mask);

    sigaction(SIGILL, &act, NULL);
    sigaction(SIGABRT, &act, NULL);
    sigaction(SIGBUS, &act, NULL);
    sigaction(SIGFPE, &act, NULL);
    sigaction(SIGSEGV, &act, NULL);
    sigaction(SIGSTKFLT, &act, NULL);
    sigaction(SIGPIPE, &act, NULL);
}