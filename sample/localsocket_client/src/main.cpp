#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <cutils/sockets.h>


#define PATH "android:renyimin"


int main(int argc, char *argv[]) 
{
	int socketID;
	int ret;
	int i = 0;
	int len = 0;
	char *buffer ;
	
	for(i=0; i<argc; i++)
	{
		len = len + strlen(argv[i]);
	}
	len = len + argc ;

	buffer = ( char *)malloc(len * sizeof( char *));
	
	if(buffer == NULL)
	{
		printf("malloc failed\n");
		return 0;
	}
	
	strcpy(buffer, argv[0]);
	for(i=1;i<argc;i++)
	{
		strcat(buffer, " "); 
		strcat(buffer, argv[i]); 
	}
	
	socketID = socket_local_client(PATH, ANDROID_SOCKET_NAMESPACE_ABSTRACT, SOCK_STREAM);
	if (socketID < 0)
	{
		return socketID;
	}
	ret = write(socketID, buffer, strlen(buffer));
	if(ret < 0)
	{
		printf("send failed\n");
		return ret;
	}
	
	char buf2[512] = {0};
	ret = read(socketID,buf2,sizeof(buf2));
	if(ret < 0)
	{
		printf("recived failed\n");
		return ret;
	}
	else
	{
		printf("c client recived from server: %s\n",buf2);
	}

	ret = close(socketID);
	if (ret < 0)
	{
		return ret;
	}

	return 0;
}



