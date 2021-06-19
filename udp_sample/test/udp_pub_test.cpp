
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 	// socket close
#include <arpa/inet.h> 	//inet_aton

#include <sys/ioctl.h>
#include <netdb.h>
#include <ifaddrs.h>

#include <chrono>
#include <thread>

#define BUFFER_SIZE  2048

int main(void)
{
	int sock;
	struct sockaddr_in addr;

    printf("Start\n");

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    std::string text_str;
    std::string text_base_str = "Hello UDP World!! -> ";

    printf("Finsh Setup\n");

    uint8_t id, x, y, z;

    x = 0;
    y = 0;
    z = 0;

    uint8_t buf[BUFFER_SIZE];

    for(int i=0; i<10000; i++)
    {
        id = i;
        z++;
        y += 2;
        x += 3;
        memset( buf, 0, sizeof(buf));
        uint8_t* p = buf;
        memcpy( p, &id, 1); 
        p++;
        memcpy( p, &x, 1);
        p++;
        memcpy( p, &y, 1);
        p++;
        memcpy( p, &z, 1);
        p++;

		printf("(id,x,y,z)=(%d,%d,%d,%d)\n", buf[0], buf[1], buf[2], buf[3]);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        sendto(sock, buf, 4, 0, (struct sockaddr *) &addr, sizeof(addr));
        /*
        printf("Send -- %s -- for %d times\n", text_base_str.c_str(), i);
        text_str = text_base_str + std::to_string(i); // "Hello UDP World!! -> i"
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        sendto(sock, text_str.c_str(), text_str.length(), 0, (struct sockaddr *) &addr, sizeof(addr));
        */



    }

    close(sock);

   return(0);

}