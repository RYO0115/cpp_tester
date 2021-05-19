

#include <stdio.h>
#include <string.h>

#include <thread>

#include "simple_udp.h"

#define BUFFER_SIZE  2048
/*

int main(void)
{
	//int sock;
	int sock[2];
	struct sockaddr_in addr;

	char buf[BUFFER_SIZE];

	//sock = socket(AF_INET, SOCK_DGRAM, 0);
	sock[0] = socket(AF_INET, SOCK_DGRAM, 0);
	sock[1] = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = INADDR_ANY;

	//bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	bind(sock[0], (struct sockaddr *)&addr, sizeof(addr));

	addr.sin_port = htons(12346);
	//bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	bind(sock[1], (struct sockaddr *)&addr, sizeof(addr));


	memset(buf, 0, sizeof(buf));
	//recv(sock,buf, sizeof(buf), 0);
	recv(sock[0],buf, sizeof(buf), 0);
	printf("sock1:%s\n",buf);
	memset(buf, 0, sizeof(buf));
	//recv(sock,buf, sizeof(buf), 0);
	recv(sock[1],buf, sizeof(buf), 0);
	printf("sock2:%s\n",buf);



	//close(sock);
	close(sock[0]);
	close(sock[1]);

	return(0);

}
*/

#include <thread>

void ThreadFunc1( struct sockaddr_in addr)
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

	std::thread th1(ThreadFunc1, addr);
	th1.join();

	addr.sin_port = htons(12346);

	ThreadFunc2(addr);
	//std::thread th2(ThreadFunc2, addr);
	//th2.join()

	return(0);
}
