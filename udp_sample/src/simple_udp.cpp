
#include "simple_udp.h"


int SimpleUDP::SendUDP( uint8_t *data, int data_length)
{
	int ret = sendto(_sock, data, data_length, 0, (struct sockaddr *) &_addr, sizeof(_addr));
	return(ret);
}

int SimpleUDP::BindUDP(void)
{
	int ret = bind( _sock, (const struct sockaddr * ) &_addr, sizeof(_addr));
	return(ret);
}

int SimpleUDP::RecvUDP(uint8_t *data)
{
	memset(data, 0, BUFFER_SIZE);
	struct sockaddr_in addr;
	int ret = recvfrom(_sock, data, BUFFER_SIZE, 0, (struct sockaddr *) & addr, (socklen_t*)sizeof(addr));
	return(ret);
}

int SimpleUDP::RecvUDP(uint8_t *data, struct sockaddr* addr)
{
	memset(data, 0, BUFFER_SIZE);
	int ret = recvfrom(_sock, data, BUFFER_SIZE, 0, (struct sockaddr *) & addr, (socklen_t*)sizeof(addr));
	return(ret);
}

int SimpleUDP::RecvUDPNoWait(uint8_t *data)
{
	memset(data, 0, BUFFER_SIZE);
	struct sockaddr_in addr;
	int ret = recvfrom(_sock, data, BUFFER_SIZE, MSG_DONTWAIT, (struct sockaddr *) & addr, (socklen_t*)sizeof(addr));
	return(ret);
}

int SimpleUDP::RecvUDPNoWait(uint8_t *data, struct sockaddr* addr)
{
	memset(data, 0, BUFFER_SIZE);
	int ret = recvfrom(_sock, data, BUFFER_SIZE, MSG_DONTWAIT, (struct sockaddr *) & addr, (socklen_t*)sizeof(addr));
	return(ret);
}
