

#include <stdio.h>
#include <string.h>

#include <thread>

#include "simple_udp.h"

#define BUFFER_SIZE  2048

#include <thread>
#include <mutex>

bool buffer_full_flag_;

// Main Thread
void ThreadFunc1( void )
{
	while(1)
	{
		memset( buf, 0, sizeof(buf));
		recv( sock, buf, sizeof(buf), 0);
		printf("sock1:%d:%s\n",counter,buf);
		counter++;
	}
	close(sock);
}

void ThreadFunc2( struct sockaddr_in addr)
{
	int sock;

	char buf[BUFFER_SIZE];
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	bind(sock, (struct sockaddr *)&addr, sizeof(addr));

	int counter = 0;
	while(1)
	{
		memset( buf, 0, sizeof(buf));
		recv( sock, buf, sizeof(buf), 0);
		printf("sock2:%d:%s\n",counter,buf);
		counter++;
	}
	close(sock);
}

int main(void)
{
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = INADDR_ANY;

	buffer_full_flag_ = false;

	std::thread th1(ThreadFunc1, addr);
	th1.join();

	addr.sin_port = htons(12346);

	ThreadFunc2(addr);
	//std::thread th2(ThreadFunc2, addr);
	//th2.join()

	return(0);
}
