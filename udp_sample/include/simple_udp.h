
#ifndef __SIMPLE_UDP__
#define __SIMPLE_UDP__


#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 	// socket close
#include <arpa/inet.h> 	//inet_aton

#include <sys/ioctl.h>
#include <netdb.h>
#include <ifaddrs.h>

#define BUFFER_SIZE  2048

class SimpleUDP
{
private:
	int _sock;
	struct sockaddr_in _addr;

public:
	//uint8_t buf_[BUFFER_SIZE];

	SimpleUDP( char* address, int port)
	{
		_sock = socket(AF_INET, SOCK_DGRAM, 0);
		_addr.sin_family = AF_INET;
		_addr.sin_addr.s_addr = inet_addr(address);
		_addr.sin_port = htons(port);
		//_addr.sin_port = port;
	}
	~SimpleUDP()
	{
		if(_sock > 0)
		{
			close(_sock);
		}
	}

	//int SendUDP(uint8_t *data, int data_length);
	//int SendUDP(uint8_t *data, int data_length, int flags);
	int SendUDP( uint8_t *data, int data_length, struct sockaddr_in addr,int flag);
	int BindUDP(void);
	int BindUDP(struct sockaddr_in addr);

	int RecvUDP(uint8_t *data);
	int RecvUDP(uint8_t *data, struct sockaddr* addr);
	int RecvUDPNoWait(uint8_t *data);
	int RecvUDPNoWait(uint8_t *data, struct sockaddr* addr);

	int GetSock(void){ return(_sock); }

	uint32_t GetAddr(void){ return((uint32_t)_addr.sin_addr.s_addr); }

	uint32_t GetSInPort(void){ return((uint32_t)_addr.sin_port); }

};

#endif /* __SIMPLE_UDP__ */


