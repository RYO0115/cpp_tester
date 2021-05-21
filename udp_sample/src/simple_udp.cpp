
#include "simple_udp.h"


//int SimpleUDP::SendUDP( uint8_t *data, int data_length, int flag=MSG_NOSIGNAL)
//{
//	int ret = sendto(_sock, data, data_length, flag, (struct sockaddr *) &_addr, sizeof(_addr));
//	return(ret);
//}

int SimpleUDP::SendUDP( uint8_t *data, int data_length, struct sockaddr_in addr,int flag=MSG_NOSIGNAL)
{
	int ret = sendto(_sock, data, data_length, flag, (struct sockaddr *) &addr, sizeof(addr));
	return(ret);
}

int SimpleUDP::BindUDP(void)
{
	int ret = bind( _sock, (const struct sockaddr * ) &_addr, sizeof(_addr));
	return(ret);
}

int SimpleUDP::BindUDP(struct sockaddr_in addr)
{
	int ret = bind( _sock, (const struct sockaddr * ) &addr, sizeof(addr));
	return(ret);
}

int SimpleUDP::RecvUDP(uint8_t *data)
{
	memset(data, 0, BUFFER_SIZE);
	struct sockaddr_in addr;
	int slen = sizeof(addr);
	int ret = recvfrom(_sock, data, BUFFER_SIZE, 0, (struct sockaddr *) & addr, (socklen_t*)&slen);
	return(ret);
}

int SimpleUDP::RecvUDP(uint8_t *data, struct sockaddr* addr)
{
	memset(data, 0, BUFFER_SIZE);
	int slen = sizeof(addr);
	int ret = recvfrom(_sock, data, BUFFER_SIZE, 0, (struct sockaddr *) & addr, (socklen_t*)&slen);
	return(ret);
}

int SimpleUDP::RecvUDPNoWait(uint8_t *data)
{
	memset(data, 0, BUFFER_SIZE);
	struct sockaddr_in addr;
	int slen = sizeof(addr);
	int ret = recvfrom(_sock, data, BUFFER_SIZE, MSG_DONTWAIT, (struct sockaddr *) & addr, (socklen_t*)&slen);
	return(ret);
}

int SimpleUDP::RecvUDPNoWait(uint8_t *data, struct sockaddr* addr)
{
	memset(data, 0, BUFFER_SIZE);
	int slen = sizeof(addr);
	int ret = recvfrom(_sock, data, BUFFER_SIZE, MSG_DONTWAIT, (struct sockaddr *) & addr, (socklen_t*)&slen);
	return(ret);
}
