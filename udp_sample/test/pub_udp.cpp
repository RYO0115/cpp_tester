
#include <stdio.h>
#include <string.h>

#include <thread>

#include "simple_udp.h"

#define BUFFER_SIZE  2048


int main(void)
{
	int sock[2];
	struct sockaddr_in addr;

	sock[0] = socket(AF_INET, SOCK_DGRAM, 0);
	sock[1] = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	std::string text= "Hello UDP World!!";
	sendto(sock[0], text.c_str(), text.length(), 0, (struct sockaddr *) &addr, sizeof(addr));
	addr.sin_port = htons(12346);
	text = "Hello UDP World!! 12346";
	sendto(sock[1], text.c_str(), text.length(), 0, (struct sockaddr *) &addr, sizeof(addr));

	for(int i=0; i<1000; i++)
	{
		addr.sin_family = AF_INET;
		addr.sin_port = htons(12345);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");

		std::string text= "Hello UDP World!!";
		sendto(sock[0], text.c_str(), text.length(), 0, (struct sockaddr *) &addr, sizeof(addr));

		if(i%5==0)
		{
			addr.sin_port = htons(12346);
			text = "Hello UDP World!! 12346";
			sendto(sock[1], text.c_str(), text.length(), 0, (struct sockaddr *) &addr, sizeof(addr));
		}
	}

	close(sock[0]);
	close(sock[1]);

	return(0);

}


